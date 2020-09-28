#ifndef _UTIL_H_INCLUDED_
#define _UTIL_H_INCLUDED_
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
 * Create date:    1 Aug 2001
 * Purpose:        Definitions for util module.
 *----------------------------------------------------------------------
 * Changes:
 * 29 Mar 05, daved@physiol.usyd.edu.au: changes requested by ZT Smith
 * 16 Dec 07, daved@physiol.usyd.edu.au: updated to GPL v3
 * 09 Nov 08, arkadiusz.firus@gmail.com: added leave_line
 * 25 Sep 11, jf@dockes.org: add ifndef _UTIL_H_INCLUDED_ and allocmem
 *--------------------------------------------------------------------*/

#ifdef HAVE_STDIO_H
#include <stdio.h>
#endif

extern int h2toi(const char *);

void leave_line(FILE *f);
extern char *concatenate(const char *, const char *);

/* Help managing a growing contiguous array */
extern void *
allocmem
(
    void 	*cp,	/* The array to grow. Can be NULL */
    int	 sz,	/* Unit size in bytes */
    int 	*np,    /* Pointer to current allocation number (units) */
    int	 min,   /* Number of units to allocate the first time */
    int	 maxinc /* Maximum increment in units (maxinc*sz bytes) */
);

#endif /* _UTIL_H_INCLUDED_ */
