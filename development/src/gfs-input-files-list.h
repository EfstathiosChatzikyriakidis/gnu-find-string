/*
 *  `gfs-input-files-list.h'.
 *
 *  This header contains input files structs, enums, typedefs.
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
   \file gfs-input-files-list.h
   \brief This header contains input files structs, enums, typedefs.
*/

/*
 * enumeration data types.
 */

/*!
   \enum file_infoT
   \brief Input file info enumeration data type.

   This enumeration data type is used from the program in
   order to specify the type or the state of an input file.
*/
enum file_infoT
{
  /* possible types. */
  f_regular,                        /*!< the input file is a regular file. */
  f_directory,                        /*!< the input file is a directory.    */
  f_block,                        /*!< the input file is a block device. */
  f_character,                        /*!< the input file is a char device.  */
  f_fifo,                        /*!< the input file is a named pipe.   */
  f_socket,                        /*!< the input file is a net socket.   */
  f_ascii,                        /*!< the input file is an ascii file.  */
  f_binary,                        /*!< the input file is a binary file.  */
  f_link,                        /*!< the input file is a link.         */

  /* possible states. */
  f_inaccessible,                /*!< we cannot access the input file. */
  f_accessible,                        /*!< we can access the input file.    */
  f_unknown,                        /*!< the input file does not exist.   */
  f_io_error                        /*!< an input/output error occurred.  */
};

/*
 * structure data types.
 */

/*!
   \struct input_fileT
   \brief Input file node data structure.

   This data structure is used for the
   input files linked list as a node.
*/
struct input_fileT
{
  /*!
     \var ptr
     \brief Input file pointer.

     This is a pointer to an input file. The program
     uses this pointer in order to open and read the
     contents of an input file.
   */
  FILE *ptr;

  /*!
     \var path
     \brief Input file path.

     This is a pointer to a file path. The program uses
     this file path in order to open an input file. Also,
     in some places it is printed.
   */
  char *path;

  /*!
     \var next
     \brief Next input file node.

     This is a pointer to the next input
     file in the input files linked list.
   */
  struct input_fileT *next;
};

/*
 * type definitions.
 */

/*!
   \typedef FILE_INFO
   \brief Input file info enumeration type definition.

   This type definition is a synonym for
   the input file info enumeration type.
*/
typedef enum file_infoT FILE_INFO;

/*!
   \typedef INPUT_FILE
   \brief Input file data structure type definition.

   This type definition is a synonym
   for the input file data structure.

   `INPUT_FILE' (seems to be a node of a linked list).
*/
typedef struct input_fileT INPUT_FILE;

/*!
   \typedef INPUT_FILES
   \brief Input file data structure type definition. 

   This type definition is a synonym
   for the input file data structure.

   `INPUT_FILES' (seems to be the head of a linked list).
*/
typedef struct input_fileT INPUT_FILES;
