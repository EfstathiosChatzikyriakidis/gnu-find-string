/*
 *  `gfs-messages.c'.
 *
 *  This interface contains all the string messages.
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
   \file gfs-messages.c
   \brief This interface contains all the string messages.
*/

/* standard includes. */
#include <stdio.h>

/* basic includes. */
#include "gfs-i18n-macros.h"
#include "gfs-typedefs.h"

/*** informative messages. ***/

/*!
   \var program_author
   \brief The author of the program.
*/
cstring program_author = N_("Written by Efstathios Chatzikyriakidis.");

/*!
   \var program_version
   \brief The program name and its version number.
*/
cstring program_version = "GNU find string 1.0";

/*!
   \var send_bugs_mail
   \brief The email address for reporting any bugs.
*/
cstring send_bugs_mail = N_("Report bugs to <bug-gnu-fs@gnu.org>");

/*!
   \var license_part_a
   \brief GNU General Public License (part a).
*/
cstring license_part_a =
 "Copyright (C) 2008  Efstathios Chatzikyriakidis (stathis.chatzikyriakidis@gmail.com). \n"
 "                                                                                      \n"
 "This program is free software: you can redistribute it and/or modify                  \n"
 "it under the terms of the GNU General Public License as published by                  \n"
 "the Free Software Foundation, either version 3 of the License, or                     \n";

/*!
   \var license_part_b
   \brief GNU General Public License (part b).
*/
cstring license_part_b =
 "(at your option) any later version.                             \n"
 "                                                                \n"
 "This program is distributed in the hope that it will be useful, \n"
 "but WITHOUT ANY WARRANTY; without even the implied warranty of  \n"
 "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the    \n";

/*!
   \var license_part_c
   \brief GNU General Public License (part c).
*/
cstring license_part_c =
 "GNU General Public License for more details.                         \n"
 "                                                                     \n"
 "You should have received a copy of the GNU General Public License    \n"
 "along with this program. If not, see <http://www.gnu.org/licenses/>. \n";

/* usage/help information. */

/*!
   \var usage_specify_pattern
   \brief A short usage informative message.
*/
cstring usage_specify_pattern = N_(
 "You must specify a search pattern. See `--help' for details.");

/*!
   \var usage_part_a
   \brief A long usage informative message (part a).
*/
cstring usage_part_a = N_("Usage:");

/*!
   \var usage_part_b
   \brief A long usage informative message (part b).
*/
cstring usage_part_b = N_("[OPTIONS] -e PATTERN [FILE...]");

/*!
   \var usage_part_c
   \brief A long usage informative message (part c).
*/
cstring usage_part_c = N_(
 "  -r, --reverse-match     Select and show non-matching lines. \n"
 "  -m, --max-matches       Show the max number of matches.     \n"
 "  -n, --line-number       Prefix each line with a number.     \n"
 "  -i, --ignore-case       Ignore case distinctions.           \n"
 "  -e, --pattern=PATTERN   Input matching pattern.             \n");

/*!
   \var usage_part_d
   \brief A long usage informative message (part d).
*/
cstring usage_part_d = N_(
 "  -v, --verbose           Explain what is being done.         \n"
 "                                                              \n"
 "      --help, --usage     Display this help and exit.         \n"
 "      --version           Print version information and exit. \n"
 "      --author            Print author information and exit.  \n"
 "      --copyleft          Print a short version of GNU/GPL.   \n");

/*** verbose messages. ***/

/* input files process procedure. */

/*!
   \var show_input_files
   \brief A verbose input files message.
*/
cstring show_input_files  = N_("Input files:");

/*!
   \var show_search_files
   \brief A message for search files.
*/
cstring show_search_files = N_("Search files:");

/*!
   \var show_max_matches
   \brief A message for number of matches.
*/
cstring show_max_matches  = N_("Number of matches:");
