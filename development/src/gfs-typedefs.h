/*
 *  `gfs-typedefs.h'.
 *
 *  This header contains some global typedefs and data types.
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
   \file gfs-typedefs.h
   \brief This header contains some global typedefs and data types.
*/

/* data types. */

/*
 * enumeration data types.
 */

/*!
   \enum boolT
   \brief Boolean enumeration data type.

   This enumeration data type is an implementation of a
   boolean data type. The program can use it, in order
   to declare variables with `true' or `false' values.
*/
enum boolT
{
  false,                        /*!< It means that something is false. */
  true                          /*!< It means that something is true. */
};

/* type definitions. */

/*
 * enumeration type definitions.
 */

/*!
   \typedef BOOL
   \brief Boolean enumeration type definition.

   This type definition is a synonym
   for the boolean enumeration type.
*/
typedef enum boolT BOOL;

/*
 * unsigned type definitions.
 */

/*!
   \typedef ushort
   \brief An unsigned short integer.
*/
typedef unsigned short ushort;

/*!
   \typedef ulong
   \brief An unsigned long integer.
*/
typedef unsigned long ulong;

/*!
   \typedef uint
   \brief An unsigned integer.
*/
typedef unsigned int uint;

/*!
   \typedef uchar
   \brief An unsigned character.
*/
typedef unsigned char uchar;

/*
 * constant type definitions.
 */

/*!
   \typedef cint
   \brief A constant integer.
*/
typedef const int cint;

/*!
   \typedef cstring
   \brief A constant pointer to a constant character.
*/
typedef const char *const cstring;
