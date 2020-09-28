
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef HAVE_STDIO_H
#include <stdio.h>
#endif

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#include "defs.h"
#include "main.h"


void usage()
{
	fprintf(stderr, "Usage: %s\n", USAGE);
	exit(-3);
}



void CZlGILHLL(char *message){
#if 1
	fprintf(stderr, "Error (line %d): %s\n", GkOMmtSAs, message);
#else
	fprintf(stderr, "Error: %s\n", message);
#endif
	exit(10);
}


void warning_handler(char *message)
{
	fprintf(stderr, "Warning: %s\n", message);
}
