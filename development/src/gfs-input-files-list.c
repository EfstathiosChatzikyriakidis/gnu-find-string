/*
 *  `gfs-input-files-list.c'.
 *
 *  This interface deals with the input files linked list.
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
   \file gfs-input-files-list.c
   \brief This interface deals with the input files linked list.
*/

/* standard includes. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* basic includes. */
#include "gfs-defines.h"
#include "gfs-typedefs.h"
#include "gfs-input-files-list.h"

/* function prototypes. */
INPUT_FILE *new_input_file (const char *filepath);
INPUT_FILE *add_input_file (INPUT_FILE * listp, INPUT_FILE * newp);

void print_input_files (FILE * stream, INPUT_FILES * listp);
void free_input_files (INPUT_FILES * listp);

BOOL input_file_exists (INPUT_FILES * listp, cstring filepath);
ulong count_input_files (INPUT_FILES * listp);

/* functions. */

/*!
   \fn INPUT_FILE * new_input_file (const char *)

   \brief A function that creates a new node for the input files linked list.

   This function allocates enough memory for a new `INPUT_FILE' data
   structure and then initializes it with `filepath'. After that, it
   returns that new `INPUT_FILE' data structure.

   \param filepath a pointer to a constant character.

   \return A pointer to a `INPUT_FILE' data structure.
*/
INPUT_FILE *
new_input_file (const char *filepath)
{
  /* externs. */

  /* function externs. */
  extern char *estrdup (const char *);
  extern void *emalloc (size_t);

  INPUT_FILE *newp;

  /* allocate enough memory space. */
  newp = (INPUT_FILE *) emalloc (sizeof (INPUT_FILE));

  /* init the node list and store the string. */
  newp->ptr = NULL;
  newp->path = estrdup (filepath);
  newp->next = NULL;

  /* return the new node item. */
  return newp;
}

/*!
   \fn INPUT_FILE * add_input_file (INPUT_FILE *, INPUT_FILE *)

   \brief A function that adds a new node to the input files linked list.

   This function adds to the end of the linked list `listp'
   the node `newp' and then returns the head of the linked
   list `listp'.

   \param listp a pointer to a `INPUT_FILE' data structure.
   \param newp a pointer to a `INPUT_FILE' data structure.

   \return A pointer to a `INPUT_FILE' data structure.
*/
INPUT_FILE *
add_input_file (INPUT_FILE * listp, INPUT_FILE * newp)
{
  INPUT_FILE *p;

  /* if the list is empty. */
  if (listp == NULL)
    return newp;

  /* go to the end of the list. */
  for (p = listp; p->next != NULL; p = p->next)
    continue;

  /* add to the end of the list `newp'. */
  p->next = newp;

  /* return the list. */
  return listp;
}

/*!
   \fn void print_input_files (FILE *, INPUT_FILES *)

   \brief A function that prints the linked list input files.

   This function tries to print all the input files of the
   list `listp' to the output `stream'. When it reaches the
   end of the linked list it returns.

   \param stream a pointer to a `FILE' data structure.
   \param listp a pointer to a `INPUT_FILES' data structure.
*/
void
print_input_files (FILE * stream, INPUT_FILES * listp)
{
  /* walk through the linked list. */
  while (listp != NULL)
    {
      /* print the input file path. */
      fprintf (stream, " * [%s]%s", listp->path, NEW_LINE);

      /* move to the next list node. */
      listp = listp->next;
    }
}

/*!
   \fn void free_input_files (INPUT_FILES *)

   \brief A function that deallocates the input files linked list.

   This function tries to deallocate all the nodes from the
   list `listp'. When all nodes are deallocated it returns.

   \param listp a pointer to a `INPUT_FILES' data structure.
*/
void
free_input_files (INPUT_FILES * listp)
{
  /* walk through the linked list. */
  while (listp != NULL)
    {
      INPUT_FILE *nextp = listp->next;
      free (listp->path);
      free (listp);
      listp = nextp;
    }
}

/*!
   \fn BOOL input_file_exists (INPUT_FILES *, cstring)

   \brief A function that look for an entry in the input files linked list.

   This function parses all the input files linked list (`listp') and
   checks if there is a previous entry of `filepath'. If it does, it
   returns `true'. Otherwise, it returns `false'.

   \param listp a pointer to a `INPUT_FILES' data structure.
   \param filepath a `cstring' type definition.

   \return A `BOOL' enumeration value (`false', `true').
*/
BOOL
input_file_exists (INPUT_FILES * listp, cstring filepath)
{
  /* walk through the linked list. */
  while (listp != NULL)
    {
      /* has already occurred. */
      if (!strcmp (filepath, listp->path))
        return true;

      /* move to the next list node. */
      listp = listp->next;
    }

  /* it is the first occurrence. */
  return false;
}

/*!
   \fn ulong count_input_files (INPUT_FILES *)

   \brief A function that counts the length of the input files linked list.
   \param listp a pointer to a `INPUT_FILES' data structure.

   \return An unsigned long integer.
*/
ulong
count_input_files (INPUT_FILES * listp)
{
  /* the sum of nodes in the list. */
  register ulong cnt;

  /* count the nodes of the list. */
  for (cnt = 0L; listp != NULL; cnt++)
    listp = listp->next;

  /* return nodes list counter. */
  return cnt;
}
