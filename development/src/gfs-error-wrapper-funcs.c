/*
 *  `gfs-error-wrapper-funcs.c'.
 *
 *  This interface deals with the error wrapper functions.
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
   \file gfs-error-wrapper-funcs.c
   \brief This interface deals with the error wrapper functions.
*/

/* standard includes. */
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/* basic includes. */
#include "gfs-defines.h"
#include "gfs-input-files-list.h"

/* function prototypes. */
void eprintf (char *fmt, ...);
void weprintf (char *fmt, ...);
FILE *efopen (const char *filepath, const char *mode);
char *estrdup (const char *str);
void *emalloc (size_t size);

/* functions. */

/*!
   \fn void eprintf (char *, ...)

   \brief A function that prints an error message and exits.

   This function gets a formatted `fmt' arguments list `args'
   and tries to print an error message. If the program has a
   name then prints it at the beginning of the line. Also, if
   the user wants to print the reason of the error, then the
   function does it. At the end, the function deallocates the
   input files linked list and exits with an error code.

   \param fmt a pointer to a character.
   \param ... an arguments list.
*/
void
eprintf (char *fmt, ...)
{
  /* externs. */

  /* function externs. */
  extern void free_input_files (INPUT_FILES *);
  extern const char *get_prog_name (void);

  /* variables externs. */

  /* the input files linked list. */
  extern INPUT_FILES *input_files_list;

  /* points to each unnamed arg in turn. */
  va_list args;

  /* flush the standard output. */
  fflush (stdout);

  /* if there is a program name print it. */
  if (get_prog_name () != NULL)
    fprintf (stderr, "%s: ", get_prog_name ());

  /* make up point to 1st unnamed arg. */
  va_start (args, fmt);

  /* print `args' according to `fmt'. */
  vfprintf (stderr, fmt, args);

  /* clean up when done. */
  va_end (args);

  /* if the `fmt' isn't empty and the last char
     of it, is `:' then print an error message
     according to the `errno' last value. */
  if (fmt[0] != '\0' && fmt[strlen (fmt) - 1] == ':')
    fprintf (stderr, " %s.", strerror (errno));

  /* print a new line. */
  fprintf (stderr, "%s", NEW_LINE);

  /* free input files linked list. */
  free_input_files (input_files_list);

  /* exit the program. */
  exit (EXIT_ERROR);
}

/*!
   \fn void weprintf (char *, ...)

   \brief A function that prints a warning message.

   This function gets a formatted `fmt' arguments list `args'
   and tries to print a warning message. If the program has a
   name then prints it at the beginning of the line. Also, if
   the user wants to print the reason of the error, then the
   function does it.

   \param fmt a pointer to a character.
   \param ... an arguments list.
*/
void
weprintf (char *fmt, ...)
{
  /* externs. */

  /* function externs. */
  extern const char *get_prog_name (void);

  /* points to each unnamed arg in turn. */
  va_list args;

  /* flush the standard output. */
  fflush (stdout);

  /* if there is a program name print it. */
  if (get_prog_name () != NULL)
    fprintf (stderr, "%s: ", get_prog_name ());

  /* make up point to 1st unnamed arg. */
  va_start (args, fmt);

  /* print `args' according to `fmt'. */
  vfprintf (stderr, fmt, args);

  /* clean up when done. */
  va_end (args);

  /* if the `fmt' isn't empty and the last char
     of it, is `:' then print an error message
     according to the `errno' last value. */
  if (fmt[0] != '\0' && fmt[strlen (fmt) - 1] == ':')
    fprintf (stderr, " %s.", strerror (errno));

  /* print a new line. */
  fprintf (stderr, "%s", NEW_LINE);
}

/*!
   \fn char * estrdup (const char *)

   \brief A function that duplicates a string and checks for error.

   This function tries to allocate enough memory space in order to
   duplicate the `str' string. If an error occur, then prints the
   error message and exits. Otherwise, duplicates the string and
   returns a pointer to it.

   \param str a pointer to a constant character.

   \return A pointer to a character.
*/
char *
estrdup (const char *str)
{
  /* allocate enough memory space. */
  char *tmp = (char *) malloc (strlen (str) + 1);

  /* if memory allocation fail. */
  if (tmp == NULL)
    eprintf ("estrdup(\"%.500s\") failed:", str);

  /* copy the string. */
  strcpy (tmp, str);

  /* return the string. */
  return tmp;
}

/*!
   \fn void * emalloc (size_t)

   \brief A function that allocates memory space and checks for error.

   This function tries to allocate memory space of `size' bytes. If
   an error occur then prints an error message and exits. Otherwise,
   returns the pointer of the first byte of the allocated memory space.

   \param size a `size_t' type definition.

   \return A pointer to void.
*/
void *
emalloc (size_t size)
{
  /* allocate enough memory space. */
  void *ptr = malloc (size);

  /* if memory allocation fail. */
  if (ptr == NULL)
    eprintf ("malloc(%u) failed:", size);

  /* return the pointer. */
  return ptr;
}

/*!
   \fn FILE * efopen (const char *, const char *)

   \brief A function that opens a file and checks for error.

   This function tries to open a file (`filepath') with mode
   (`mode'). If the file open then returns the pointer to the
   file. Otherwise, prints an error message and returns NULL.

   \param filepath a pointer to a constant character.
   \param mode a pointer to a constant character.

   \return A pointer to a `FILE' data structure.
*/
FILE *
efopen (const char *filepath, const char *mode)
{
  /* local variables. */

  /* file pointer. */
  FILE *fp = NULL;

  /* try to open the file. */
  fp = fopen (filepath, mode);

  /* if the file is opened return a pointer to it. */
  if (fp != NULL)
    return fp;

  /* print a warning why the file can't open. */
  weprintf ("fopen(\"%.500s\") failed:", filepath);

  /* the file can't open. */
  return fp;
}
