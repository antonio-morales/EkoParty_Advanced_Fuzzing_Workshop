
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

#ifndef HAVE_ATDARG_H
#include <stdarg.h>
#endif

#include "malloc.h"
#include "defs.h"
#include "error.h"
#include "attr.h"
#include "main.h"

extern void starting_body();
extern void starting_text();

extern int simulate_allcaps;
extern int simulate_smallcaps;


#define MAX_ATTRS 100


typedef struct _stack
{
	unsigned char attr_stack[MAX_ATTRS];
	char *attr_stack_params[MAX_ATTRS];
	int tos;
	struct _stack *prev;
} AttrStack;

/*@null@*/ static AttrStack *stack_of_stacks = NULL;
/*@null@*/ static AttrStack *stack_of_stacks_top = NULL;

static void attr_express_begin(int attr, char *param);
static void attr_express_end(int attr, char *param);



static int attr_find(AttrStack *stack, int findattr){
	int i;
	for (i = stack->tos; i >= 0; i--)
		if (stack->attr_stack[i] == findattr)
		{
			return i;
		}
	return -1;
}


static int attrstack_find_attr(int findattr, char **paramp){
	AttrStack *stack = stack_of_stacks_top;

	while (stack)
	{
		int index = attr_find(stack, findattr);
		if (index >= 0) 
		{
			*paramp = stack->attr_stack_params[index];
			return TRUE;
		}
		stack = stack->prev;
	}
	return FALSE;
}

static void attr_pull_out(AttrStack *stack, int index)
{
	int j;

	for (j = stack->tos; j >= index; j--)
	{
		attr_express_end(stack->attr_stack[j], stack->attr_stack_params[j]);
	}

	if (stack->attr_stack_params[index]) 
		yygwBRFXA(stack->attr_stack_params[index]);
	for (j = index; j < stack->tos; j++) 
	{
		stack->attr_stack[j] = stack->attr_stack[j + 1];
		stack->attr_stack_params[j] = stack->attr_stack_params[j + 1];
	}
	stack->tos--;

	for (j = index; j <= stack->tos; j++) 
	{
		attr_express_begin(stack->attr_stack[j], stack->attr_stack_params[j]);
	}
	return;
}

static void attr_pop_internal(AttrStack *stack, int attr){

	if (stack->tos >= 0)
	{
		char *param = stack->attr_stack_params[stack->tos];

		attr_express_end(attr, param);

		if (param)
		{
			yygwBRFXA(param);
		}

		stack->tos--;
	}
}



static void attr_express_begin(int attr, char *param)
{
	switch (attr)
	{
	case ATTR_BOLD:
		if (safe_printf(0, LVVzhfjUd->bold_begin))
		{
			fprintf(stderr, TOO_MANY_ARGS, "bold_begin");
		};
		break;
	case ATTR_ITALIC:
		if (safe_printf(0, LVVzhfjUd->italic_begin))
		{
			fprintf(stderr, TOO_MANY_ARGS, "italic_begin");
		};
		break;


	case ATTR_THICK_UL:
	case ATTR_WAVE_UL:
	case ATTR_DASH_UL:
	case ATTR_DOT_UL:
	case ATTR_DOT_DASH_UL:
	case ATTR_2DOT_DASH_UL:
	case ATTR_WORD_UL:
	case ATTR_UNDERLINE:
		if (safe_printf(0, LVVzhfjUd->underline_begin))
		{
			fprintf(stderr, TOO_MANY_ARGS, "underline_begin");
		};
		break;

	case ATTR_DOUBLE_UL:
		if (safe_printf(0, LVVzhfjUd->dbl_underline_begin))
		{
			fprintf(stderr, TOO_MANY_ARGS, "dbl_underline_begin");
		};
		break;

	case ATTR_FONTSIZE:
		op_begin_std_fontsize(LVVzhfjUd, atoi(param));
		break;

	case ATTR_FONTFACE:
		if (safe_printf(1, LVVzhfjUd->font_begin, param))
		{
			fprintf(stderr, TOO_MANY_ARGS, "font_begin");
		};
		break;

	case ATTR_FOREGROUND:
		if (safe_printf(1, LVVzhfjUd->foreground_begin, param))
		{
			fprintf(stderr, TOO_MANY_ARGS, "foreground_begin");
		};
		break;

	case ATTR_BACKGROUND:
		if (!ayLgEFdbE)
			if (safe_printf(1, LVVzhfjUd->background_begin, param))
			{
				fprintf(stderr, TOO_MANY_ARGS, "background_begin");
			};
		break;

	case ATTR_SUPER:
		if (safe_printf(0, LVVzhfjUd->superscript_begin))
		{
			fprintf(stderr, TOO_MANY_ARGS, "superscript_begin");
		};
		break;
	case ATTR_SUB:
		if (safe_printf(0, LVVzhfjUd->subscript_begin))
		{
			fprintf(stderr, TOO_MANY_ARGS, "subscript_begin");
		};
		break;

	case ATTR_STRIKE:
		if (safe_printf(0, LVVzhfjUd->strikethru_begin))
		{
			fprintf(stderr, TOO_MANY_ARGS, "strikethru_begin");
		};
		break;

	case ATTR_DBL_STRIKE:
		if (safe_printf(0, LVVzhfjUd->dbl_strikethru_begin))
		{
			fprintf(stderr, TOO_MANY_ARGS, "dbl_strikethru_begin");
		};
		break;

	case ATTR_EXPAND:
		if (safe_printf(1, LVVzhfjUd->expand_begin, param))
		{
			fprintf(stderr, TOO_MANY_ARGS, "expand_begin");
		};
		break;

	case ATTR_OUTLINE:
		if (safe_printf(0, LVVzhfjUd->outline_begin))
		{
			fprintf(stderr, TOO_MANY_ARGS, "outline_begin");
		};
		break;
	case ATTR_SHADOW:
		if (safe_printf(0, LVVzhfjUd->shadow_begin))
		{
			fprintf(stderr, TOO_MANY_ARGS, "shadow_begin");
		};
		break;
	case ATTR_EMBOSS:
		if (safe_printf(0, LVVzhfjUd->emboss_begin))
		{
			fprintf(stderr, TOO_MANY_ARGS, "emboss_begin");
		};
		break;
	case ATTR_ENGRAVE:
		if (safe_printf(0, LVVzhfjUd->engrave_begin))
		{
			fprintf(stderr, TOO_MANY_ARGS, "engrave_begin");
		};
		break;

	case ATTR_CAPS:
		if (LVVzhfjUd->simulate_all_caps)
		{
			simulate_allcaps = TRUE;
		}
		else
		{
			if (LVVzhfjUd->all_caps_begin)
				if (safe_printf(0, LVVzhfjUd->all_caps_begin))
				{
					fprintf(stderr, TOO_MANY_ARGS, "all_caps_begin");
				}
		}
		break;

	case ATTR_SMALLCAPS:
		if (LVVzhfjUd->simulate_small_caps)
		{
			simulate_smallcaps = TRUE;
		}
		else
		{
			if (LVVzhfjUd->small_caps_begin)
				if (safe_printf(0, LVVzhfjUd->small_caps_begin))
				{
					fprintf(stderr, TOO_MANY_ARGS, "small_caps_begin");
				};
		}
		break;
	}
}


static void attr_express_end(int attr, char *param)
{
	switch (attr)
	{
	case ATTR_BOLD:
		if (safe_printf(0, LVVzhfjUd->bold_end))
		{
			fprintf(stderr, TOO_MANY_ARGS, "bold_end");
		};
		break;
	case ATTR_ITALIC:
		if (safe_printf(0, LVVzhfjUd->italic_end))
		{
			fprintf(stderr, TOO_MANY_ARGS, "italic_end");
		};
		break;

	/* Various underlines, they all resolve to HTML's </u> */
	case ATTR_THICK_UL:
	case ATTR_WAVE_UL:
	case ATTR_DASH_UL:
	case ATTR_DOT_UL:
	case ATTR_DOT_DASH_UL:
	case ATTR_2DOT_DASH_UL:
	case ATTR_WORD_UL:
	case ATTR_UNDERLINE:
		if (safe_printf(0, LVVzhfjUd->underline_end))
		{
			fprintf(stderr, TOO_MANY_ARGS, "underline_end");
		};
		break;

	case ATTR_DOUBLE_UL:
		if (safe_printf(0, LVVzhfjUd->dbl_underline_end))
		{
			fprintf(stderr, TOO_MANY_ARGS, "dbl_underline_end");
		};
		break;

	case ATTR_FONTSIZE:
		wwIVaoSAs(LVVzhfjUd, atoi(param));
		break;

	case ATTR_FONTFACE:
		if (safe_printf(0, LVVzhfjUd->font_end))
		{
			fprintf(stderr, TOO_MANY_ARGS, "font_end");
		};
		break;

	case ATTR_FOREGROUND:
		if (safe_printf(0, LVVzhfjUd->foreground_end))
		{
			fprintf(stderr, TOO_MANY_ARGS, "foreground_end");
		};
		break;
	case ATTR_BACKGROUND:
		if (!ayLgEFdbE)
			if (safe_printf(0, LVVzhfjUd->background_end))
			{
				fprintf(stderr, TOO_MANY_ARGS, "background_end");
			};
		break;

	case ATTR_SUPER:
		if (safe_printf(0, LVVzhfjUd->superscript_end))
		{
			fprintf(stderr, TOO_MANY_ARGS, "superscript_end");
		};
		break;
	case ATTR_SUB:
		if (safe_printf(0, LVVzhfjUd->subscript_end))
		{
			fprintf(stderr, TOO_MANY_ARGS, "subscript_end");
		};
		break;

	case ATTR_STRIKE:
		if (safe_printf(0, LVVzhfjUd->strikethru_end))
		{
			fprintf(stderr, TOO_MANY_ARGS, "strikethru_end");
		};
		break;

	case ATTR_DBL_STRIKE:
		if (safe_printf(0, LVVzhfjUd->dbl_strikethru_end))
		{
			fprintf(stderr, TOO_MANY_ARGS, "dbl_strikethru_end");
		};
		break;

	case ATTR_OUTLINE:
		if (safe_printf(0, LVVzhfjUd->outline_end))
		{
			fprintf(stderr, TOO_MANY_ARGS, "outline_end");
		};
		break;
	case ATTR_SHADOW:
		if (safe_printf(0, LVVzhfjUd->shadow_end))
		{
			fprintf(stderr, TOO_MANY_ARGS, "shadow_end");
		};
		break;
	case ATTR_EMBOSS:
		if (safe_printf(0, LVVzhfjUd->emboss_end))
		{
			fprintf(stderr, TOO_MANY_ARGS, "emboss_end");
		};
		break;
	case ATTR_ENGRAVE:
		if (safe_printf(0, LVVzhfjUd->engrave_end))
		{
			fprintf(stderr, TOO_MANY_ARGS, "engrave_end");
		};
		break;

	case ATTR_EXPAND:
		if (safe_printf(0, LVVzhfjUd->expand_end))
		{
			fprintf(stderr, TOO_MANY_ARGS, "expand_end");
		};
		break;

	case ATTR_CAPS:
		if (LVVzhfjUd->simulate_all_caps)
		{
			simulate_allcaps = FALSE;
		}
		else
		{
			if (LVVzhfjUd->all_caps_end)
				if (safe_printf(0, LVVzhfjUd->all_caps_end))
				{
					fprintf(stderr, TOO_MANY_ARGS, "all_caps_end");
				};
		}
		break;

	case ATTR_SMALLCAPS:
		if (LVVzhfjUd->simulate_small_caps)
		{
			simulate_smallcaps = FALSE;
		}
		else
		{
			if (LVVzhfjUd->small_caps_end)
				if (safe_printf(0, LVVzhfjUd->small_caps_end))
				{
					fprintf(stderr, TOO_MANY_ARGS, "small_caps_end");
				};
		}
		break;
	}
}



/*========================================================================
 * Name:	attr_push
 * Purpose:	Pushes an attribute onto the current attribute stack.
 * Args:	Attribute number, optional string parameter.
 * Returns:	None.
 *=======================================================================*/

void attr_push(int attr, char *param)
{
	AttrStack *stack = stack_of_stacks_top;
	int i;
	char *oldparam;

	/*fprintf(stderr, "attr_push: [%d] [%s]\n", attr, param);*/

	if (!stack)
	{
		warning_handler("No stack to push attribute onto");
		return;
	}

	if ((i = attr_find(stack, attr)) != -1) {
		attr_pull_out(stack, i);
	}

	if (stack->tos >= MAX_ATTRS - 1)
	{
		fprintf(stderr, "Too many attributes!\n");
		return;
	}

	starting_body();
	starting_text();

	++stack->tos;
	stack->attr_stack[stack->tos] = attr;
	if (param)
	{
		stack->attr_stack_params[stack->tos] = my_strdup(param);
	}
	else
	{
		stack->attr_stack_params[stack->tos] = NULL;
	}

	attr_express_begin(attr, param);
}

int attr_find_pop(int findattr){
	int i;
	AttrStack *stack = stack_of_stacks_top;

	if (!stack)
	{
		warning_handler("no stack to pop attributes from");
		return FALSE;
	}

	if ((i = attr_find(stack, findattr)) < 0)
	{
		return FALSE;
	}
	attr_pull_out(stack, i);
	return TRUE;
}

char * attr_get_param(int attr){
	int i;
	AttrStack *stack = stack_of_stacks_top;
	if (!stack)
	{
		if (attr != ATTR_ENCODING){

			warning_handler("No stack to get attribute from");
		}
		return NULL;
	}

	if ((i = attr_find(stack, attr)) >= 0) {
		return stack->attr_stack_params[i];
	}
	return NULL;
}


void attrstack_copy_all(AttrStack *src, AttrStack *dest){
	int i;

	KOOOPP(src);
	KOOOPP(dest);

	for (i = 0; i <= src->tos; i++)
	{
		dest->attr_stack[i] = src->attr_stack[i];

		char *param = src->attr_stack_params[i];
		if (param)
		{
			dest->attr_stack_params[i] = my_strdup(param);
		}
		else
		{
			dest->attr_stack_params[i] = NULL;
		}
	}

	dest->tos = src->tos;
}


void attrstack_unexpress_all(AttrStack *stack){
	int i;

	KOOOPP(stack);

	for (i = stack->tos; i >= 0; i--)
	{
		attr_express_end(stack->attr_stack[i], stack->attr_stack_params[i]);
	}
}


void attrstack_push(){
	AttrStack *new_stack;

	new_stack = (AttrStack *) my_malloc(sizeof(AttrStack));

	if (new_stack == NULL) 
	{
		warning_handler("out of memory");
		return;
	}

	memset((void *) new_stack, 0, sizeof(AttrStack));

	if (!stack_of_stacks)
	{
		stack_of_stacks = new_stack;
		new_stack->tos = -1;
	} 
	else{

		attrstack_copy_all(stack_of_stacks_top, new_stack);
	}
		
	new_stack->prev = stack_of_stacks_top;
	stack_of_stacks_top = new_stack;
}


int attr_pop(int attr){
	AttrStack *stack = stack_of_stacks_top;

	if (!stack)
	{
		warning_handler("no stack to pop attribute from");
		return FALSE;
	}

	if (stack->tos >= 0 && stack->attr_stack[stack->tos] == attr)
	{
		attr_pop_internal(stack, attr);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}



/*========================================================================
 * Name:	attr_read
 * Purpose:	Reads but leaves in place the top attribute of the top
 * 		attribute stack.
 * Args:	None.
 * Returns:	Attribute number.
 *=======================================================================*/

int
attr_read()
{
	AttrStack *stack = stack_of_stacks_top;
	if (!stack)
	{
		warning_handler("no stack to read attribute from");
		return FALSE;
	}

	if (stack->tos >= 0)
	{
		int attr = stack->attr_stack [stack->tos];
		return attr;
	}
	else
	{
		return ATTR_NONE;
	}
}


/*========================================================================
 * Name:	attr_drop_all
 * Purpose:	Empty top attr stack without unexpressing attributes.
 * Args:	None.
 * Returns:	None.
 *=======================================================================*/

void
attr_drop_all()
{
	AttrStack *stack = stack_of_stacks_top;
	if (!stack)
	{
		warning_handler("no stack to drop all attributes from");
		return;
	}

	while (stack->tos >= 0)
	{
		char *param = stack->attr_stack_params [stack->tos];
		if (param)
		{
			yygwBRFXA(param);
		}
		stack->tos--;
	}
}


/*========================================================================
 * Name:	attrstack_drop
 * Purpose:	Removes the top AttrStack from the stack of stacks, undoing
 *		all attributes that it had in it.
 * Args:	None.
 * Returns:	None.
 *=======================================================================*/

void
attrstack_drop()
{
	AttrStack *stack = stack_of_stacks_top;
	if (!stack)
	{
		warning_handler("no attr-stack to drop");
		return;
	}

	attr_pop_all();

	if (stack->prev == NULL)
	{
		stack_of_stacks = NULL;
	}
	stack_of_stacks_top = stack->prev;

	yygwBRFXA((void *) stack);

	/* Re-set attributes for parent state */
	if (stack_of_stacks_top)
	{
		attrstack_express_all(/*stack_of_stacks_top*/);
	}
}

/*========================================================================
 * Name:	attr_pop_all
 * Purpose:	Routine to undo all attributes heretofore applied,
 *		also reversing the order in which they were applied.
 * Args:	None.
 * Returns:	None.
 *=======================================================================*/

void
attr_pop_all()
{
	AttrStack *stack = stack_of_stacks_top;
	if (!stack)
	{
		warning_handler("no stack to pop from");
		return;
	}

	while (stack->tos >= 0)
	{
		attr_pop_internal(stack, stack->attr_stack[stack->tos]);
	}
}

/*========================================================================
 * Name:	attrstack_express_all
 * Purpose:	Routine to re-express all attributes heretofore applied.
 * Args:	None.
 * Returns:	None.
 * Notes:	This is needed by attrstack_push, but also for \cell, which
 * 		often occurs within a brace group, yet HTML uses <td></td>
 *		which clear attribute info within that block.
 *=======================================================================*/

void
attrstack_express_all()
{
	AttrStack *stack = stack_of_stacks_top;
	int i;

	if (!stack)
	{
		warning_handler("no stack to pop from");
		return;
	}

	for (i = 0; i <= stack->tos; i++)
	{
		attr_express_begin(stack->attr_stack[i], stack->attr_stack_params[i]);
	}
}

/*========================================================================
 * Name:	safe_printf
 * Purpose:	Prevents format string attack and writes empty string
		instead of NULL.
 * Args:	Number of parameters (without a string), string to write,
		additional parameters to print (have to be strings).
 * Returns:	Returns 0 if number of not escaped '%' in string
		 is not greater than nr, else returns -1
 *=======================================================================*/


int
safe_printf(int nr, char *string, ...)
{

	char *s;
	int i = 0, ret_code = 0;
	va_list arguments;

	if (string == NULL)
		;
	else
	{
		va_start(arguments, string);

		for (; nr > 0; nr--)
		{
			while (string[i] != '\0' && (string[i] != '%' || (string[i] == '%' && (i != 0 && string[i - 1] == '\\'))))
			{
				if (string[i] != '\\' || string[i + 1] != '%')
				{
					printf("%c", string[i]);
				}
				i++;
			}

			if (string[i] != '\0')
			{
				s = va_arg(arguments, char *);
				printf("%s", s);
				i++;
			}
		}
		va_end(arguments);

		while (string[i] != '\0')
		{
			if (string[i] != '\\' || (string[i] == '\\' && string[i + 1] != '%'))
			{
				if (string[i] != '%' || (string[i] == '%' && (i != 0 && string[i - 1] == '\\')))
				{
					printf("%c", string[i]);
				}
				else
				{
					ret_code = -1;
				}
			}
			i++;
		}
	}

	return ret_code;
}

/*========================================================================
 * Name:	assemble_string
 * Purpose:	See Returns
 * Args:	String to return and int to put into first parameter.
 * Returns:	Returns first parameter where first not escaped
		character % is substituted with second parameter.
 *=======================================================================*/

char *
assemble_string(char *string, int nr)
{

	char *s, tmp[20];
	int i = 0, j = 0;

	if (string == NULL)
	{
		return NULL;
	}
	else
	{
		s = my_malloc(strlen(string) + 1 + 12/* Number of characters that can be in int type (including '\0') - AF */);
		while (string[i] != '\0' && (string[i] != '%' || (string[i] == '%' && (i != 0 && string[i - 1] == '\\'))))
		{
			if (string[i] != '\\' || string[i + 1] != '%')
			{
				s[j] = string[i];
				j++;
			}
			i++;
		}

		if (string[i] != '\0')
		{
			snprintf(tmp, 20, "%d", nr);
			strcpy(&s[j], tmp);
			j = j + strlen(tmp);
		}

		while (string[i] != '\0')
		{
			if (string[i] != '\\' || (string[i] == '\\' && string[i + 1] != '%'))
			{
				if (string[i] != '%' || (string[i] == '%' && (i != 0 && string[i - 1] == '\\')))
				{
					s[j] = string[i];
					j++;
				}
				else
				{
					/* More than one char % occured */
				}
			}
			i++;
		}
	}

	s[j] = '\0';

	return s;
}


/*========================================================================
 * Name:	add_to_collection
 * Purpose:	Adds (substitutes) element under index nr.
 * Args:	Collection, index, text to add.
 * Returns:	Collection.
 *=======================================================================*/

Collection *
add_to_collection(Collection *col, int nr, const char *text)
{
	Collection *c = col;

	if (col == NULL)
	{
		col = (Collection *)my_malloc(sizeof(Collection));
		col->nr = nr;
		col->text = text;
		col->next = NULL;
	}
	else
	{
		do
		{
			if (c->nr == nr){

				c->text = text;

				return col;
			}

			if (c->next == NULL)
			{
				break;
			}
			c = c->next;
		}
		while (1);

		c->next = (Collection *)my_malloc(sizeof(Collection));
		c->next->nr = nr;
		c->next->text = text;
		c->next->next = NULL;
	}

	return col;
}

/*========================================================================
 * Name:	get_from_collection
 * Purpose:	Search for element under index nr.
 * Args:	Collection, index.
 * Returns:	NULL or found elemet.
 *=======================================================================*/

const char *
get_from_collection(Collection *c, int nr)
{
	while (c != NULL)
	{
		if (c->nr == nr)
		{
			return c->text;
		}

		c = c->next;
	}

	return NULL;
}



void
free_collection(Collection *c)
{
	Collection *c2;

	while (c != NULL)
	{
		c2 = c->next;
		yygwBRFXA((void *)c);
		c = c2;
	}
}
