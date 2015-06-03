#!/bin/sh

#######
#
#  `install-nox.sh'.
#
#  This file is the text-based installation program of GNU fs.
#
#  Copyright (C) 2008  Efstathios Chatzikyriakidis (contact@efxa.org)
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

must_install_program="You must install first the following program :"
must_input_value="You must input a value to continue."
must_be_root="You must be root to run the installation program."
install_welcome="Welcome to the installation program."
install_exit="Exit from the installation program."
argument_errors="Insufficient arguments."
wrong_option="You have selected an unknown option."
proc_done="Procedure done."
proc_error="Procedure error."

### functions. ###

##
# name: print_error.
#
# description: prints an error message to STDERR.
#
# arguments: $@ -> message to print.
##
print_error ()
{
    if [ $# -lt 1 ] ; then
        print_error "$argument_errors"
        return 1
    fi

    echo "ERROR:" $@ >&2 
    exit 1
}

##
# name: print_warning.
#
# description: prints a warning message to STDERR.
#
# arguments: $@ -> message to print.
##
print_warning () 
{ 
    if [ $# -lt 1 ] ; then
        print_error "$argument_errors"
        return 1
    fi

    echo "WARNING:" $@ >&2
    exit 1
}

##
# name: print_info.
#
# description: prints an info message to STDOUT.
#
# arguments: $@ -> message to print.
##
print_info () 
{
    if [ $# -lt 1 ] ; then
        print_error "$argument_errors"
        return 1
    fi

    echo "INFO:" $@
    exit 0
}

##
# name: print_message.
#
# description: prints a message to STDOUT.
#
# arguments: $@ -> message to print.
##
print_message () 
{ 
    if [ $# -lt 1 ] ; then
        print_error "$argument_errors"
        return 1
    fi

    echo $@

    return 0
}

##
# name: prompt_yes_no.
#
# description: ask a yes/no question.
#
# arguments: $1 -> The prompt.
#            $2 -> The default answer (optional).
#
# variables: YESNO -> set to the users response
#                     y for yes, n for no (y/n).
##
prompt_yes_no () 
{
    if [ $# -lt 1 ] ; then
        print_error "$argument_errors"
        return 1
    fi

    DEF_ARG=""
    YESNO=""

    case "$2" in 
        [yY]|[yY][eE][sS]) 
            DEF_ARG=y ;;
        [nN]|[nN][oO]) 
            DEF_ARG=n ;;
    esac

    while :
    do
        printf "$1 (y/n)? "
        if [ -n "$DEF_ARG" ] ; then
            printf "[$DEF_ARG] "
        fi

        read YESNO

        if [ -z "$YESNO" ] ; then 
            YESNO="$DEF_ARG"
        fi

        case "$YESNO" in 
            [yY]|[yY][eE][sS]) 
                YESNO=y ; break ;;
            [nN]|[nN][oO]) 
                YESNO=n ; break ;;
            *)
                YESNO="" ;;
        esac
    done

    export YESNO
    unset DEF_ARG
    return 0
}

##
# name: prompt_response.
#
# description: ask a question.
#
# arguments: $1 -> The prompt.
#            $2 -> The default answer (optional).
#
# variables: RESPONSE -> set to the users response.
##
prompt_response () 
{
    if [ $# -lt 1 ] ; then
        print_error "$argument_errors"
        return 1
    fi

    RESPONSE=""
    DEF_ARG="$2"

    while :
    do
        printf "$1 ? "
        if [ -n "$DEF_ARG" -a "$DEF_ARG" != "-" ] ; then 
            printf "[$DEF_ARG] "
        fi
        
        read RESPONSE
        
        if [ -n "$RESPONSE" ] ; then
            break
        elif [ -z "$RESPONSE" -a -n "$DEF_ARG" ] ; then
            RESPONSE="$DEF_ARG"
            if [ "$RESPONSE" = "-" ] ; then RESPONSE="" ; fi
            break
        fi
    done

    export RESPONSE
    unset DEF_ARG
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

# print welcome message.
print_message "$install_welcome"

# check to see if the user is not the superuser.
is_user_root
if [ ! $? -eq 0 ]; then
    echo; print_message "$must_be_root"
    echo; print_info "$install_exit"
fi

# the user has superuser privileges.

echo # print a new line.

# test for missing programs.

app_exists zenity
if [ $? -eq 0 ]; then
    print_error "$must_install_program 'zenity'."
fi

app_exists make
if [ $? -eq 0 ]; then
    print_error "$must_install_program 'make'."
fi

app_exists gcc
if [ $? -eq 0 ]; then
    print_error "$must_install_program 'gcc'."
fi

# print the menu to the user.
echo -n "Select which procedure you want to do.

 1) Install the program.
 2) Uninstall the program.
 3) Compile the program.
 4) Clean the program.
     
Answer here: ";

# read input from user.
read OPTION

# set `$OPTION' values depending on user input.
case $OPTION in
 1) OPTION="install"   ;;
 2) OPTION="uninstall" ;;
 3) OPTION="compile"   ;;
 4) OPTION="clean"     ;;
 *)
    echo # print a new line.
    print_error "$wrong_option"
    ;;
esac

# are you sure you want to uninstall the program?
if [ "$OPTION" = "uninstall" ]; then
    echo; prompt_yes_no "Are you sure you want to continue" "y"
    if [ "$YESNO" = "n" ]; then
        echo; print_info "$install_exit"
    fi
fi

if [ "$OPTION" = "uninstall" -o "$OPTION" = "install" ]; then

    # just print basic info in order to inform the user.

    # suggest some basic paths (we need it for 
    # installation/unistallation). if there is
    # no satisfied option the user will input
    # the value manually.

    echo "
     The program needs some information in order to know where the man
     pages, the info pages, the locales and the executables are located.
     We suggest you some basic directory paths, but if the options does
     not help you, please type the values manually."

    echo # print a new line.

    # ask for locales input.
    prompt_response "Locales directory path?" "/usr/share/locale"
    if [ -z "$RESPONSE" ]; then
        echo; print_warning "$must_input_value"
    fi
    l="$RESPONSE"

    # ask for manual page input.
    prompt_response "Manual pages directory path?" "/usr/share/man/man1"
    if [ -z "$RESPONSE" ]; then
        echo; print_warning "$must_input_value"
    fi
    m="$RESPONSE"

    # ask for info page input.
    prompt_response "Info pages directory path?" "/usr/share/info"
    if [ -z "$RESPONSE" ]; then
        echo; print_warning "$must_input_value"
    fi
    i="$RESPONSE"

    # ask for binary input.
    prompt_response "Binary programs directory path?" "/usr/bin"
    if [ -z "$RESPONSE" ]; then
        echo; print_warning "$must_input_value"
    fi
    b="$RESPONSE"
fi

# do the appropriate procedure.
if [ "$OPTION" = "install" ]; then

    make install loc_path="$l" bin_path="$b" \
    info_path="$i" man_path="$m" > /dev/null

elif [ "$OPTION" = "uninstall" ]; then

    make uninstall loc_path="$l" bin_path="$b" \
    info_path="$i" man_path="$m" > /dev/null

elif [ "$OPTION" = "compile" ]; then
    make > /dev/null
else
    make clean > /dev/null
fi

# print the procedure message status.
if [ $? -eq 0 ] ; then
    echo; print_info "$proc_done"
else
    echo; print_error "$proc_error"
fi
