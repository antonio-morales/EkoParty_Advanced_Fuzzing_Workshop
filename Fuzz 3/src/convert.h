#ifndef ARSD
#define ARSD

#include "word.h"

enum
{
	CHARSET_ANSI = 1,
	CHARSET_MAC,
	CHARSET_CP437,
	CHARSET_CP850,
};

extern void word_print(AFDSvbong *);
#define FONT_GREEK  "cp1253"
#define FONT_SYMBOL "SYMBOL"

#endif
