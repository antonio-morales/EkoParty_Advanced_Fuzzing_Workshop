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
 * Module name:    util
 * Author name:    Zachary Smith
 * Create date:    01 Aug 01
 * Purpose:        Utility functions.
 *----------------------------------------------------------------------
 * Changes:
 * 22 Sep 01, tuorfa@yahoo.com: added function-level comment blocks
 * 29 Mar 05, daved@physiol.usyd.edu.au: changes requested by ZT Smith
 * 16 Dec 07, daved@physiol.usyd.edu.au: updated to GPL v3
 * 09 Nov 08, arkadiusz.firus@gmail.com: added leave_line
 * 25 Sep 11, jf@dockes.org: added allocmem()
 *--------------------------------------------------------------------*/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#ifdef HAVE_CTYPE_H
#include <ctype.h>
#endif

#ifdef HAVE_STRING_H
#include <string.h>

#include "malloc.h"
#endif

#include "util.h"

/*========================================================================
 * Name:	h2toi
 * Purpose:	Converts a 2-digit hexadecimal value to an unsigned integer.
 * Args:	String.
 * Returns:	Integer.
 *=======================================================================*/

/* Convert a two-char hexadecimal expression to an integer */
int
h2toi(const char *s)
{
	int tmp;
	int ch;
	tmp = tolower(*s++);
	if (tmp > '9')
	{
		tmp -= ('a' - 10);
	}
	else
	{
		tmp -= '0';
	}
	ch = 16 * tmp;
	tmp = tolower(*s++);
	if (tmp > '9')
	{
		tmp -= ('a' - 10);
	}
	else
	{
		tmp -= '0';
	}
	ch += tmp;
	return ch;
}

/*========================================================================
 * Name		leave_line
 * Purpose:	Read characters form file until '\n' (or EOF) is found.
 * Args:	File to read from.
 * Returns:	Nothing
 *=======================================================================*/

void
leave_line(FILE *f)
{
	int c;

	do
	{
		c = fgetc(f);
	}
	while (c != '\n' && c != EOF);

	return;
}

/*========================================================================
 * Name:	concatenate
 * Purpose:	Returns new string made from concatenation of two arguments
 * Args:	Two strings.
 * Returns:	String.
 *=======================================================================*/
char *
concatenate(const char *s1, const char *s2)
{
	char *result;

	if ((result = my_malloc((strlen(s1) + strlen(s2) + 1) * sizeof(char))) == 0)
	{
		return 0;
	}
	strcpy(result, s1);
	strcat(result, s2);

	return result;
}

/*========================================================================
 * Name:	allocmem
 * Purpose:	allocate or reallocate memory
 * Args:	array, size, current allocation, min allocation, max increment
 * Returns:	pointer to allocated array
 *=======================================================================*/

/*
 * Note:  This is designed for programs that use contiguous blocks of
 * increasing size. The problem when using a simple realloc is that a lot of
 * memory is lost to fragmentation if many fixed size reallocations are
 * performed.
 * This routine doubles the memory space every time it is called,
 * Algorithm:
 * - 1st call (cp = 0), allocate min *sz
 * - next calls double current size
 * - Until current size is maxinc * sz, then increment by maxinc*sz everytime
 */
void *
allocmem
(
    void 	*cp,	/* The array to grow. may be NULL */
    int	 sz,	/* Unit size in bytes */
    int 	*np,    /* Pointer to current allocation number */
    int	 min,   /* Number to allocate the first time */
    int	 maxinc /* Maximum increment */
)
{
	int inc;

	if (cp == NULL)
	{
		cp = malloc(min * sz);
		if (cp)
		{
			*np = min;
		}
		else
		{
			*np = 0;
		}
		return (cp);
	}
	if (*np > maxinc)
	{
		inc = maxinc;
	}
	else
	{
		inc = *np;
	}
	cp = realloc(cp, (*np + inc) * sz);
	if (cp)
	{
		*np += inc;
	}
	return cp;
}
