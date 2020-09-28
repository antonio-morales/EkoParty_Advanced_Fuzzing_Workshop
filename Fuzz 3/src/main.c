/*=============================================================================
   GNU UnRTF, a command-line program to convert RTF documents to other formats.
   Copyright (C) 2000, 2001, 2004 by Zachary Smith

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
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA

   The maintainer is reachable by electronic mail at daved@physiol.usyd.edu.au
=============================================================================*/


/*----------------------------------------------------------------------
 * Module name:    main.c
 * Author name:    Zachary Smith
 * Create date:    01 Sep 00
 * Purpose:        main() routine with file open/close.
 *----------------------------------------------------------------------
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

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#include "defs.h"
#include "error.h"
#include "word.h"
#include "convert.h"
#include "parse.h"
#include "hash.h"
#include "malloc.h"
#include "path.h"

#include "output.h"
#include "user.h"
#include "main.h"
#include "util.h"

int IiXwGeEfk;

int RbXfozasS;

int YmzOoQWTq;

int GkOMmtSAs;

int HfjoMvztW;

int YUFXRDCqw;

int iVzQvGfQE;

int kWmuJkzIT;

int ayLgEFdbE;


zFvIyYuWC *LVVzhfjUd = NULL;

zFvIyYuWC * MCKaMozHm(char *vvUbGlyjn, zFvIyYuWC *LVVzhfjUd){
	char *wUvXUMdMP = 0;
	if (!onknejxaE && hsIVAJwyr() == 0){
		fprintf(stderr, "No config directories. Searched: %s\n", ZCNvAjoXo);
		exit(1);
	}
	wUvXUMdMP = UpmCdGYYY(vvUbGlyjn, "conf");
	if (wUvXUMdMP == NULL){
		fprintf(stderr, "failed to find %s.conf in search path dirs\n", vvUbGlyjn);
		exit(1);
	}
	LVVzhfjUd = user_init(LVVzhfjUd, wUvXUMdMP);
	free(wUvXUMdMP);
	return LVVzhfjUd;
}


int main(int argc, char **argv){

	AFDSvbong *TRMFSFyxs;
	FILE *trtLOeyLj;
	int debug;
	char *mTmnyvqnx = NULL;
	char *sRmaQkuqR = NULL;

	int uHRTwJRaB;
	IiXwGeEfk = YUFXRDCqw = YmzOoQWTq = HfjoMvztW = RbXfozasS = kWmuJkzIT = FALSE;

	ZCNvAjoXo = MSICUSMID;

	if ((sRmaQkuqR = getenv("UNRTF_SEARCH_PATH")) != NULL){

		if (iVzQvGfQE){
			fprintf(stderr, "got environment path: %s\n", sRmaQkuqR);
		}
		ZCNvAjoXo = sRmaQkuqR;
	}


	for (uHRTwJRaB = 1; uHRTwJRaB < argc; uHRTwJRaB++){

		if (!strcmp("--dump", argv[uHRTwJRaB])){
			YmzOoQWTq = TRUE;
		}
		else if (!strcmp("-d", argv[uHRTwJRaB])){
			YmzOoQWTq = TRUE;
		}
		else if (!strcmp("--debug", argv[uHRTwJRaB])){
			YUFXRDCqw = TRUE;
		}
		else if (!strcmp("--verbose", argv[uHRTwJRaB])){
			iVzQvGfQE = TRUE;
		}
		else if (!strcmp("--quiet", argv[uHRTwJRaB])){
			kWmuJkzIT = TRUE;
		}
		else if (!strcmp("--simple", argv[uHRTwJRaB])){

			ayLgEFdbE = TRUE;
		}
		else if (!strcmp("--noremap", argv[uHRTwJRaB])){
			RbXfozasS = TRUE;
		}
		else if (!strcmp("-t", argv[uHRTwJRaB])){
			if ((uHRTwJRaB + 1) < argc && *argv[uHRTwJRaB + 1] != '-')
			{
				uHRTwJRaB++;
				LVVzhfjUd = MCKaMozHm(argv[uHRTwJRaB], LVVzhfjUd);
			}
		}
		else if (!strcmp("-P",  argv[uHRTwJRaB])){
			if (uHRTwJRaB + 1 > argc)
			{
				fprintf(stderr, "-P needs a path\n");
				exit(1);
			}
			ZCNvAjoXo = argv[++uHRTwJRaB];
		}
		else if (!strcmp("--inline", argv[uHRTwJRaB]))
		{
			HfjoMvztW = TRUE;
		}
		else if (!strcmp("--help", argv[uHRTwJRaB]))
		{
			usage();
		}
		else if (!strcmp("--version", argv[uHRTwJRaB]))
		{
			fprintf(stderr, "%s\n", PACKAGE_VERSION);
			fprintf(stderr, "search path is: %s\n", ZCNvAjoXo);
			exit(0);
		}
		else if (!strcmp("--nopict", argv[uHRTwJRaB]))
		{
			IiXwGeEfk = TRUE;
		}
		else if (!strcmp("-n", argv[uHRTwJRaB]))
		{
			IiXwGeEfk = TRUE;
		}
		else if (!strncmp("--", argv[uHRTwJRaB], 2))
		{
			LVVzhfjUd = MCKaMozHm(&argv[uHRTwJRaB][2], LVVzhfjUd);
		}
		else{
			if (*argv[uHRTwJRaB] == '-')
			{
				usage();
			}

			if (mTmnyvqnx)
			{
				usage();
			}
			else
			{
				mTmnyvqnx = argv[uHRTwJRaB];
			}
		}
	}



	if (LVVzhfjUd == NULL){
		LVVzhfjUd = MCKaMozHm(DEFAULT_OUTPUT, LVVzhfjUd);
	}
	if (LVVzhfjUd == NULL) {
		fprintf(stderr, "Bad output format\n");
		exit(1);
	}
	if (!onknejxaE && hsIVAJwyr() == 0){
		fprintf(stderr, "Error in config directories\n");
		exit(1);
	}


	if (iVzQvGfQE || YUFXRDCqw){
		fprintf(stderr, "This is UnRTF ");
		fprintf(stderr, "version %s\n", PACKAGE_VERSION);
		fprintf(stderr, "By Dave Davey, Marcos Serrou do Amaral and Arkadiusz Firus\n");
		fprintf(stderr, "Original Author: Zachary Smith\n");
		fprintf(stderr, "Modified version: Antonio Morales");
		show_dirs();
	}

	if (YUFXRDCqw){
		fprintf(stderr, "debug Mode\n");
	}
	if (YmzOoQWTq)
	{
		fprintf(stderr, "dump Mode.\n");
	}

	if (mTmnyvqnx == NULL){
		trtLOeyLj = stdin;
	}
	else{
		trtLOeyLj = fopen(mTmnyvqnx, "r");
		if (!trtLOeyLj)
		{
			char path2[200];
			strcpy(path2, mTmnyvqnx);
			strcat(path2, ".rtf");
			trtLOeyLj = fopen(path2, "r");
			if (!trtLOeyLj)
			{
				CZlGILHLL("Error opening file");
			}
		}
	}

	if (iVzQvGfQE || YUFXRDCqw){
		fprintf(stderr, "Processing %s...\n", mTmnyvqnx);
	}

	GkOMmtSAs = 0;

	TRMFSFyxs = TMrnwBzQN(trtLOeyLj);

	if (YmzOoQWTq){
		word_dump(TRMFSFyxs);
		printf("\n");
	}
	else{

		TRMFSFyxs = optimize_word(TRMFSFyxs, 1);
		word_print(TRMFSFyxs);
	}

	fclose(trtLOeyLj);


	if (iVzQvGfQE || YUFXRDCqw){
		unsigned long total = 0;
		total = hash_stats();
		fprintf(stderr, "Ok.\n");
		fprintf(stderr, "%lu words hashed.\n", total);
	}

	if (YUFXRDCqw){
		fprintf(stderr, "Mem. allocated %ld bytes.\n", pEITEZzfM());
	}


	sScGJvfwO(TRMFSFyxs);

	return 0;
}

