/*
 *  `gfs-process-input-files.c'.
 *
 *  This interface deals with the processing of input files.
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
   \file gfs-process-input-files.c
   \brief This interface deals with the processing of input files.
*/

/* standard includes. */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <libintl.h>

/* basic includes. */
#include "gfs-defines.h"
#include "gfs-i18n-macros.h"
#include "gfs-typedefs.h"
#include "gfs-options.h"
#include "gfs-input-files-list.h"

/* enumeration constants. */

/*!
   \brief Constants used from the interface.

   This anonymous enumeration is used from the
   interface in order to specify some constants.
*/
enum
{
  MAX_LINE = 1024 * 1024 /*!< Max line characters (1Mbyte). */
};

/* function prototypes. */
BOOL process_input_files (INPUT_FILES * listp, OPTIONS * cop);
BOOL process_input_file (FILE * input, OPTIONS * cop);
static char *strlwr (char *str);

/* functions. */

/*!
   \fn BOOL process_input_files (INPUT_FILES *, OPTIONS *)

   \brief A function that process the linked list input files.

   This function process the linked list input files (`listp'). For each
   input file, reads data (line by line) and checks if the current line
   matches to the pattern that user has given. Also, this function keeps
   in mind all the command line arguments (`cop'). At the end, if there
   is no match found it returns `true'. Otherwise, it returns `false'.

   \param listp a pointer to a `INPUT_FILES' data structure.
   \param cop a pointer to a `OPTIONS' data structure.

   \return A `BOOL' enumeration value (`false', `true').
*/
BOOL
process_input_files (INPUT_FILES * listp, OPTIONS * cop)
{
  /* externs. */

  /* variable externs. */
  extern cstring show_max_matches;

  /* function externs. */
  extern FILE *efopen (const char *, const char *);

  /* local variables. */

  /* current line of chars within a file. */
  char data_line_init[MAX_LINE] = { '\0' };
  char data_line_case[MAX_LINE] = { '\0' };

  /* do we have at least one match? */
  BOOL found_match = false;

  /* current line in the input file. */
  register ulong curr_line = 0L;

  /* number of matches in the input file. */
  register ulong num_match = 0L;

  /* if user wants case insensitive string search. */
  if (cop->ignore_case)
    strlwr (cop->pattern);

  /* process input files. */

  /* walk through the input files linked list. */
  while (listp != NULL)
    {
      if ((listp->ptr = efopen (listp->path, "r")) == NULL)
        {
          /* move to the next list node. */
          listp = listp->next;
          continue;
        }

      /* if verbose option is enabled 
         print now the input file path. */
      if (cop->verbose)
        fprintf (stdout, " * [%s]%s", listp->path, NEW_LINE);

      /* start fetching lines from file until EOF found. */
      while (fgets (data_line_init, MAX_LINE, listp->ptr) != NULL)
        {
          /* get current line number. */
          ++curr_line;

          /* user wants case insensitive keep
             a lowercase version of the line. */
          if (cop->ignore_case)
            strlwr (strcpy (data_line_case, data_line_init));

          /* if user wants to display the lines
             that do not match with the pattern. */
          if (cop->reverse_match)
            {
              /* if user wants to ignore case distinctions. */
              if (cop->ignore_case)
                {
                  if (strstr (data_line_case, cop->pattern) == NULL)
                    {
                      /* if verbose option is enabled. */
                      if (cop->verbose)
                        {
                          /* print only when we are in the first line. */
                          if (!num_match)
                            fprintf (stdout, "%s", NEW_LINE);

                          /* print tab space. */
                          fprintf (stdout, "%s", TAB_SPACE);
                        }

                      /* print the filepath. */
                      if (!cop->verbose)
                        fprintf (stdout, "%s:", listp->path);

                      /* user wants to print the line number. */
                      if (cop->line_number)
                        fprintf (stdout, "%lu:", curr_line);

                      /* print the data line. */
                      fprintf (stdout, "%s", data_line_init);

                      /* increase the cnt of max
                         matches within the file. */
                      ++num_match;

                      /* this is for informing the caller
                         that at least one match occurred. */
                      found_match = true;
                    }
                }
              else
                {
                  if (strstr (data_line_init, cop->pattern) == NULL)
                    {
                      /* if verbose option is enabled. */
                      if (cop->verbose)
                        {
                          /* print only when we are in the first line. */
                          if (!num_match)
                            fprintf (stdout, "%s", NEW_LINE);

                          /* print tab space. */
                          fprintf (stdout, "%s", TAB_SPACE);
                        }

                      /* print the filepath. */
                      if (!cop->verbose)
                        fprintf (stdout, "%s:", listp->path);

                      /* user wants to print the line number. */
                      if (cop->line_number)
                        fprintf (stdout, "%lu:", curr_line);

                      /* print the data line. */
                      fprintf (stdout, "%s", data_line_init);

                      /* increase the cnt of max
                         matches within the file. */
                      ++num_match;

                      /* this is for informing the caller
                         that at least one match occurred. */
                      found_match = true;
                    }
                }
            }
          /* otherwise, print the line
             that matches with pattern. */
          else
            {
              /* if user wants to ignore case distinctions. */
              if (cop->ignore_case)
                {
                  if (strstr (data_line_case, cop->pattern) != NULL)
                    {
                      /* if verbose option is enabled. */
                      if (cop->verbose)
                        {
                          /* print only when we are in the first line. */
                          if (!num_match)
                            fprintf (stdout, "%s", NEW_LINE);

                          /* print tab space. */
                          fprintf (stdout, "%s", TAB_SPACE);
                        }

                      /* print the filepath. */
                      if (!cop->verbose)
                        fprintf (stdout, "%s:", listp->path);

                      /* user wants to print the line number. */
                      if (cop->line_number)
                        fprintf (stdout, "%lu:", curr_line);

                      /* print the data line. */
                      fprintf (stdout, "%s", data_line_init);

                      /* increase the cnt of max
                         matches within the file. */
                      ++num_match;

                      /* this is for informing the caller
                         that at least one match occurred. */
                      found_match = true;
                    }
                }
              else
                {
                  if (strstr (data_line_init, cop->pattern) != NULL)
                    {
                      /* if verbose option is enabled. */
                      if (cop->verbose)
                        {
                          /* print only when we are in the first line. */
                          if (!num_match)
                            fprintf (stdout, "%s", NEW_LINE);

                          /* print tab space. */
                          fprintf (stdout, "%s", TAB_SPACE);
                        }

                      /* print the filepath. */
                      if (!cop->verbose)
                        fprintf (stdout, "%s:", listp->path);

                      /* user wants to print the line number. */
                      if (cop->line_number)
                        fprintf (stdout, "%lu:", curr_line);

                      /* print the data line. */
                      fprintf (stdout, "%s", data_line_init);

                      /* increase the cnt of max
                         matches within the file. */
                      ++num_match;

                      /* this is for informing the caller
                         that at least one match occurred. */
                      found_match = true;
                    }
                }
            }
        }

      /* now print a newline only if at least one
         match found and this isn't the last file. */
      if (cop->verbose && num_match)
        if (listp->next != NULL)
          fprintf (stdout, "%s", NEW_LINE);

      /* if user wants to print the number of matches. */
      if (cop->max_matches && num_match)
        {
          /* if verbose option is enabled
             and this is the last file. */
          if (cop->verbose && (listp->next == NULL))
            fprintf (stdout, "%s", NEW_LINE);

          /* if verbose option is enabled. */
          if (cop->verbose)
            fprintf (stdout, "%s", "   ");

          fprintf (stdout, "%s %lu.%s", _(show_max_matches), num_match,
                   NEW_LINE);

          /* if verbose option is enabled
             and this isn't the last file. */
          if (cop->verbose && (listp->next != NULL))
            fprintf (stdout, "%s", NEW_LINE);
        }

      /* zero counters. */
      curr_line = num_match = 0L;

      /* close input file pointer. */
      if (listp->ptr != NULL)
        fclose (listp->ptr);

      /* move to the next list node. */
      listp = listp->next;
    }

  /* return status to the caller. */
  return found_match;
}

/*!
   \fn BOOL process_input_file (FILE *, OPTIONS *)

   \brief A function that process the data from an input stream.

   This function process the `input' stream. It reads data (line by
   line) and checks if the current line matches to the pattern that
   user has given. Also, it keeps in mind all the command line args
   (`cop'). At the end, if there isn't any match found it returns
   `true'. Otherwise, it returns `false'.

   \param input a pointer to a `FILE' data structure.
   \param cop a pointer to a `OPTIONS' data structure.

   \return A `BOOL' enumeration value (`false', `true').
*/
BOOL
process_input_file (FILE * input, OPTIONS * cop)
{
  /* externs. */

  /* variable externs. */
  extern cstring show_max_matches;

  /* local variables. */

  /* current line of chars within a file. */
  char data_line_init[MAX_LINE] = { '\0' };
  char data_line_case[MAX_LINE] = { '\0' };

  /* do we have at least one match? */
  BOOL found_match = false;

  /* current line in the input file. */
  register ulong curr_line = 0L;

  /* number of matches in the input file. */
  register ulong num_match = 0L;

  /* if user wants case insensitive string search. */
  if (cop->ignore_case)
    strlwr (cop->pattern);

  /* process input. */

  /* start fetching lines from file until EOF found. */
  while (fgets (data_line_init, MAX_LINE, input) != NULL)
    {
      /* get current line number. */
      ++curr_line;

      /* user wants case insensitive keep
         a lowercase version of the line. */
      if (cop->ignore_case)
        strlwr (strcpy (data_line_case, data_line_init));

      /* if user wants to display the lines
         that do not match with the pattern. */
      if (cop->reverse_match)
        {
          /* if user wants to ignore case distinctions. */
          if (cop->ignore_case)
            {
              if (strstr (data_line_case, cop->pattern) == NULL)
                {
                  /* user wants to print the line number. */
                  if (cop->line_number)
                    fprintf (stdout, "%lu:", curr_line);

                  /* print the data line. */
                  fprintf (stdout, "%s", data_line_init);

                  /* increase the cnt of max
                     matches within the file. */
                  ++num_match;

                  /* this is for informing the caller
                     that at least one match occurred. */
                  found_match = true;
                }
            }
          else
            {
              if (strstr (data_line_init, cop->pattern) == NULL)
                {
                  /* user wants to print the line number. */
                  if (cop->line_number)
                    fprintf (stdout, "%lu:", curr_line);

                  /* print the data line. */
                  fprintf (stdout, "%s", data_line_init);

                  /* increase the cnt of max
                     matches within the file. */
                  ++num_match;

                  /* this is for informing the caller
                     that at least one match occurred. */
                  found_match = true;
                }
            }
        }
      /* otherwise, print the line
         that matches with pattern. */
      else
        {
          /* if user wants to ignore case distinctions. */
          if (cop->ignore_case)
            {
              if (strstr (data_line_case, cop->pattern) != NULL)
                {
                  /* user wants to print the line number. */
                  if (cop->line_number)
                    fprintf (stdout, "%lu:", curr_line);

                  /* print the data line. */
                  fprintf (stdout, "%s", data_line_init);

                  /* increase the cnt of max
                     matches within the file. */
                  ++num_match;

                  /* this is for informing the caller
                     that at least one match occurred. */
                  found_match = true;
                }
            }
          else
            {
              if (strstr (data_line_init, cop->pattern) != NULL)
                {
                  /* user wants to print the line number. */
                  if (cop->line_number)
                    fprintf (stdout, "%lu:", curr_line);

                  /* print the data line. */
                  fprintf (stdout, "%s", data_line_init);

                  /* increase the cnt of max
                     matches within the file. */
                  ++num_match;

                  /* this is for informing the caller
                     that at least one match occurred. */
                  found_match = true;
                }
            }
        }
    }

  /* print only if at least one match found and
     user wants to print the number of matches. */
  if (cop->max_matches && num_match)
    fprintf (stdout, "%s %lu.%s", _(show_max_matches), num_match, NEW_LINE);

  /* return status to the caller. */
  return found_match;
}

/*!
   \fn static char * strlwr (char *)

   \brief A function that gets a string and returns it in lowercase.

   This function tries to lowercase each character of `s'
   string. So, creates a new string with the new version
   of lowercase characters. After that, it returns it.

   \param str a pointer to a character.

   \return a pointer to a character.
*/
static char *
strlwr (char *str)
{
  /* if the string is not empty. */
  if (str != NULL)
    {
      char *p;

      /* try to lowercase all chars. */
      for (p = str; *p != '\0'; p++)
        *p = (char) tolower (*p);
    }

  /* return the string. */
  return str;
}
