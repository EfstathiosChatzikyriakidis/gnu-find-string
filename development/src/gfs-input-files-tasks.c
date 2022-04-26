/*
 *  `gfs-input-files-tasks.c'.
 *
 *  This interface deals with the checking of input files.
 *
 *  Copyright (C) 2008  Efstathios Chatzikyriakidis (stathis.chatzikyriakidis@gmail.com).
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*!
   \file gfs-input-files-tasks.c
   \brief This interface deals with the checking of input files.
*/

/* standard includes. */
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/stat.h>
#include <errno.h>

/* basic includes. */
#include "gfs-typedefs.h"
#include "gfs-input-files-list.h"

/* function prototypes. */
FILE_INFO check_input_file (cstring filepath);
static FILE_INFO get_file_type (cstring filepath);
static FILE_INFO file_regular (cstring filepath);

/* functions. */

/*!
   \fn FILE_INFO check_input_file (cstring)

   \brief A function that checks if a file is acceptable.

   This function checks if a file (`filepath') is acceptable.
   That means, that it is a readable and regular ascii file.

   \param filepath a `cstring' type definition.

   \return A `FILE_INFO' enumeration value.
*/
FILE_INFO
check_input_file (cstring filepath)
{
  /* is used for system's routine `access'. */
  register int aval;

  /* is used in order to know the info of the file. */
  FILE_INFO finfo;

  /* check if the file exists. */
  aval = access (filepath, F_OK);
  if (aval != 0)
    {
      if (errno == ENOENT)
        return f_unknown;        /* file doesn't exist. */
      else if (errno == EACCES)
        return f_inaccessible;        /* we cannot access it. */
      else
        return f_io_error;        /* an i/o problem occured. */
    }

  /* check if the file is readable. */
  aval = access (filepath, R_OK);
  if (aval != 0)
    /* we cannot read it. */
    return f_inaccessible;
  else
    {
      /* get the info of the file. */
      finfo = get_file_type (filepath);

      /* if it is a regular file. */
      if (finfo == f_regular)
        {
          /* get the type of regular
             file (ascii or binary). */
          finfo = file_regular (filepath);
          if (finfo == f_ascii)
            /* we accept the input file. */
            return f_accessible;
          else
            /* return the info of the file. */
            return finfo;
        }
      else
        /* return the info of the file. */
        return finfo;
    }

  /* if the control flow reaches
     here do not accept the file. */
  return f_inaccessible;
}

/*!
   \brief Constants used from the interface.

   This anonymous enumeration is used from the
   interface in order to specify some constants.
*/
enum
{
  BIN_BUF_LEN = 512                /*!< Binary buffer length. */
};

/*!
   \fn static FILE_INFO file_regular (cstring)

   \brief A function that checks if a file is binary or not.

   This function checks if an input file (`filepath') is binary or
   ascii. Specifically, it reads the first `BIN_BUF_LEN' characters
   of the file and checks if there are any non ascii characters. If
   there is at least one, then returns that the file is binary. But,
   if there aren't any non-ascii characters then, returns that the
   file is ascii.

   \param filepath a `cstring' type definition.

   \return A `FILE_INFO' enumeration value.
*/
static FILE_INFO
file_regular (cstring filepath)
{
  /* externs. */

  /* function externs. */
  extern FILE *efopen (const char *, const char *);

  /* the buffer of characters. */
  static uchar buf[BIN_BUF_LEN];

  /* temporary help variables. */
  register ulong i, n;

  /* this is a pointer to the file. */
  FILE *fp = NULL;

  /* try to open the file. */
  if ((fp = efopen (filepath, "r")) == NULL)
    /* an error occured. */
    return f_io_error;

  /* try to read from the file. */
  n = fread (buf, sizeof (buf[0]), sizeof (buf), fp);

  /* there was a problem with the reading. */
  if (n < BIN_BUF_LEN)
    {
      /* close the file. */
      if (fp != NULL)
        fclose (fp);

      /* an error occured. */
      return f_io_error;
    }

  /* check each character if it is binary. */
  for (i = 0L; i < n; i++)
    if (!isprint (buf[i]) &&        /* is not printable character. */
        !isspace (buf[i]) &&        /* is not a space character. */
        !ispunct (buf[i]) &&        /* is not a punctuation character. */
        !isalnum (buf[i]) &&        /* is not an alphabetic, digit character. */
        iscntrl (buf[i]))        /* is a control character. */
      {
        /* close the file. */
        if (fp != NULL)
          fclose (fp);

        /* the file is a regular binary file. */
        return f_binary;
      }

  /* close the file. */
  if (fp != NULL)
    fclose (fp);

  /* the file is a regular ascii file. */
  return f_ascii;
}

/*!
   \fn static FILE_INFO get_file_type (cstring)

   \brief A function that gets the type of a file.

   This function tries to get the type of a file
   (`filepath'). After that, it returns the type.

   \param filepath a `cstring' type definition.

   \return A `FILE_INFO' enumeration value.
*/
static FILE_INFO
get_file_type (cstring filepath)
{
  /* buffer for keeping file info. */
  struct stat stbuf;

  /* get the information of the file. */
  if (stat (filepath, &stbuf) == -1)
    return f_io_error;

  /* return the appropriate type of the file. */
  if (S_ISREG (stbuf.st_mode))
    return f_regular;
  else if (S_ISDIR (stbuf.st_mode))
    return f_directory;
  else if (S_ISBLK (stbuf.st_mode))
    return f_block;
  else if (S_ISCHR (stbuf.st_mode))
    return f_character;
  else if (S_ISFIFO (stbuf.st_mode))
    return f_fifo;

  /* if the control flow reaches
     here assume it as a bizarre. */
  return f_inaccessible;
}
