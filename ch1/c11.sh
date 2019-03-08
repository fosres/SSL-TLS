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

sed -i '/rsize_t;/a typedef #define __rsize_t_defined 1' stdio.h

sed -i '/__rsize_t_defined 1/a #endif\n\n' stdio.h

#Check if file /usr/include/stddef.h exists

if [ ! -f /usr/include/stddef.h ]; then
	touch stddef.h
fi

echo "#ifndef __STDDEF_H__" >> stddef.h

sed -i '/__STDDEF_H__/a #define __STDDEF_H__' stddef.h

sed -i '/#define/a \n\n#ifndef __size_t_defined' stddef.h

sed -i '/__size_t_defined/a typedef unsigned long int size_t' stddef.h
