/*
 *  `gfs-defines.h'.
 *
 *  This header contains some global defines.
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
   \file gfs-defines.h
   \brief This header contains some global defines.
*/

/* global defines. */

/*!
   \def EXIT_SUCCESS
   \brief Exit success code.

   This define is used from the program in
   order to return a success exit status.
*/
#ifndef EXIT_SUCCESS
# define EXIT_SUCCESS 0
#endif /* not EXIT_SUCCESS. */

/*!
   \def EXIT_FAILURE
   \brief Exit failure code.

   This define is used from the program in
   order to return a failure exit status.
*/
#ifndef EXIT_FAILURE
# define EXIT_FAILURE 1
#endif /* not EXIT_FAILURE. */

/*!
   \def EXIT_ERROR
   \brief Exit error code.

   This define is used from the program in
   order to return an error exit status.
*/
#ifndef EXIT_ERROR
# define EXIT_ERROR 2
#endif /* not EXIT_ERROR. */

/*!
   \def NEW_LINE
   \brief New line character.

   This define is used from the program in
   order to print the new line character.
*/
#define NEW_LINE  "\n"

/*!
   \def TAB_SPACE
   \brief Tab space character.

   This define is used from the program in
   order to print the tab space character.
*/
#define TAB_SPACE "\t"
