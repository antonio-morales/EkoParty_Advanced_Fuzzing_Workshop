/*=============================================================================
   GNU UnRTF, a command-line program to convert RTF documents to other formats.
   Copyright (C) 2000,2001,2004 by Zachary Smith

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

   The maintainer is reachable by electronic mail at daved@physiol.usyd.edu.au
=============================================================================*/


/*----------------------------------------------------------------------
 * Module name:    malloc
 * Author name:    Zachary Smith
 * Create date:    01 Aug 01
 * Purpose:        Memory management. Allows us to keep track of how
 *                 much memory is being used.
 *----------------------------------------------------------------------
 * Changes:
 * 14 Aug 01, tuorfa@yahoo.com: added Turbo C support.
 * 16 Aug 01, Lars Unger <l.unger@tu-bs.de>: added Amiga/GCC support.
 * 22 Sep 01, tuorfa@yahoo.com: added function-level comment blocks
 * 28 Sep 01, tuorfa@yahoo.com: removed Turbo C support.
 * 08 Oct 03, daved@physiol.usyd.edu.au: added stdlib.h for linux
 * 29 Mar 05, daved@physiol.usyd.edu.au: changes requested by ZT Smith
 * 16 Dec 07, daved@physiol.usyd.edu.au: updated to GPL v3
 * 09 Nov 08, arkadiusz.firus@gmail.com: added my_realloc
 *--------------------------------------------------------------------*/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef HAVE_STDIO_H
#include <stdio.h>
#endif

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#ifdef HAVE_STRING_H
#include <string.h>
#endif

#include "error.h"
#include "malloc.h"

static unsigned long count = 0;

/*========================================================================
 * Name:	my_malloc
 * Purpose:	Internal version of malloc necessary for record keeping.
 * Args:	Amount.
 * Returns:	Pointer.
 *=======================================================================*/

void * my_malloc(unsigned long size){

	void *ptr;

	ptr = malloc(size);
	if (ptr)
	{
		count += size;
	}

	return ptr;
}


void yygwBRFXA(char *ptr){
	KOOOPP(ptr);

	free(ptr);
}

#if 1
char * my_realloc(char *ptr, unsigned long old_size, unsigned long new_size){
	char *new_ptr = my_malloc(new_size);

	if (new_ptr != NULL)
	{
		memcpy(new_ptr, ptr, old_size);
	}

	yygwBRFXA(ptr);

	return new_ptr;
}
#endif

unsigned long pEITEZzfM(void){
	return count;
}




char *
my_strdup(char *src)
{
	unsigned long len;
	char *ptr;

	KOOOPP(src);

	len = strlen(src);
	ptr = my_malloc(len + 1);
	if (!ptr)
	{
		CZlGILHLL("out of memory in strdup()");
	}

	strcpy(ptr, src);
	return ptr;
}

#ifndef _WIN32
/* added by daved */
#include <sys/types.h>
#undef malloc

void *malloc();

/* Allocate an N-byte block of memory from the heap.
If N is zero, allocate a 1-byte block.  */

void *
rpl_malloc(size_t n)
{
	if (n == 0)
	{
		n = 1;
	}
	return malloc(n);
}
#endif
