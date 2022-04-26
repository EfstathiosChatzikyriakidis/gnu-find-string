/*
 *  `gfs-handle-program-name.c'.
 *
 *  This interface deals with the handling of the program's name.
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
   \file gfs-handle-program-name.c
   \brief This interface deals with the handling of the program's name.
*/

/* standard includes. */
#include <stdio.h>

/* static variables. */

/*! 
   \var name
   \brief Program's name.

   A variable that points to the name of the program.
*/
static char *name = NULL;

/* function prototypes. */
const char *get_prog_name (void);
void set_prog_name (const char *new_name);

/* functions. */

/*!
   \fn const char * get_prog_name (void)

   \brief A function that gets the name of the program.
   \return A pointer to a constant character.
*/
const char *
get_prog_name (void)
{
  /* return the name of the program. */
  return name;
}

/*!
   \fn void set_prog_name (const char *)

   \brief A function that sets a new name for the program.
   \param new_name pointer to a constant character.
*/
void
set_prog_name (const char *new_name)
{
  /* externs. */

  /* function externs. */
  extern char *estrdup (const char *);

  /* store the new name of the program. */
  name = estrdup (new_name);
}
