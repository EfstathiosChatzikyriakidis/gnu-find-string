/*
 *  `gfs' - print lines matching a pattern.
 *
 *    See Texinfo manual page for more information.
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
   \file gfs.c
   \brief Print lines matching a pattern.
*/

/* standard includes. */
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <libintl.h>

/* basic includes. */
#include "gfs-defines.h"
#include "gfs-i18n-macros.h"
#include "gfs-typedefs.h"
#include "gfs-options.h"
#include "gfs-input-files-list.h"

/* basic defines. */

/*!
   \def LOCALE_PACKAGE
   \brief Locale package name.

   This define is used from the program in
   order to specify locale's package name.
*/
#define LOCALE_PACKAGE "gfs"

/*!
   \def PROGRAM_NAME
   \brief Internal name of the program.

   This define is used from the program in
   order to set and get its internal name.
*/
#define PROGRAM_NAME "gfs"

/* global variables. */

/*!
   \var input_files_list
   \brief Input files linked list.

   This is a pointer to the input files linked list.
*/
INPUT_FILES *input_files_list = NULL;

/* functions. */

/*!
   \fn int main (int, char *[])

   \brief This is the program's main function.

   \param argc a constant integer value.
   \param argv an array of pointers to character.

   \return An integer exit status value.
*/
int
main (int argc, char *argv[])
{
  /* externs. */

  /* function externs. */
  extern OPTIONS *parse_options (OPTIONS *, cint, char *[]);
  extern INPUT_FILES *parse_input_files (INPUT_FILES *, cint, char *[]);

  extern ulong count_input_files (INPUT_FILES *);
  extern void print_input_files (FILE *, INPUT_FILES *);
  extern void free_input_files (INPUT_FILES *);

  extern BOOL process_input_files (INPUT_FILES *, OPTIONS *);
  extern BOOL process_input_file (FILE *, OPTIONS *);

  extern void eprintf (char *, ...);
  extern FILE *efopen (const char *, const char *);
  extern void set_prog_name (const char *);

  /* variable externs. */
  extern cstring program_version;
  extern cstring show_input_files;
  extern cstring show_search_files;
  extern cstring usage_specify_pattern;

  /* local variables. */

  /* this is a pointer to the command's line options. */
  OPTIONS *cop = NULL;

  /* this is a pointer to the environment input file path. */
  const char *env_input = NULL;

  /* this is a pointer to the environment input file. */
  FILE *efp = NULL;

  /*
   * this is a boolean variable that deals with
   * possibility of at least one pattern match.
   */
  BOOL found_match = false;

  /*** set program name and get environment input. ***/

  /* set the internal program name. */
  set_prog_name (PROGRAM_NAME);

  /* fetch environment input file path. */
  env_input = getenv ("GFS_INPUT");

  /*** install internationalization. ***/

  /* reset the locale variables LC_*. */
  setlocale (LC_CTYPE, "");
  setlocale (LC_MESSAGES, "");

  /* bind with MO file. */
  bindtextdomain (LOCALE_PACKAGE, LOC_DIR);
  textdomain (LOCALE_PACKAGE);

  /*** manage command line options. ***/

  /* parse the command line arguments. */
  cop = parse_options (cop, argc, argv);

  /* if match pattern is empty return a short usage. */
  if (cop->pattern == NULL)
    eprintf ("%s", _(usage_specify_pattern));

  /* print verbose messages. */

  /* if verbose option is enabled
     print program's version info. */
  if (cop->verbose)
    fprintf (stdout, "%s%s", _(program_version), NEW_LINE);

  /*** manage command line input files. ***/

  /* parse the input files. */
  input_files_list = parse_input_files (input_files_list, argc, argv);

  /* print verbose messages. */

  /* if verbose option is enabled and there
     are some input files, just print them. */
  if (cop->verbose && (count_input_files (input_files_list) > 0))
    {
      fprintf (stdout, "%s%s%s", NEW_LINE, _(show_input_files), NEW_LINE);
      print_input_files (stdout, input_files_list);
      fprintf (stdout, "%s", NEW_LINE);
    }

  /*** try to open the environment input file. ***/

  /* if there are no input files. */
  if (count_input_files (input_files_list) == 0)
    /* if there is an environment input file. */
    if (env_input != NULL)
      /* try to open it and check for error. */
      if ((efp = efopen (env_input, "r")) == NULL)
        {
          /* free input files linked list. */
          free_input_files (input_files_list);

          return (EXIT_ERROR);
        }

  /*** process input data. ***/

  /* if the are any accepted input files. */
  if (count_input_files (input_files_list) > 0)
    {
      /* if verbose option is enabled. */
      if (cop->verbose)
        fprintf (stdout, "%s%s", _(show_search_files), NEW_LINE);

      /* process the input files linked list. */
      found_match = process_input_files (input_files_list, cop);
    }
  else
    /* process either environment or standard input. */
    found_match = process_input_file ((efp != NULL ? efp : stdin), cop);

  /*** free memory, close files and return status. ***/

  /* close environment input file. */
  if (efp != NULL)
    fclose (efp);

  /* free input files linked list. */
  free_input_files (input_files_list);

  /* return status to the caller. */
  return !found_match;
}
