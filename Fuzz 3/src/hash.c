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
 * Module name:    hash
 * Author name:    Zachary Smith
 * Create date:    01 Sep 00
 * Purpose:        shared string storage. This is used to save us from
 *                 doing multiple mallocs for recurring strings such as
 *                 'the' and \par. This is not a big issue under Unix,
 *                 but it is under other OSes and anyway, waste not want not.
 *----------------------------------------------------------------------
 * Changes:
 * 08 Apr 01, tuorfa@yahoo.com: check for out of memory after malloc.
 * 21 Apr 01, tuorfa@yahoo.com: signed to conversion unsigned bug
 * 03 Aug 01, tuorfa@yahoo.com: fixes for using 16-bit compiler
 * 22 Sep 01, tuorfa@yahoo.com: added function-level comment blocks
 * 08 Oct 03, daved@physiol.usyd.edu.au: some type fixes
 * 29 Mar 05, daved@physiol.usyd.edu.au: changes requsted by ZT Smith
 * 06 Jan 06, marcossamaral@terra.com.br: changes hash_stats function
 * 16 Dec 07, daved@physiol.usyd.edu.au: updated to GPL v3
 * Further: see VCS log
 *--------------------------------------------------------------------*/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef HAVE_STDIO_H
#include <stdio.h>
#endif

#ifdef HAVE_STRING_H
#include <string.h>
#endif

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#include "error.h"
#include "main.h"
#include "malloc.h"


typedef struct _hi
{
	struct _hi *next;
	char str[1];
} HashItem;


/* Index by first char of string not \ */
static HashItem *hash[256];

/*========================================================================
 * Name:	hash_stats
 * Purpose:	Return the number of words stored. This is all words,
 * 			including commands to RTF, NOT the number of printed words in
 * 			a given document.
 * Args:	None.
 * Returns:	Number of words stored.
 *=======================================================================*/

unsigned long
hash_stats()
{
	int i;
	unsigned long total = 0;
	HashItem *hi;
	for (i = 0; i < 256; i++)
	{
		hi = hash[i];
		while (hi)
		{
			total++;
			hi = hi->next;
		}
	}
	return total;
}



/*========================================================================
 * Name:	hashitem_new
 * Purpose:	Creates a new linked list item for the hash table.
 * Args:	String.
 * Returns:	HashItem.
 *=======================================================================*/

static HashItem *
hashitem_new(char *str)
{
	HashItem *hi;

	unsigned int l = sizeof(HashItem) + strlen(str);
	hi = (HashItem *) my_malloc(l);
	if (!hi)
	{
		CZlGILHLL("Out of memory");
	}
	strcpy(hi->str, str);
	hi->next = NULL;

	return hi;
}


const char * hash_store(char *str){
	unsigned char ch = (unsigned char) * str;
	HashItem *hi;

	if (ch == '\\' && *(str + 1))
	{
		ch = *(str + 1);
	}
	hi = hash[ch];
	while (hi)
	{
		if (!strcmp(hi->str, str))
		{
			return hi->str;
		}
		hi = hi->next;
	}
	/* not in hash */
	hi = hashitem_new(str);
	hi->next = hash[ch];
	hash[ch] = hi;
	return hi->str;
}

