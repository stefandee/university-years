# NOTE: this is a GNU Makefile.  You must use "gmake" rather than "make".
#
# Makefile for the multiprogramming assignment
#    Defines set up assuming multiprogramming is done before the file system.
#    If not, use the "filesys first"  defines below. 
#
#
# Copyright (c) 1992 The Regents of the University of California.
# All rights reserved.  See copyright.h for copyright notice and limitation 
# of liability and disclaimer of warranty provisions.

DEFINES = -DUSER_PROGRAM -DFILESYS_NEEDED -DFILESYS_STUB
INCPATH = -I../bin -I../filesys -I../userprog -I../threads -I../machine
HFILES = $(THREAD_H) $(USERPROG_H)
CFILES = $(THREAD_C) $(USERPROG_C)
C_OFILES = $(THREAD_O) $(USERPROG_O)

# if file sys done first!
#DEFINES = -DUSER_PROGRAM -DFILESYS_NEEDED -DFILESYS
#INCPATH = -I../bin -I../filesys -I../userprog -I../threads -I../machine
#HFILES = $(THREAD_H) $(USERPROG_H) $(FILESYS_H)
#CFILES = $(THREAD_C) $(USERPROG_C) $(FILESYS_C)
#C_OFILES = $(THREAD_O) $(USERPROG_O) $(FILESYS_O)

include ../Makefile.common
include ../Makefile.dep
#-----------------------------------------------------------------
# DO NOT DELETE THIS LINE -- make depend uses it
# DEPENDENCIES MUST END AT END OF FILE
main.o: ../threads/main.cc ../threads/copyright.h ../threads/utility.h \
 /usr/include/g++/bool.h /usr/include/_G_config.h \
 /usr/include/gnu/types.h /usr/include/features.h \
 /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i586-pc-linux-gnu/pgcc-2.91.57/include/stddef.h \
 ../machine/sysdep.h /usr/include/stdio.h /usr/include/libio.h \
 /usr/lib/gcc-lib/i586-pc-linux-gnu/pgcc-2.91.57/include/stdarg.h \
 /usr/include/stdio_lim.h /usr/include/string.h ../threads/system.h \
 ../threads/thread.h ../machine/machine.h ../machine/translate.h \
 ../machine/disk.h ../userprog/addrspace.h ../filesys/filesys.h \
 ../filesys/openfile.h ../threads/scheduler.h ../threads/list.h \
 ../machine/interrupt.h ../machine/stats.h ../machine/timer.h
list.o: ../threads/list.cc ../threads/copyright.h ../threads/list.h \
 ../threads/utility.h /usr/include/g++/bool.h /usr/include/_G_config.h \
 /usr/include/gnu/types.h /usr/include/features.h \
 /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i586-pc-linux-gnu/pgcc-2.91.57/include/stddef.h \
 ../machine/sysdep.h /usr/include/stdio.h /usr/include/libio.h \
 /usr/lib/gcc-lib/i586-pc-linux-gnu/pgcc-2.91.57/include/stdarg.h \
 /usr/include/stdio_lim.h /usr/include/string.h
scheduler.o: ../threads/scheduler.cc ../threads/copyright.h \
 ../threads/scheduler.h ../threads/list.h ../threads/utility.h \
 /usr/include/g++/bool.h /usr/include/_G_config.h \
 /usr/include/gnu/types.h /usr/include/features.h \
 /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i586-pc-linux-gnu/pgcc-2.91.57/include/stddef.h \
 ../machine/sysdep.h /usr/include/stdio.h /usr/include/libio.h \
 /usr/lib/gcc-lib/i586-pc-linux-gnu/pgcc-2.91.57/include/stdarg.h \
 /usr/include/stdio_lim.h /usr/include/string.h ../threads/thread.h \
 ../machine/machine.h ../machine/translate.h ../machine/disk.h \
 ../userprog/addrspace.h ../filesys/filesys.h ../filesys/openfile.h \
 ../threads/system.h ../machine/interrupt.h ../machine/stats.h \
 ../machine/timer.h
synch.o: ../threads/synch.cc ../threads/copyright.h ../threads/synch.h \
 ../threads/thread.h ../threads/utility.h /usr/include/g++/bool.h \
 /usr/include/_G_config.h /usr/include/gnu/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i586-pc-linux-gnu/pgcc-2.91.57/include/stddef.h \
 ../machine/sysdep.h /usr/include/stdio.h /usr/include/libio.h \
 /usr/lib/gcc-lib/i586-pc-linux-gnu/pgcc-2.91.57/include/stdarg.h \
 /usr/include/stdio_lim.h /usr/include/string.h ../machine/machine.h \
 ../machine/translate.h ../machine/disk.h ../userprog/addrspace.h \
 ../filesys/filesys.h ../filesys/openfile.h ../threads/list.h \
 ../threads/system.h ../threads/scheduler.h ../machine/interrupt.h \
 ../machine/stats.h ../machine/timer.h
synchlist.o: ../threads/synchlist.cc ../threads/copyright.h \
 ../threads/synchlist.h ../threads/list.h ../threads/utility.h \
 /usr/include/g++/bool.h /usr/include/_G_config.h \
 /usr/include/gnu/types.h /usr/include/features.h \
 /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i586-pc-linux-gnu/pgcc-2.91.57/include/stddef.h \
 ../machine/sysdep.h /usr/include/stdio.h /usr/include/libio.h \
 /usr/lib/gcc-lib/i586-pc-linux-gnu/pgcc-2.91.57/include/stdarg.h \
 /usr/include/stdio_lim.h /usr/include/string.h ../threads/synch.h \
 ../threads/thread.h ../machine/machine.h ../machine/translate.h \
 ../machine/disk.h ../userprog/addrspace.h ../filesys/filesys.h \
 ../filesys/openfile.h
system.o: ../threads/system.cc ../threads/copyright.h \
 ../threads/system.h ../threads/utility.h /usr/include/g++/bool.h \
 /usr/include/_G_config.h /usr/include/gnu/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i586-pc-linux-gnu/pgcc-2.91.57/include/stddef.h \
 ../machine/sysdep.h /usr/include/stdio.h /usr/include/libio.h \
 /usr/lib/gcc-lib/i586-pc-linux-gnu/pgcc-2.91.57/include/stdarg.h \
 /usr/include/stdio_lim.h /usr/include/string.h ../threads/thread.h \
 ../machine/machine.h ../machine/translate.h ../machine/disk.h \
 ../userprog/addrspace.h ../filesys/filesys.h ../filesys/openfile.h \
 ../threads/scheduler.h ../threads/list.h ../machine/interrupt.h \
 ../machine/stats.h ../machine/timer.h
thread.o: ../threads/thread.cc ../threads/copyright.h \
 ../threads/thread.h ../threads/utility.h /usr/include/g++/bool.h \
 /usr/include/_G_config.h /usr/include/gnu/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i586-pc-linux-gnu/pgcc-2.91.57/include/stddef.h \
 ../machine/sysdep.h /usr/include/stdio.h /usr/include/libio.h \
 /usr/lib/gcc-lib/i586-pc-linux-gnu/pgcc-2.91.57/include/stdarg.h \
 /usr/include/stdio_lim.h /usr/include/string.h ../machine/machine.h \
 ../machine/translate.h ../machine/disk.h ../userprog/addrspace.h \
 ../filesys/filesys.h ../filesys/openfile.h ../threads/switch.h \
 ../threads/synch.h ../threads/list.h ../threads/system.h \
 ../threads/scheduler.h ../machine/interrupt.h ../machine/stats.h \
 ../machine/timer.h
utility.o: ../threads/utility.cc ../threads/copyright.h \
 ../threads/utility.h /usr/include/g++/bool.h /usr/include/_G_config.h \
 /usr/include/gnu/types.h /usr/include/features.h \
 /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i586-pc-linux-gnu/pgcc-2.91.57/include/stddef.h \
 ../machine/sysdep.h /usr/include/stdio.h /usr/include/libio.h \
 /usr/lib/gcc-lib/i586-pc-linux-gnu/pgcc-2.91.57/include/stdarg.h \
 /usr/include/stdio_lim.h /usr/include/string.h
threadtest.o: ../threads/threadtest.cc ../threads/copyright.h \
 ../threads/system.h ../threads/utility.h /usr/include/g++/bool.h \
 /usr/include/_G_config.h /usr/include/gnu/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i586-pc-linux-gnu/pgcc-2.91.57/include/stddef.h \
 ../machine/sysdep.h /usr/include/stdio.h /usr/include/libio.h \
 /usr/lib/gcc-lib/i586-pc-linux-gnu/pgcc-2.91.57/include/stdarg.h \
 /usr/include/stdio_lim.h /usr/include/string.h ../threads/thread.h \
 ../machine/machine.h ../machine/translate.h ../machine/disk.h \
 ../userprog/addrspace.h ../filesys/filesys.h ../filesys/openfile.h \
 ../threads/scheduler.h ../threads/list.h ../machine/interrupt.h \
 ../machine/stats.h ../machine/timer.h ../threads/synch.h
interrupt.o: ../machine/interrupt.cc ../threads/copyright.h \
 ../machine/interrupt.h ../threads/list.h ../threads/utility.h \
 /usr/include/g++/bool.h /usr/include/_G_config.h \
 /usr/include/gnu/types.h /usr/include/features.h \
 /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i586-pc-linux-gnu/pgcc-2.91.57/include/stddef.h \
 ../machine/sysdep.h /usr/include/stdio.h /usr/include/libio.h \
 /usr/lib/gcc-lib/i586-pc-linux-gnu/pgcc-2.91.57/include/stdarg.h \
 /usr/include/stdio_lim.h /usr/include/string.h ../threads/system.h \
 ../threads/thread.h ../machine/machine.h ../machine/translate.h \
 ../machine/disk.h ../userprog/addrspace.h ../filesys/filesys.h \
 ../filesys/openfile.h ../threads/scheduler.h ../machine/stats.h \
 ../machine/timer.h
sysdep.o: ../machine/sysdep.cc ../threads/copyright.h \
 /usr/include/stdio.h /usr/include/libio.h /usr/include/features.h \
 /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h \
 /usr/include/_G_config.h /usr/include/gnu/types.h \
 /usr/lib/gcc-lib/i586-pc-linux-gnu/pgcc-2.91.57/include/stddef.h \
 /usr/lib/gcc-lib/i586-pc-linux-gnu/pgcc-2.91.57/include/stdarg.h \
 /usr/include/stdio_lim.h /usr/include/string.h /usr/include/signal.h \
 /usr/include/sigset.h /usr/include/signum.h /usr/include/sigaction.h \
 /usr/include/sigcontext.h /usr/include/asm/sigcontext.h \
 /usr/include/sigstack.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bytesex.h \
 /usr/include/sys/select.h /usr/include/selectbits.h \
 /usr/include/sys/time.h /usr/include/timebits.h \
 /usr/include/sys/socket.h /usr/include/socketbits.h \
 /usr/include/sockaddrcom.h /usr/include/asm/socket.h \
 /usr/include/asm/sockios.h /usr/include/sys/file.h \
 /usr/include/fcntl.h /usr/include/fcntlbits.h /usr/include/sys/un.h \
 /usr/include/sys/mman.h /usr/include/linux/mman.h \
 /usr/include/asm/mman.h /usr/include/unistd.h \
 /usr/include/posix_opt.h /usr/include/confname.h \
 ../machine/interrupt.h ../threads/list.h ../threads/utility.h \
 /usr/include/g++/bool.h ../machine/sysdep.h ../threads/system.h \
 ../threads/thread.h ../machine/machine.h ../machine/translate.h \
 ../machine/disk.h ../userprog/addrspace.h ../filesys/filesys.h \
 ../filesys/openfile.h ../threads/scheduler.h ../machine/stats.h \
 ../machine/timer.h
stats.o: ../machine/stats.cc ../threads/copyright.h \
 ../threads/utility.h /usr/include/g++/bool.h /usr/include/_G_config.h \
 /usr/include/gnu/types.h /usr/include/features.h \
 /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i586-pc-linux-gnu/pgcc-2.91.57/include/stddef.h \
 ../machine/sysdep.h /usr/include/stdio.h /usr/include/libio.h \
 /usr/lib/gcc-lib/i586-pc-linux-gnu/pgcc-2.91.57/include/stdarg.h \
 /usr/include/stdio_lim.h /usr/include/string.h ../machine/stats.h
timer.o: ../machine/timer.cc ../threads/copyright.h ../machine/timer.h \
 ../threads/utility.h /usr/include/g++/bool.h /usr/include/_G_config.h \
 /usr/include/gnu/types.h /usr/include/features.h \
 /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i586-pc-linux-gnu/pgcc-2.91.57/include/stddef.h \
 ../machine/sysdep.h /usr/include/stdio.h /usr/include/libio.h \
 /usr/lib/gcc-lib/i586-pc-linux-gnu/pgcc-2.91.57/include/stdarg.h \
 /usr/include/stdio_lim.h /usr/include/string.h ../threads/system.h \
 ../threads/thread.h ../machine/machine.h ../machine/translate.h \
 ../machine/disk.h ../userprog/addrspace.h ../filesys/filesys.h \
 ../filesys/openfile.h ../threads/scheduler.h ../threads/list.h \
 ../machine/interrupt.h ../machine/stats.h
addrspace.o: ../userprog/addrspace.cc ../threads/copyright.h \
 ../threads/system.h ../threads/utility.h /usr/include/g++/bool.h \
 /usr/include/_G_config.h /usr/include/gnu/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i586-pc-linux-gnu/pgcc-2.91.57/include/stddef.h \
 ../machine/sysdep.h /usr/include/stdio.h /usr/include/libio.h \
 /usr/lib/gcc-lib/i586-pc-linux-gnu/pgcc-2.91.57/include/stdarg.h \
 /usr/include/stdio_lim.h /usr/include/string.h ../threads/thread.h \
 ../machine/machine.h ../machine/translate.h ../machine/disk.h \
 ../userprog/addrspace.h ../filesys/filesys.h ../filesys/openfile.h \
 ../threads/scheduler.h ../threads/list.h ../machine/interrupt.h \
 ../machine/stats.h ../machine/timer.h ../bin/noff.h
bitmap.o: ../userprog/bitmap.cc ../threads/copyright.h \
 ../userprog/bitmap.h ../threads/utility.h /usr/include/g++/bool.h \
 /usr/include/_G_config.h /usr/include/gnu/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i586-pc-linux-gnu/pgcc-2.91.57/include/stddef.h \
 ../machine/sysdep.h /usr/include/stdio.h /usr/include/libio.h \
 /usr/lib/gcc-lib/i586-pc-linux-gnu/pgcc-2.91.57/include/stdarg.h \
 /usr/include/stdio_lim.h /usr/include/string.h ../filesys/openfile.h
exception.o: ../userprog/exception.cc ../threads/copyright.h \
 ../threads/system.h ../threads/utility.h /usr/include/g++/bool.h \
 /usr/include/_G_config.h /usr/include/gnu/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i586-pc-linux-gnu/pgcc-2.91.57/include/stddef.h \
 ../machine/sysdep.h /usr/include/stdio.h /usr/include/libio.h \
 /usr/lib/gcc-lib/i586-pc-linux-gnu/pgcc-2.91.57/include/stdarg.h \
 /usr/include/stdio_lim.h /usr/include/string.h ../threads/thread.h \
 ../machine/machine.h ../machine/translate.h ../machine/disk.h \
 ../userprog/addrspace.h ../filesys/filesys.h ../filesys/openfile.h \
 ../threads/scheduler.h ../threads/list.h ../machine/interrupt.h \
 ../machine/stats.h ../machine/timer.h ../userprog/syscall.h
progtest.o: ../userprog/progtest.cc ../threads/copyright.h \
 ../threads/system.h ../threads/utility.h /usr/include/g++/bool.h \
 /usr/include/_G_config.h /usr/include/gnu/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i586-pc-linux-gnu/pgcc-2.91.57/include/stddef.h \
 ../machine/sysdep.h /usr/include/stdio.h /usr/include/libio.h \
 /usr/lib/gcc-lib/i586-pc-linux-gnu/pgcc-2.91.57/include/stdarg.h \
 /usr/include/stdio_lim.h /usr/include/string.h ../threads/thread.h \
 ../machine/machine.h ../machine/translate.h ../machine/disk.h \
 ../userprog/addrspace.h ../filesys/filesys.h ../filesys/openfile.h \
 ../threads/scheduler.h ../threads/list.h ../machine/interrupt.h \
 ../machine/stats.h ../machine/timer.h ../machine/console.h \
 ../threads/synch.h
console.o: ../machine/console.cc ../threads/copyright.h \
 ../machine/console.h ../threads/utility.h /usr/include/g++/bool.h \
 /usr/include/_G_config.h /usr/include/gnu/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i586-pc-linux-gnu/pgcc-2.91.57/include/stddef.h \
 ../machine/sysdep.h /usr/include/stdio.h /usr/include/libio.h \
 /usr/lib/gcc-lib/i586-pc-linux-gnu/pgcc-2.91.57/include/stdarg.h \
 /usr/include/stdio_lim.h /usr/include/string.h ../threads/system.h \
 ../threads/thread.h ../machine/machine.h ../machine/translate.h \
 ../machine/disk.h ../userprog/addrspace.h ../filesys/filesys.h \
 ../filesys/openfile.h ../threads/scheduler.h ../threads/list.h \
 ../machine/interrupt.h ../machine/stats.h ../machine/timer.h
machine.o: ../machine/machine.cc ../threads/copyright.h \
 ../machine/machine.h ../threads/utility.h /usr/include/g++/bool.h \
 /usr/include/_G_config.h /usr/include/gnu/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i586-pc-linux-gnu/pgcc-2.91.57/include/stddef.h \
 ../machine/sysdep.h /usr/include/stdio.h /usr/include/libio.h \
 /usr/lib/gcc-lib/i586-pc-linux-gnu/pgcc-2.91.57/include/stdarg.h \
 /usr/include/stdio_lim.h /usr/include/string.h ../machine/translate.h \
 ../machine/disk.h ../threads/system.h ../threads/thread.h \
 ../userprog/addrspace.h ../filesys/filesys.h ../filesys/openfile.h \
 ../threads/scheduler.h ../threads/list.h ../machine/interrupt.h \
 ../machine/stats.h ../machine/timer.h
mipssim.o: ../machine/mipssim.cc ../threads/copyright.h \
 ../machine/machine.h ../threads/utility.h /usr/include/g++/bool.h \
 /usr/include/_G_config.h /usr/include/gnu/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i586-pc-linux-gnu/pgcc-2.91.57/include/stddef.h \
 ../machine/sysdep.h /usr/include/stdio.h /usr/include/libio.h \
 /usr/lib/gcc-lib/i586-pc-linux-gnu/pgcc-2.91.57/include/stdarg.h \
 /usr/include/stdio_lim.h /usr/include/string.h ../machine/translate.h \
 ../machine/disk.h ../machine/mipssim.h ../threads/system.h \
 ../threads/thread.h ../userprog/addrspace.h ../filesys/filesys.h \
 ../filesys/openfile.h ../threads/scheduler.h ../threads/list.h \
 ../machine/interrupt.h ../machine/stats.h ../machine/timer.h
translate.o: ../machine/translate.cc ../threads/copyright.h \
 ../machine/machine.h ../threads/utility.h /usr/include/g++/bool.h \
 /usr/include/_G_config.h /usr/include/gnu/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i586-pc-linux-gnu/pgcc-2.91.57/include/stddef.h \
 ../machine/sysdep.h /usr/include/stdio.h /usr/include/libio.h \
 /usr/lib/gcc-lib/i586-pc-linux-gnu/pgcc-2.91.57/include/stdarg.h \
 /usr/include/stdio_lim.h /usr/include/string.h ../machine/translate.h \
 ../machine/disk.h ../userprog/addrspace.h ../filesys/filesys.h \
 ../filesys/openfile.h ../threads/system.h ../threads/thread.h \
 ../threads/scheduler.h ../threads/list.h ../machine/interrupt.h \
 ../machine/stats.h ../machine/timer.h
# DEPENDENCIES MUST END AT END OF FILE
# IF YOU PUT STUFF HERE IT WILL GO AWAY
# see make depend above
