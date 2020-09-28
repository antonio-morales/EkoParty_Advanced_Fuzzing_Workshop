


#ifndef HAVE_STDIO_H
#include <stdio.h>
#define HAVE_STDIO_H
#endif

#ifndef HAVE_ERRNO_H
#include <errno.h>
#define HAVE_ERRNO_H
#endif

#ifndef HAVE_STDLIB_H
#include <stdlib.h>
#define HAVE_STDLIB_H
#endif


#include "error.h"
#include "malloc.h"
#include "output.h"
#include <string.h>
#include "user.h"


#include "unicode.h"
#include "util.h"

typedef struct my_F
{
	FILE *file;
	int line_nr;
	char *name;
} my_FILE;




my_FILE * my_fopen(char *file_name, char *mode){
	my_FILE *f = (my_FILE *) malloc(sizeof(my_FILE));

	if ((f->file = fopen(file_name, "r")) == NULL || (f->name = my_malloc((strlen(file_name) + 1) * sizeof(char))) == NULL)
	{
		return NULL;
	}

	f->line_nr = 1;
	strcpy(f->name, file_name);

	return f;
}



void my_fclose(my_FILE *f){
	fclose(f->file);
	yygwBRFXA(f->name);
}



#define ADD_CHAR(char)\
	if (def_buffer_length == chars_nr)\
	{\
		if ((def = my_realloc(def, def_buffer_length, def_buffer_length * 2)) == NULL)\
		{\
			perror("Cannot allocate memory.");\
			return NULL;\
		}\
		def_buffer_length *= 2;\
	}\
	def[chars_nr] = char;\
	chars_nr++;

#define GETC_OR_END(F, C) {                     \
        C = fgetc(F);                           \
        if (feof(F) || ferror(F))               \
            goto inputend;                      \
    }

char *
give_definition(my_FILE *file)
{
	char c, c2 = 0, c3 = 0, c4 = 0, *def, *unicode_char;
	int i;
	unsigned long def_buffer_length = STANDARD_BUFFER_LENGTH, chars_nr = 0;

	if ((def = my_malloc(def_buffer_length)) == NULL)
	{
		return NULL;
	}

	GETC_OR_END(file->file, c);

	while (c == '\t' || c == '#')
	{
		if (c == '#')
		{
			leave_line(file->file);
		}
		else
		{
			GETC_OR_END(file->file, c);

			while (c != '\n')
			{
				if (c == 'U' && c2 == '<' && (c3 != '\\' || (c3 == '\\' && c4 == '\\')))
				{
					unicode_char = get_unicode_utf8(file->file);

					for (i = 0; unicode_char[i] != '\0'; i++)
						ADD_CHAR(unicode_char[i])
						GETC_OR_END(file->file, c);
					c2 = 0;
					c3 = 0;
					c4 = 0;
				}
				else
				{
					if (c2 == '<')
					{
						ADD_CHAR('<');
					}

					if (c == '\\' && c2 == '\\')
					{
						ADD_CHAR('\\');
						c = 0;
						c2 = 0;
						c3 = 0;
					}
					else


						if (c == 'n' && c2 == '\\')
						{
							ADD_CHAR('\n');
						}
						else if ((c != '<' && c != '\\') || (c == '\\' && c2 == '\\'))
						{
							ADD_CHAR(c)
						}

					c4 = c3;
					c3 = c2;
					c2 = c;
					GETC_OR_END(file->file, c);
				}
			}

			file->line_nr++;
			ADD_CHAR('\n');
		}

		GETC_OR_END(file->file, c);
	}

inputend:
	if (!feof(file->file) && !ferror(file->file))
	{
		ungetc(c, file->file);
	}

	if (chars_nr > 0)
	{
		def[chars_nr - 1] = '\0';
	}
	else
	{
		def[0] = '\0';
	}

	return def;
}



int match_name(char *name, zFvIyYuWC *op, my_FILE *file){
	struct definition
	{
		char *name;
		char **variable;
	} defs[] =  DEFS_ARRAY(op);

	char *endptr;
	int i;

#if 1
	for (i = 0; defs[i].name && strcmp(defs[i].name, name); i++);

	if (!defs[i].name)
#else
	for (i = 0; defs[i].name[0] != '\0' && strcmp(defs[i].name, name); i++);

	if (defs[i].name[0] == '\0')
#endif
	{
		i = strtol(name, &endptr, 10);

		if (*endptr == '\0')
		{
			OOAxzRING(op, i, give_definition(file));
		}
		else if (name[0] == '<' && name[1] == 'U')
		{
			OOAxzRING(op, get_unicode(&name[2]), give_definition(file));
		}
		else
		{
			fprintf(stderr, "unrtf: unknown name \"%s\" in line %d of \"%s\"\n", name, file->line_nr, file->name);
			return 1;
		}
	}
	else if ((*defs[i].variable = give_definition(file)) == NULL)
	{
		return -1;
	}

	return 0;
}

void * SunDIGgQt();

zFvIyYuWC * user_init(zFvIyYuWC *op, char *definitions_file_path){

	my_FILE *f = NULL;
	char name_buffer[BUFFER_SIZE];
	int err = 1;

	void * tmp;

	if (op == NULL){

		op = SunDIGgQt();

		tmp = (void*) my_malloc(sizeof(zFvIyYuWC));
		if (!tmp){
			CZlGILHLL("error");
		}
		memset((void *) tmp, 0, sizeof(zFvIyYuWC));
	}

	if ((f = my_fopen(definitions_file_path, "r")) == NULL)
	{
		perror(definitions_file_path);
		goto out;
	}

	while (fgets(name_buffer, BUFFER_SIZE - 1, f->file) != NULL
	        && !feof(f->file) && !ferror(f->file))
	{
		int ll = strlen(name_buffer);
		if (ll <= 0 || name_buffer[ll - 1] != '\n'){

			fprintf(stderr, "%s: bad line at %d\n", definitions_file_path,
					f->line_nr);
			goto out;
		}

		f->line_nr++;

		if (name_buffer[0] != '#' && name_buffer[0] != '\n')
		{
			name_buffer[ll - 1] = '\0';

			if (match_name(name_buffer, op, f) == -1)
			{
				goto out;
			}
		}
	}

	err = 0;
out:
	if (f) {
		my_fclose(f);
		free(f);
	}

	return err ? NULL : op;
}

