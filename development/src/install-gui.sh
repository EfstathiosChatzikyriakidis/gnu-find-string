#!/bin/sh

#######
#
#  `install-gui.sh'.
#
#  This file is the gui installation program of GNU fs.
#
#  Copyright (C) 2008  Efstathios Chatzikyriakidis (stathis.chatzikyriakidis@gmail.com)
#
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program. If not, see <http://www.gnu.org/licenses/>.
#
#######

### string messages. ###

install_welcome="Welcome to the installation program."
install_exit="Exit from the installation program."

select_from_list="Select an option from the list."
gnu_gpl="GNU General Public License Information."
argument_errors="Insufficient arguments."
path_directory="Path directory."

must_be_root="You must be root to run the installation program."
must_install_program="You must install first the following program :"
must_select_option="You must select an option."
must_input_value="You must input a value to continue."

progress_window="Progress Window."
info_window="Information Window."
warning_window="Warning Window."
error_window="Error Window."

proc_done="Procedure done."
proc_error="Procedure error."

### functions. ###

##
# name: print_error.
#
# description: prints an error message and exits.
#
# argument: $1 -> message to print.
##
print_error () 
{
    if [ $# -lt 1 ] ; then
        print_error "$argument_errors"
        return 1
    fi

    zenity --error --title "$error_window" --text "$1"
    exit 1
}

##
# name: print_warning.
#
# description: prints a warning message and
#              exits only if user wants to.
#
# argument: $1 -> message to print.
##
print_warning () 
{
    if [ $# -lt 1 ] ; then
        print_error "$argument_errors"
        return 1
    fi

    zenity --warning --title "$warning_window" --text "$1"
    if [ $? -eq 1 ]; then
        exit 1
    fi

    return 0
}

##
# name: print_file.
#
# description: prints the contents of a text file.
#
# argument: $1 -> file to print.
##
print_file () 
{ 
    if [ $# -lt 1 ] ; then
        print_error "$argument_errors"
        return 1
    fi

    zenity --text-info --title "$gnu_gpl" \
    --width 600 --height 500 --filename="$1"
    return 0
}

##
# name: print_info.
#
# description: prints an information message.
#
# argument: $1 -> message to print.
##
print_info () 
{
    if [ $# -lt 1 ] ; then
        print_error "$argument_errors"
    fi

    zenity --info --title "$info_window" --text "$1"
    return 0
}

##
# name: get_uid.
#
# description: outputs a numeric user id.
#
# argument: $1 -> a user name (optional).
##
get_uid () 
{
    id -u $1
}

##
# name: is_user_root.
#
# description: returns true (0) if the user's UID=0.
#
# argument: $1 -> a user name (optional).
##
is_user_root () 
{
    if [ "`get_uid $1`" -eq 0 ] ; then 
        return 0
    fi
    return 1
}

##
# name: app_exists.
#
# description: return true (0) if an application exists.
#
# argument: $1 -> application to search for.
##
app_exists ()
{
    if [ $# -lt 1 ] ; then
        print_error "$argument_errors"
        return 1
    fi

    type "$1" > /dev/null 2>&1

    if [ $? -eq 0 ] ; then
        return 1
    fi

    return 0
}

### main program. ###

# check to see if the user has superuser privileges.
is_user_root
if [ $? -eq 0 ]; then

    # test for missing programs.

    app_exists zenity
    if [ $? -eq 0 ]; then
        print_error "$must_install_program zenity."
    fi

    app_exists make
    if [ $? -eq 0 ]; then
        print_error "$must_install_program make."
    fi

    app_exists gcc
    if [ $? -eq 0 ]; then
        print_error "$must_install_program gcc."
    fi

    # select what kind of procedure you want to be done.
    OPTION=`zenity --list --height 300 --width 350 --text "Select \
    which procedure you want to do." --title "$install_welcome"   \
    --radiolist --column "Select" --column "Procedure." TRUE      \
    "Install" FALSE "Uninstall" FALSE "Compile" FALSE "Clean"`

    # print the user menu.

    # set `$OPTION' values depending on user input.
    case $OPTION in
       "Install") OPTION="install"           ;;
     "Uninstall") OPTION="uninstall"         ;;
       "Compile") OPTION="compile"           ;;
         "Clean") OPTION="clean"             ;;
               *) 
                  print_info "$must_select_option" 
                  exit 1 ;;
    esac

    # are you sure you want to uninstall the program?
    if [ "$OPTION" = "uninstall" ]; then
        print_warning "Are you sure you want to continue?"
    fi

    if [ "$OPTION" = "uninstall" -o "$OPTION" = "install" ]; then

        # just print basic info in order to inform the user.
        print_info "The installation program needs some information in order \
to know where the man pages, the info pages, the locales and the executables \
are located. However, it suggests you some basic directory paths, but if the \
options does not help you, please press cancel and type the values manually."

        # suggest some basic paths (we need it for 
        # installation/unistallation). if there is
        # no satisfied option the user will input
        # the value manually.

        # ask for locales input.
        l=`zenity --list --title "$select_from_list" --text \
        "Input locales directory path." --column "$path_directory" \
        "/usr/share/locale" "/usr/local/locale" "/usr/local/share/locale"`

        if [ $? -eq 1 -o -z "$l" ]; then

            # manual input.
            l=`zenity --entry --title "$input_window" --text \
            "Input locales directory path." --entry-text "/usr/share/locale"`

            if [ $? -eq 1 ]; then
                print_error "$must_input_value"
            fi
        fi

        # ask for manual page input.
        m=`zenity --list --title "$select_from_list" --text \
        "Input manual pages directory path." --column "$path_directory" \
        "/usr/share/man/man1" "/usr/local/man/man1" "/usr/local/share/man/man1"`

        if [ $? -eq 1 -o -z "$m" ]; then

            # manual input.
            m=`zenity --entry --title "$input_window" --text \
            "Input manual pages directory path." \
            --entry-text "/usr/share/man/man1"`

            if [ $? -eq 1 ]; then
                print_error "$must_input_value"
            fi
        fi

        # ask for info page input.
        i=`zenity --list --title "$select_from_list" --text \
        "Input info pages directory path." --column "$path_directory" \
        "/usr/share/info" "/usr/local/info" "/usr/local/share/info" `

        if [ $? -eq 1 -o -z "$i" ]; then

            # manual input.
            i=`zenity --entry --title "$input_window" --text \
            "Input info pages directory path." --entry-text "/usr/share/info"`

            if [ $? -eq 1 ]; then
                print_error "$must_input_value"
            fi
        fi

        # ask for binary input.
        b=`zenity --list --title "$select_from_list" --text \
        "Input binary directory path." --column "$path_directory" \
        "/usr/bin" "/usr/sbin" "/usr/local/bin" "/usr/local/sbin"`

        if [ $? -eq 1 -o -z "$b" ]; then

            # manual input.
            b=`zenity --entry --title "$input_window" --text \
            "Input binary directory path." --entry-text "/usr/bin"`

            if [ $? -eq 1 ]; then
                print_error "$must_input_value"
            fi
        fi
    fi

    # do the appropriate procedure.
    if [ "$OPTION" = "install" ]; then
        print_file "../COPYING"

        make install loc_path="$l" bin_path="$b" info_path="$i" \
        man_path="$m" | zenity --progress --width 300 --text \
        "Installing program.." --title "$progress_window" --pulsate

    elif [ "$OPTION" = "uninstall" ]; then

        make uninstall loc_path="$l" bin_path="$b" info_path="$i" \
        man_path="$m" | zenity --progress --width 300 --text \
        "Uninstalling program." --title "$progress_window" --pulsate

    elif [ "$OPTION" = "compile" ]; then
        make | zenity --progress --width 300 --text \
        "Compiling program." --title "$progress_window" --pulsate
    else
        make clean | zenity --progress --width 300 --text \
        "Cleaning program." --title "$progress_window" --pulsate
    fi

else
    print_error "$must_be_root"
fi
