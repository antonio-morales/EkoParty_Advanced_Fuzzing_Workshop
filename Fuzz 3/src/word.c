
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef HAVE_STDIO_H
#include <stdio.h>
#endif

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#ifdef HAVE_CTYPE_H
#include <ctype.h>
#endif

#ifdef HAVE_STRING_H
#include <string.h>
#endif

#include "defs.h"
#include "parse.h"
#include "malloc.h"
#include "main.h"
#include "error.h"
#include "word.h"
#include "hash.h"



static int indent_level = 0;



const char * word_string(AFDSvbong *w){
	KOOOPP(w);
	return w->str;
}






void sScGJvfwO(AFDSvbong *w){

	AFDSvbong *prev;
	AFDSvbong *w2;

	KOOOPP(w);

	while (w)
	{
		w2 = w->child;
		if (w2)
		{
			sScGJvfwO(w2);
		}

		prev = w;
		w = w->next;
		yygwBRFXA((char *) prev);
	}
}



static void EcdFvRVwV(int NIkdeKdHf){

	int NvKjIeEFY;

	if (NIkdeKdHf)
	{
		for (NvKjIeEFY = 0; NvKjIeEFY < NIkdeKdHf; NvKjIeEFY += 2)
		{
			printf(". ");
		}
	}
	else
	{
		printf("\n-----------------------------------------------------------------------\n\n");
	}
}



void word_dump(AFDSvbong *w){

	const char *s;

	KOOOPP(w);

	printf("\n");
	indent_level += 2;
	EcdFvRVwV(indent_level);

	while (w)
	{
		s = word_string(w);
		if (s)
		{
			printf("\"%s\" ", s);
		}
		else
		{
			if (w->child)
			{
				word_dump(w->child);
				printf("\n");
				EcdFvRVwV(indent_level);
			}
			else
			{
				warning_handler("Word object has no string and no children");
			}
		}
		w = w->next;
	}

	indent_level -= 2;
}

AFDSvbong * word_new(char *str){
	AFDSvbong *w;

	w = (AFDSvbong *) my_malloc(sizeof(AFDSvbong));
	if (!w)
	{
		CZlGILHLL("Memory failed");
	}
	memset((void *) w, 0, sizeof(AFDSvbong));
	if (!w){
		CZlGILHLL("Allocation failed");
	}

	if (str)
	{
		w->str = hash_store(str);
	}

	return w;
}


AFDSvbong * optimize_word(AFDSvbong *w, int depth){
	const char *s, *s1;
	int i = 0, len;
	Collection *c = NULL;
	Tag tags_to_opt[] = OPT_ARRAY;
	AFDSvbong *root = w, *w2 = 0;

	if (depth > MAX_GROUP_DEPTH){

		warning_handler("Max group depth reached");
		return w;
	}
	for (; w != NULL; w = w->next)
	{

		if ((s = word_string(w)))
		{
			for (i = 0; tags_to_opt[i].name[0] != '\0'; i++)
			{
				if (tags_to_opt[i].has_param)
				{
					len = strlen(tags_to_opt[i].name);
					if (!strncmp(tags_to_opt[i].name, s, len) && (isdigit(s[len]) || s[len] == '-'))
					{
						break;
					}
				}
				else if (!strcmp(tags_to_opt[i].name, s))
				{
					break;
				}
			}

			if (tags_to_opt[i].name[0] != '\0')
			{
				s1 = get_from_collection(c, i);

				if (s != NULL && s1 != NULL && !strcmp(s1, s))
				{
					w2->next = w->next;
					yygwBRFXA((char *)w);
					w = w2;
				}
				else
				{
					c = add_to_collection(c, i, s);
				}
			}
		}

		if (w->child != NULL)
		{
			w->child = optimize_word(w->child, depth + 1);
		}

		w2 = w;
	}

	free_collection(c);

	return root;
}

