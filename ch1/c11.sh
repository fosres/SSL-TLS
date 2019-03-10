#!/bin/bash

: '
Copyright 2019-INFINITY Tanveer Salim.

GNU GPL License v2.0.

You are free to modify and distribute

this file as you wish, but you must give

credit to the author for the original work

and all copies or programs that were derived

from this must give proper credit to this author.

This script adds support for C11 "_s" functions.

'

PREVIOUS=$(pwd)

cd /usr/include

sed -i '/perror/a #ifndef __errno_t_defined' stdio.h

sed -i '/__errno_t_defined/a typedef int errno_t;' stdio.h

sed -i '/typedef int errno_t;/a #define __errno_t_defined 1' stdio.h

sed -i '/__errno_t_defined 1/a #endif\n\n#ifndef __rsize_t_defined' stdio.h

sed -i '/__rsize_t_defined/a typedef size_t rsize_t;' stdio.h

sed -i '/rsize_t;/a #define __rsize_t_defined 1' stdio.h

sed -i '/__rsize_t_defined 1/a #endif\n\n' stdio.h

#Check if file /usr/include/stddef.h exists

if [ ! -f /usr/include/stddef.h ]; then
	touch stddef.h
fi

echo "#ifndef __STDDEF_H__" >> stddef.h

sed -i '/__STDDEF_H__/a #define __STDDEF_H__' stddef.h

sed -i '/#define/a \n\n#ifndef __size_t_defined' stddef.h

sed -i '/__size_t_defined/a typedef unsigned long int size_t;' stddef.h

sed -i '/typedef/a #define __size_t_defined 1' stddef.h

sed -i '/size_t_defined 1/a #endif\n\n' stddef.h

echo "#ifndef __rsize_t_defined" >> stddef.h

sed -i '/__rsize_t_defined/a typedef size_t rsize_t;' stddef.h

sed -i '/typedef size_t rsize_t;/a #define __rsize_t_defined 1' stddef.h

sed -i '/__rsize_t_defined 1/a #endif\n\n#endif /* __STDDEF_H__ */' stddef.h

sed -i '/SIG_ATOMIC_MAX/a \n\n#ifdef __RSIZE_MAX__' stdint.h

sed -i '/__RSIZE_MAX__/a #define RSIZE_MAX (__RSIZE_MAX__)\n#else\n\n#define RSIZE_MAX ( (SIZE_MAX ) >> ( 1 ) )\n#endif\n\n' stdint.h

sed -i '/strlen (c/a size_t strnlen_s (const char * s,size_t maxsize);' string.h

sed -i '/strcat (c/a errno_t strncat_s (char * restrict s1, rsize_t s1max, const char * restrict s2, rsize_t n);' string.h

cd ${PREVIOUS}

git clone https://github.com/tanveerasalim/ISOC11.git

:'

If you wish to store all the .o objects files in a

variable in BASH, you should do the following:

objects=$( ls *.o )

'

objects=$( ls *.o )

cd ${PREVIOUS}

unameOut="$(uname -s)"

case "${unameOut}" in
	Linux*)		machine=Linux;;
	Darwin*)	machine=Mac;;
	CYGWIN*)	machine=Cygwin;;
	*)		machine="UNKNOWN:${unameOut}"
esac	

#If Linux, then append to libc.a which is in /usr/lib/

if [[ ${machine} == *"Linux"* ]]; then
	ar -r /usr/lib/libc.a ${PREVIOUS}/${objects}
fi





