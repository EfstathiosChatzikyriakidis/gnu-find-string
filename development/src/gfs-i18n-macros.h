/*
 *  `gfs-i18n-macros.h'.
 *
 *  This header contains internationalization facility macros.
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
   \file gfs-i18n-macros.h
   \brief This header contains i18n facility macros.
*/

/* i18n support macros. */

/* the following macros are used for gettext support. */

/*!
   \def _()

   This define is used from the program
   in order to support the i18n facility.
*/
#define _(String) (char *) gettext(String)

/*!
   \def gettext_noop()

   This define is used from the program
   in order to support the i18n facility.
*/
#define gettext_noop(String) (String)

/*!
   \def N_()

   This define is used from the program
   in order to support the i18n facility.
*/
#define N_(String) gettext_noop(String)
