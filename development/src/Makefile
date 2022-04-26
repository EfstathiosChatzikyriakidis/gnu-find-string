#######
#
#  `Makefile'.
#
#  This file is the makefile for the GNU fs.
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

# information which help the compilation part.

# the compiler which is used is the `GNU C Compiler'.
CC = gcc

# options which help the compiler to check
# if the program is both ansi/well written.
ANSI_FLAGS = -D__USE_FIXED_PROTOTYPES__ --ansi -pedantic -W  \
             -Wshadow -pedantic-errors -Wall -Wpointer-arith \
             -Wstrict-prototypes -Wconversion -Wcast-qual

# set defines to the program.
LOCALE_DEFS = -DLOC_DIR='"$(loc_path)"'

# the name of the executable.
EXEC = gfs

# the targets of the objects.
OBJS = gfs-parse-in-files \
       gfs-err-wrap-funcs \
       gfs-in-files-tasks \
        gfs-proc-in-files \
        gfs-han-prog-name \
        gfs-in-files-list \
        gfs-parse-options \
           gfs-print-info \
             gfs-messages \
	         gfs-main

# the targets.

# produce the executable.
gfs-exec: $(OBJS)
	      $(CC) $(ANSI_FLAGS) $(CFLAGS) -o $(EXEC) *.o

# produce the interface objects.
gfs-main: gfs.c
	      $(CC) $(ANSI_FLAGS) $(LOCALE_DEFS) $(CFLAGS) -c gfs.c

gfs-parse-in-files: gfs-parse-input-files.c
	                $(CC) $(ANSI_FLAGS) $(CFLAGS) -c gfs-parse-input-files.c

gfs-proc-in-files: gfs-process-input-files.c
	               $(CC) $(ANSI_FLAGS) $(CFLAGS) -c gfs-process-input-files.c

gfs-err-wrap-funcs: gfs-error-wrapper-funcs.c
	                $(CC) $(ANSI_FLAGS) $(CFLAGS) -c gfs-error-wrapper-funcs.c

gfs-in-files-tasks: gfs-input-files-tasks.c
	                $(CC) $(ANSI_FLAGS) $(CFLAGS) -c gfs-input-files-tasks.c

gfs-han-prog-name: gfs-handle-program-name.c
	               $(CC) $(ANSI_FLAGS) $(CFLAGS) -c gfs-handle-program-name.c

gfs-in-files-list: gfs-input-files-list.c
	               $(CC) $(ANSI_FLAGS) $(CFLAGS) -c gfs-input-files-list.c

gfs-parse-options: gfs-parse-options.c
	               $(CC) $(ANSI_FLAGS) $(CFLAGS) -c gfs-parse-options.c

gfs-print-info: gfs-print-info.c
	            $(CC) $(ANSI_FLAGS) $(CFLAGS) -c gfs-print-info.c

gfs-messages: gfs-messages.c
	          $(CC) $(ANSI_FLAGS) $(CFLAGS) -c gfs-messages.c

# clean executable and object files.
clean:
	rm -f $(EXEC) *.o

# install man page, info page, locales and the program.
install: gfs-exec
	 gzip -c ../man/$(EXEC).1 > ../man/$(EXEC).1.gz
	 mv -f ../man/$(EXEC).1.gz $(man_path)

	 makeinfo ../texi/$(EXEC).texi -o ../texi/$(EXEC).info
	 gzip -c ../texi/$(EXEC).info > ../texi/$(EXEC).info.gz
	 mv -f ../texi/$(EXEC).info.gz $(info_path)

	 cp -fr ../mo/*/ $(loc_path)
	 mv -f $(EXEC) $(bin_path)

	 rm -f *.o ../texi/$(EXEC).info

# uninstall man page, info page, locales and the program.
uninstall:
	rm -f $(man_path)/$(EXEC).1.gz
	rm -f $(info_path)/$(EXEC).info.gz
	rm -f $(loc_path)/*/*/$(EXEC).mo
	rm -f $(bin_path)/$(EXEC)
