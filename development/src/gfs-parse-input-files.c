/*
 *  `gfs-parse-input-files.c'.
 *
 *  This interface deals with the parsing of the input files.
 *
 *  Copyright (C) 2008  Efstathios Chatzikyriakidis (contact@efxa.org).
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
   \file gfs-parse-input-files.c
   \brief This interface deals with the parsing of the input files.
*/

/* standard includes. */
#include <stdio.h>

/* basic includes. */
#include "gfs-typedefs.h"
#include "gfs-input-files-list.h"

/* function prototypes. */
INPUT_FILES *parse_input_files (INPUT_FILES * listp, cint argc, char *argv[]);

/* functions. */

/*!
   \fn INPUT_FILES * parse_input_files (INPUT_FILES *, cint, char *[])

   \brief A function that parses the command line input files arguments.

   This function parses all the command line arguments that seems to be
   input files (by using `argc', `argv', `optind'). For each input file
   checks if it is acceptable (necessary conditions). If it does, adds
   it to the input files linked list `listp'. At the end, it returns the
   input files linked list `listp'.

   \param listp a pointer to a `INPUT_FILES' data structure.
   \param argc a constant integer value.
   \param argv an array of pointers to a character.

   \return A pointer to a `INPUT_FILES' data structure.
*/
INPUT_FILES *
parse_input_files (INPUT_FILES * listp, cint argc, char *argv[])
{
  /* externs. */

  /* function externs. */
  extern INPUT_FILE *new_input_file (const char *);
  extern INPUT_FILE *add_input_file (INPUT_FILE *, INPUT_FILE *);
  extern BOOL input_file_exists (INPUT_FILES *, cstring);
  extern FILE_INFO check_input_file (cstring);

  /* variable externs. */

  /* starting input files position. */
  extern int optind;

  /* if there are possible input files check them. */
  if (argc > optind)
    {
      /* is used for the loop. */
      register int i;

      /* parse possible input files (accept only
         regular ascii files and add them to the
         list. */
      for (i = optind; i < argc; i++)
        if (!input_file_exists (listp, argv[i]))
          if (check_input_file (argv[i]) == f_accessible)
            listp = add_input_file (listp, new_input_file (argv[i]));
    }

  /* return the input files list. */
  return listp;
}
