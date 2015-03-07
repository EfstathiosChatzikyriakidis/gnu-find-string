/*
 *  `gfs-parse-options.c'.
 *
 *  This interface deals with the parsing of command line options.
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
   \file gfs-parse-options.c
   \brief This interface deals with the parsing of command line options.
*/

/* standard includes. */
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

/* basic includes. */
#include "gfs-defines.h"
#include "gfs-typedefs.h"
#include "gfs-options.h"

/* function prototypes. */
OPTIONS *parse_options (OPTIONS * cop, cint argc, char *argv[]);
static OPTIONS *new_options (void);

/* functions. */

/*!
   \fn OPTIONS * parse_options (OPTIONS *, cint, char *[])

   \brief A function that parses the command line arguments.

   This function parses the command line arguments (by using `argc' and
   `argv'). During this procecure both it initializes and configures an
   `OPTIONS' data structure (`cop') according to the user preferences.
   At the end, it returns the `OPTIONS' structure.

   \param cop a pointer to a `OPTIONS' data structure.
   \param argc a constant integer value.
   \param argv an array of pointers to a character.

   \return A pointer to a `OPTIONS' data structure.
*/
OPTIONS *
parse_options (OPTIONS * cop, cint argc, char *argv[])
{
  /* externs. */

  /* function externs. */
  extern char *estrdup (const char *);
  extern void print_usage (FILE *, cint);
  extern void print_version (FILE *, cint);
  extern void print_author (FILE *, cint);
  extern void print_license (FILE *, cint);

  /* next option in command line. */
  register int next_option;

  /* short options. */
  cstring short_options = "rmnie:v";

  /* long options. */
  const struct option long_options[] = {
    {"reverse-match", 0, NULL, 'r'},
    {"max-matches", 0, NULL, 'm'},
    {"line-number", 0, NULL, 'n'},
    {"ignore-case", 0, NULL, 'i'},
    {"pattern", 1, NULL, 'e'},
    {"verbose", 0, NULL, 'v'},
    {"copyleft", 0, NULL, 'c'},
    {"author", 0, NULL, 'a'},
    {"version", 0, NULL, 'V'},
    {"help", 0, NULL, 'h'},
    {"usage", 0, NULL, 'u'},
    {NULL, 0, NULL, 0}
  };

  /* create and initialize 
     options data structure. */
  cop = new_options ();

  /* start scanning. */
  do
    {
      /* get next option. */
      next_option =
        getopt_long (argc, argv, short_options, long_options, NULL);

      switch (next_option)
        {
          /* print usage and exit. */
        case 'h':
        case 'u':
          print_usage (stdout, EXIT_SUCCESS);

          /* print version and exit. */
        case 'V':
          print_version (stdout, EXIT_SUCCESS);

          /* print author and exit. */
        case 'a':
          print_author (stdout, EXIT_SUCCESS);

          /* print license and exit. */
        case 'c':
          print_license (stdout, EXIT_SUCCESS);

          /* invert the sence of matching. */
        case 'r':
          cop->reverse_match = true;
          break;

          /* show the max number of matches. */
        case 'm':
          cop->max_matches = true;
          break;

          /* show each line of output with the line number. */
        case 'n':
          cop->line_number = true;
          break;

          /* ignore case distinctions. */
        case 'i':
          cop->ignore_case = true;
          break;

          /* input matching pattern. */
        case 'e':
          cop->pattern = estrdup (optarg);
          break;

          /* explain what is being done. */
        case 'v':
          cop->verbose = true;
          break;

          /* unknown option. */
        case '?':
          print_usage (stderr, EXIT_ERROR);

          /* eop. */
        case -1:
          break;

        default:
          abort ();
        }
    }
  while (next_option != -1);

  /* return the options pointer. */
  return cop;
}

/*!
   \fn static OPTIONS * new_options (void)

   \brief A function that returns a new `OPTIONS' data structure.

   This function allocates enough memory for a new `OPTIONS'
   data structure. Then initializes it to an initial state
   and returns it.

   \return A pointer to a `OPTIONS' data structure.
*/
static OPTIONS *
new_options (void)
{
  /* externs. */

  /* function externs. */
  extern void *emalloc (size_t);

  OPTIONS *newp;

  /* allocate enough memory space. */
  newp = (OPTIONS *) emalloc (sizeof (OPTIONS));

  /* init options to a default state. */
  newp->verbose = false;
  newp->reverse_match = false;
  newp->max_matches = false;
  newp->line_number = false;
  newp->ignore_case = false;
  newp->pattern = NULL;

  /* return the options pointer. */
  return newp;
}
