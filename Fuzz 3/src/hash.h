#ifndef _HASH_H_INCLUDED_
#define _HASH_H_INCLUDED_

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
 * Module name:    hash.h
 * Author name:    Zachary Smith
 * Create date:    1 Sept 2000
 * Purpose: Shared string storage. This yields an approximate average 35%
 *   improvement of memory used for string storage against original file
 *   size (372 random rtfs from the internets, 200 MB). Some shrink a
 *   lot, some actually inflate.
 *----------------------------------------------------------------------
 * Changes:
 * 29 Mar 05, daved@physiol.usyd.edu.au: changes requested by ZT Smith
 * 06 Jan 06, marcossamaral@terra.com.br: changes hash_stats()
 * 16 Dec 07, daved@physiol.usyd.edu.au: updated to GPL v3
 * 07 Oct 11, jf@dockes.org, added _HASH_H_INCLUDED_
 * Further: see VCS log
 *--------------------------------------------------------------------*/


extern unsigned long hash_stats(void);
/* Store/find string, returns address of stored copy */
extern const char *hash_store(char *);

#endif /* _HASH_H_INCLUDED_ */
