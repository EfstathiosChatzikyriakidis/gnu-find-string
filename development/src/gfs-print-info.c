/*
 *  `gfs-print-info.c'.
 *
 *  This interface deals with the printing of useful information.
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
   \file gfs-print-info.c
   \brief This interface deals with the printing of useful information.
*/

/* standard includes. */
#include <stdio.h>
#include <stdlib.h>
#include <libintl.h>

/* basic includes. */
#include "gfs-defines.h"
#include "gfs-i18n-macros.h"
#include "gfs-typedefs.h"

/* function prototypes. */
void print_usage (FILE * stream, cint exit_code);
void print_version (FILE * stream, cint exit_code);
void print_author (FILE * stream, cint exit_code);
void print_license (FILE * stream, cint exit_code);

/* functions. */

/*!
   \fn void print_usage (FILE * stream, cint exit_code)

   \brief A function that prints usage information.

   This function prints to the output `stream' the
   usage information of the program. After that, it
   exits with `exit_code'.

   \param stream a pointer to a `FILE' data structure.
   \param exit_code a constant integer value.
*/
void
print_usage (FILE * stream, cint exit_code)
{
  /* externs. */

  /* function externs. */
  extern const char *get_prog_name (void);

  /* variable externs. */
  extern cstring usage_part_a, usage_part_b;
  extern cstring usage_part_c, usage_part_d;
  extern cstring send_bugs_mail;

  /* print usage information. */
  fprintf (stream, "%s %s", _(usage_part_a), get_prog_name ());
  fprintf (stream, " %s%s", _(usage_part_b), NEW_LINE);
  fprintf (stream, "%s%s", NEW_LINE, _(usage_part_c));
  fprintf (stream, "%s%s%s", NEW_LINE, _(usage_part_d), NEW_LINE);
  fprintf (stream, "%s%s", _(send_bugs_mail), NEW_LINE);

  /* exit the program. */
  exit (exit_code);
}

/*!
   \fn void print_version (FILE * stream, cint exit_code)

   \brief A function that prints version information.

   This function prints to the output `stream' the
   version information of the program. After that,
   it exits with `exit_code'.

   \param stream a pointer to a `FILE' data structure.
   \param exit_code a constant integer value.
*/
void
print_version (FILE * stream, cint exit_code)
{
  /* externs. */

  /* variable externs. */
  extern cstring program_version;

  /* print and exit the program. */
  fprintf (stream, "%s%s", _(program_version), NEW_LINE);
  exit (exit_code);
}

/*!
   \fn void print_author (FILE * stream, cint exit_code)

   \brief A function that prints author information.

   This function prints to the output `stream' the
   author information of the program. After that,
   it exits with `exit_code'.

   \param stream a pointer to a `FILE' data structure.
   \param exit_code a constant integer value.
*/
void
print_author (FILE * stream, cint exit_code)
{
  /* externs. */

  /* variable externs. */
  extern cstring program_author;

  /* print and exit the program. */
  fprintf (stream, "%s%s", _(program_author), NEW_LINE);
  exit (exit_code);
}

/*!
   \fn void print_license (FILE * stream, cint exit_code)

   \brief A function that prints license information.

   This function prints to the output `stream' the
   license information of the program. After that,
   it exits with `exit_code'.

   \param stream a pointer to a `FILE' data structure.
   \param exit_code a constant integer value.
*/
void
print_license (FILE * stream, cint exit_code)
{
  /* externs. */

  /* variable externs. */
  extern cstring license_part_a;
  extern cstring license_part_b;
  extern cstring license_part_c;

  /* print license info. */
  fprintf (stream, "%s", _(license_part_a));
  fprintf (stream, "%s", _(license_part_b));
  fprintf (stream, "%s", _(license_part_c));

  /* exit the program. */
  exit (exit_code);
}
