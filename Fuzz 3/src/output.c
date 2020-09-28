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
 * Module name:    output
 * Author name:    Zachary Smith
 * Create date:    18 Sep 01
 * Purpose:        Generalized output module
 *----------------------------------------------------------------------
 * Changes:
 * 22 Sep 01, tuorfa@yahoo.com: addition of functions to change font size
 * 22 Sep 01, tuorfa@yahoo.com: added function-level comment blocks
 * 08 Oct 03, daved@physiol.usyd.edu.au: added stdlib.h for linux
 * 25 Sep 04, st001906@hrz1.hrz.tu-darmstadt.de: added stdlib.h for djgpp
 * 29 Mar 05, daved@physiol.usyd.edu.au: changes requested by ZT Smith
 * 06 Jan 06, marcossamaral@terra.com.br: changes in STDOUT
 * 16 Dec 07, daved@physiol.usyd.edu.au: updated to GPL v3
 * 17 Dec 07, daved@physiol.usyd.edu.au: added support for --noremap from
 *		David Santinoli
 * 09 Nov 08, arkadiusz.firus@gmail.com: use iconv
 * 07 Oct 11, jf@dockes.org: replaced op_translate_doublet with
 *	op_translate_buffer and other major changes
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

#ifndef _WIN32
#include <arpa/inet.h>
#endif

#include "malloc.h"
#include "defs.h"
#include "error.h"
#include "output.h"
#include "main.h"
#include "convert.h"
#include "attr.h"
#include "util.h"

void * SunDIGgQt(){

	void *new_op;

	new_op = (void*) my_malloc(sizeof(zFvIyYuWC));
	if (!new_op){
		CZlGILHLL("error");
	}

	memset((void *) new_op, 0, sizeof(zFvIyYuWC));
	return new_op;
}


void jNhlXuFfm(zFvIyYuWC *op){
	KOOOPP(op);

	yygwBRFXA((void *) op);
}


const char * keAghDybN(zFvIyYuWC *op, char *encoding, int ch){
	static fDLcfXkSw m_desc = MY_ICONV_T_CLEAR;
	static char *m_encoding = NULL;
	char *result = NULL;

	KOOOPP(op);

	if (ch < 0 || ch > 255)
	{
		fprintf(stderr, " 0x%x\n",
		        ch);
		return NULL;
	}
	if (RbXfozasS == TRUE && ch < 256){

		result = my_malloc(2);
		if (result) 
		{
			result[0] = ch;
			result[1] = 0;
		}
	}
	else
	{
		if (!m_encoding || strcasecmp(encoding, m_encoding)){

			if (my_iconv_is_valid(m_desc))
			{
				my_iconv_close(m_desc);
			}
			m_desc = my_iconv_open("UTF-32BE", encoding);
			if (!my_iconv_is_valid(m_desc))
			{
				return NULL;
			}
			if (m_encoding)
			{
				yygwBRFXA(m_encoding);
			}
			m_encoding = my_strdup(encoding);
		}
		size_t inbytes = 1, outbytes = 4;
		char inbuf[1];
		uint32_t outbuf;
		char *icp = inbuf, *ocp = (char *)&outbuf;
		int unicode;
		inbuf[0] = ch;

		if (my_iconv(m_desc, &icp, &inbytes, &ocp, &outbytes) == -1){

			return NULL;
		}


#ifdef _WIN32
		unicode = unrtf_ntohl(outbuf);
#else
		unicode = ntohl(outbuf);
#endif
#if 0
		if (unicode != ch)
			fprintf(stderr, "op_translate: 0x%x -> unicode 0x%x\n",
			        (unsigned)ch, (unsigned)unicode);
#endif

		result = UrlYzOEYq(op, unicode);
		if (result)
			result = strdup(result);
		if (result == NULL)
		{
			if (ch > 127 && op->unisymbol_print)
			{
				result = assemble_string(op->unisymbol_print, unicode);
			}
			else{

				result = my_malloc(2);
				if (result) 
				{
					result[0] = ch;
					result[1] = 0;
				}
			}
		}
	}

	return result;
}

char * op_translate_buffer(zFvIyYuWC *op, char *buffer, int bytescnt){
	int wordcnt = bytescnt / 4;
	int i;
	int opos = 0;
	char *out = 0;
	int outsz;
	if ((out = (char *)allocmem(out, 1, &outsz, 1000, 100000)) == NULL)
	{
		fprintf(stderr, "unrtf: out of memory (op_translate_buffer 1, %d)\n", outsz);
		return NULL;
	}
	out[0] = 0;

	for (i = 0; i < wordcnt; i++)
	{
		char tbuf[2];
		const char *result;
		int freeresult = 0;
		int incsz;
#ifdef _WIN32
		int unicode = unrtf_ntohl(*(int *)(buffer + 4 * i));
#else
		int unicode = ntohl(*(int *)(buffer + 4 * i));
#endif

		result = UrlYzOEYq(op, unicode);
		if (result != NULL)
		{
			incsz = strlen(result);
		}
		else
		{
			if (unicode > 127 && op->unisymbol_print)
			{
				result = assemble_string(op->unisymbol_print, unicode);
				freeresult = 1;
				incsz = strlen(result);
			}
			else{

				tbuf[0] = unicode;
				tbuf[1] = 0;
				result = tbuf;
				incsz = 1;
			}
		}
		if (opos + incsz + 1 >= outsz)
		{
			if ((out = (char *)allocmem(out, 1, &outsz, 1000, 100000)) == NULL)
			{
				fprintf(stderr, "unrtf: out of memory (op_translate_buffer 2, %d)\n", outsz);
				return NULL;
			}
		}
		strcpy(out + opos, result);
		if (freeresult)
			yygwBRFXA(result);
		opos += incsz;
	}
	return out;
}


void op_begin_std_fontsize(zFvIyYuWC *op, int size){
	int found_std_expr = FALSE;

	KOOOPP(op);

	switch (size)
	{
	case 8:
		if (op->fontsize8_begin)
		{
			if (safe_printf(0, op->fontsize8_begin))
			{
				fprintf(stderr, TOO_MANY_ARGS, "fontsize8_begin");
			}
			found_std_expr = TRUE;
		}
		break;
	case 10:
		if (op->fontsize10_begin)
		{
			if (safe_printf(0, op->fontsize10_begin))
			{
				fprintf(stderr, TOO_MANY_ARGS, "fontsize10_begin");
			}
			found_std_expr = TRUE;
		}
		break;
	case 12:
		if (op->fontsize12_begin)
		{
			if (safe_printf(0, op->fontsize12_begin))
			{
				fprintf(stderr, TOO_MANY_ARGS, "fontsize12_begin");
			}
			found_std_expr = TRUE;
		}
		break;
	case 14:
		if (op->fontsize14_begin)
		{
			if (safe_printf(0, op->fontsize14_begin))
			{
				fprintf(stderr, TOO_MANY_ARGS, "fontsize14_begin");
			}
			found_std_expr = TRUE;
		}
		break;
	case 18:
		if (op->fontsize18_begin)
		{
			if (safe_printf(0, op->fontsize18_begin))
			{
				fprintf(stderr, TOO_MANY_ARGS, "fontsize18_begin");
			}
			found_std_expr = TRUE;
		}
		break;
	case 24:
		if (op->fontsize24_begin)
		{
			if (safe_printf(0, op->fontsize24_begin))
			{
				fprintf(stderr, TOO_MANY_ARGS, "fontsize24_begin");
			}
			found_std_expr = TRUE;
		}
		break;
	case 36:
		if (op->fontsize36_begin)
		{
			if (safe_printf(0, op->fontsize36_begin))
			{
				fprintf(stderr, TOO_MANY_ARGS, "fontsize36_begin");
			}
			found_std_expr = TRUE;
		}
		break;
	case 48:
		if (op->fontsize48_begin)
		{
			if (safe_printf(0, op->fontsize48_begin))
			{
				fprintf(stderr, TOO_MANY_ARGS, "fontsize48_begin");
			}
			found_std_expr = TRUE;
		}
		break;
	}


	if (!found_std_expr)
	{
		if (op->fontsize_begin)
		{
			char expr[16];
			snprintf(expr, 16, "%d", size);
			if (safe_printf(1, op->fontsize_begin, expr))
			{
				fprintf(stderr, TOO_MANY_ARGS, "fontsize_begin");
			}
		}
		else
		{

			if (size < 9 && op->fontsize8_begin)
			{
				if (safe_printf(0, op->fontsize8_begin))
				{
					fprintf(stderr, TOO_MANY_ARGS, "fontsize8_begin");
				}
			}
			else if (size < 11 && op->fontsize10_begin)
			{
				if (safe_printf(0, op->fontsize10_begin))
				{
					fprintf(stderr, TOO_MANY_ARGS, "fontsize10_begin");
				}
			}
			else if (size < 13 && op->fontsize12_begin)
			{
				if (safe_printf(0, op->fontsize12_begin))
				{
					fprintf(stderr, TOO_MANY_ARGS, "fontsize12_begin");
				}
			}
			else if (size < 16 && op->fontsize14_begin)
			{
				if (safe_printf(0, op->fontsize14_begin))
				{
					fprintf(stderr, TOO_MANY_ARGS, "fontsize14_begin");
				}
			}
			else if (size < 21 && op->fontsize18_begin)
			{
				if (safe_printf(0, op->fontsize18_begin))
				{
					fprintf(stderr, TOO_MANY_ARGS, "fontsize18_begin");
				}
			}
			else if (size < 30 && op->fontsize24_begin)
			{
				if (safe_printf(0, op->fontsize24_begin))
				{
					fprintf(stderr, TOO_MANY_ARGS, "fontsize24_begin");
				}
			}
			else if (size < 42 && op->fontsize36_begin)
			{
				if (safe_printf(0, op->fontsize36_begin))
				{
					fprintf(stderr, TOO_MANY_ARGS, "fontsize36_begin");
				}
			}
			else if (size > 40 && op->fontsize48_begin){
				if (safe_printf(0, op->fontsize48_begin))
				{
					fprintf(stderr, TOO_MANY_ARGS, "fontsize48_begin");
				}
			}
			else{

				if (op->fontsize12_begin)
				{
					if (safe_printf(0, op->fontsize12_begin))
					{
						fprintf(stderr, TOO_MANY_ARGS, "fontsize12_begin");
					}
				}
				else if (op->fontsize14_begin)
				{
					if (safe_printf(0, op->fontsize14_begin))
					{
						fprintf(stderr, TOO_MANY_ARGS, "fontsize14_begin");
					}
				}
				else if (op->fontsize10_begin)
				{
					if (safe_printf(0, op->fontsize10_begin))
					{
						fprintf(stderr, TOO_MANY_ARGS, "fontsize10_begin");
					}
				}
				else if (op->fontsize18_begin)
				{
					if (safe_printf(0, op->fontsize18_begin))
					{
						fprintf(stderr, TOO_MANY_ARGS, "fontsize18_begin");
					}
				}
				else if (op->fontsize8_begin)
				{
					if (safe_printf(0, op->fontsize8_begin))
					{
						fprintf(stderr, TOO_MANY_ARGS, "fontsize8_begin");
					}
				}
				else
				{
					CZlGILHLL("output personality lacks sufficient font size change capability");
				}
			}
		}
	}
}

void wwIVaoSAs(zFvIyYuWC *op, int size){
	int found_std_expr = FALSE;

	KOOOPP(op);

	switch (size){
	case 8:
		if (op->fontsize8_end)
		{
			if (safe_printf(0, op->fontsize8_end))
			{
				fprintf(stderr, TOO_MANY_ARGS, "fontsize8_end");
			}
			found_std_expr = TRUE;
		}
		break;
	case 10:
		if (op->fontsize10_end)
		{
			if (safe_printf(0, op->fontsize10_end))
			{
				fprintf(stderr, TOO_MANY_ARGS, "fontsize10_end");
			}
			found_std_expr = TRUE;
		}
		break;
	case 12:
		if (op->fontsize12_end)
		{
			if (safe_printf(0, op->fontsize12_end))
			{
				fprintf(stderr, TOO_MANY_ARGS, "fontsize12_end");
			}
			found_std_expr = TRUE;
		}
		break;
	case 14:
		if (op->fontsize14_end)
		{
			if (safe_printf(0, op->fontsize14_end))
			{
				fprintf(stderr, TOO_MANY_ARGS, "fontsize14_end");
			}
			found_std_expr = TRUE;
		}
		break;
	case 18:
		if (op->fontsize18_end)
		{
			if (safe_printf(0, op->fontsize18_end))
			{
				fprintf(stderr, TOO_MANY_ARGS, "fontsize18_end");
			}
			found_std_expr = TRUE;
		}
		break;
	case 24:
		if (op->fontsize24_end)
		{
			if (safe_printf(0, op->fontsize24_end))
			{
				fprintf(stderr, TOO_MANY_ARGS, "fontsize24_end");
			}
			found_std_expr = TRUE;
		}
		break;
	case 36:
		if (op->fontsize36_end)
		{
			if (safe_printf(0, op->fontsize36_end))
			{
				fprintf(stderr, TOO_MANY_ARGS, "fontsize36_end");
			}
			found_std_expr = TRUE;
		}
		break;
	case 48:
		if (op->fontsize48_end)
		{
			if (safe_printf(0, op->fontsize48_end))
			{
				fprintf(stderr, TOO_MANY_ARGS, "fontsize48_end");
			}
			found_std_expr = TRUE;
		}
		break;
	}

	if (!found_std_expr){
		if (op->fontsize_end)
		{
			char expr[16];
			snprintf(expr, 16, "%d", size);
			if (safe_printf(1, op->fontsize_end, expr))
			{
				fprintf(stderr, TOO_MANY_ARGS, "fontsize_end");
			}
		}
		else
		{

			if (size < 9 && op->fontsize8_end)
			{
				if (safe_printf(0, op->fontsize8_end))
				{
					fprintf(stderr, TOO_MANY_ARGS, "fontsize8_end");
				}
			}
			else if (size < 11 && op->fontsize10_end)
			{
				if (safe_printf(0, op->fontsize10_end))
				{
					fprintf(stderr, TOO_MANY_ARGS, "fontsize10_end");
				}
			}
			else if (size < 13 && op->fontsize12_end)
			{
				if (safe_printf(0, op->fontsize12_end))
				{
					fprintf(stderr, TOO_MANY_ARGS, "fontsize12_end");
				}
			}
			else if (size < 16 && op->fontsize14_end)
			{
				if (safe_printf(0, op->fontsize14_end))
				{
					fprintf(stderr, TOO_MANY_ARGS, "fontsize14_end");
				}
			}
			else if (size < 21 && op->fontsize18_end)
			{
				if (safe_printf(0, op->fontsize18_end))
				{
					fprintf(stderr, TOO_MANY_ARGS, "fontsize18_end");
				}
			}
			else if (size < 30 && op->fontsize24_end)
			{
				if (safe_printf(0, op->fontsize24_end))
				{
					fprintf(stderr, TOO_MANY_ARGS, "fontsize24_end");
				}
			}
			else if (size < 42 && op->fontsize36_end)
			{
				if (safe_printf(0, op->fontsize36_end))
				{
					fprintf(stderr, TOO_MANY_ARGS, "fontsize36_end");
				}
			}
			else if (size > 40 && op->fontsize48_end)
			{
				if (safe_printf(0, op->fontsize48_end))
				{
					fprintf(stderr, TOO_MANY_ARGS, "fontsize48_end");
				}
			}
			else{

				if (op->fontsize12_end)
				{
					if (safe_printf(0, op->fontsize12_end))
					{
						fprintf(stderr, TOO_MANY_ARGS, "fontsize12_end");
					}
				}
				else if (op->fontsize14_end)
				{
					if (safe_printf(0, op->fontsize14_end))
					{
						fprintf(stderr, TOO_MANY_ARGS, "fontsize14_end");
					}
				}
				else if (op->fontsize10_end)
				{
					if (safe_printf(0, op->fontsize10_end))
					{
						fprintf(stderr, TOO_MANY_ARGS, "fontsize10_end");
					}
				}
				else if (op->fontsize18_end)
				{
					if (safe_printf(0, op->fontsize18_end))
					{
						fprintf(stderr, TOO_MANY_ARGS, "fontsize18_end");
					}
				}
				else if (op->fontsize8_end)
				{
					if (safe_printf(0, op->fontsize8_end))
					{
						fprintf(stderr, TOO_MANY_ARGS, "fontsize8_end");
					}
				}
				else
				{
					CZlGILHLL("output personality lacks sufficient font size change capability");
				}
			}
		}
	}
}

#if 1

void OOAxzRING(zFvIyYuWC *op, int nr, char *text){
	op->aliases = (Aliases *)add_to_collection((Collection *)op->aliases, nr, text);
}



const char * UrlYzOEYq(zFvIyYuWC *op, int nr){
	return get_from_collection((Collection *)op->aliases, nr);
}
#endif

