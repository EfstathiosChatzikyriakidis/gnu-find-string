/*
 *  `gfs-options.h'.
 *
 *  This header contains command line options struct and typedef.
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
   \file gfs-options.h
   \brief This header contains command line options struct and typedef.
*/

/*
 * structure data types.
 */

/*!
   \struct optionsT
   \brief Command line options data structure.

   This data structure is used from the program in
   order to keep, organize the command line options.
   Also, is used when we want to check the options.
*/
struct optionsT
{
  /*!
     \var verbose
     \brief Print verbose messages variable.

     This variable is used in order
     to explain what is being done.
   */
  BOOL verbose;

  /*!
     \var reverse_match
     \brief Reverse matching variable.

     This variable is used in order
     to invert the sence of matching.
   */
  BOOL reverse_match;

  /*!
     \var max_matches
     \brief Print max matches variable.

     This variable is used in order to 
     output the max number of matches.
   */
  BOOL max_matches;

  /*!
     \var line_number
     \brief Print line number variable.

     This variable is used in order to prefix
     each line of output with the line number.
   */
  BOOL line_number;

  /*!
     \var ignore_case;
     \brief Ignore case distinctions variable.

     This variable is used in order
     to ignore case distinctions.
   */
  BOOL ignore_case;

  /*!
     \var pattern
     \brief Input pattern variable.

     This variable is used in order
     to input the matching pattern.
   */
  char *pattern;
};

/*
 * type definitions.
 */

/*!
   \typedef OPTIONS
   \brief Command line options data structure type definition.

   This type definition is a synonym for
   the command line options data structure.
*/
typedef struct optionsT OPTIONS;
