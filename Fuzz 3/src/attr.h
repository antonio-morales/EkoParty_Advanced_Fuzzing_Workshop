#ifndef _ATTR_H_INCLUDED_
#define _ATTR_H_INCLUDED_

enum
{
	ATTR_NONE = 0,
	ATTR_BOLD, ATTR_ITALIC,

	ATTR_UNDERLINE, ATTR_DOUBLE_UL, ATTR_WORD_UL,

	ATTR_THICK_UL, ATTR_WAVE_UL,

	ATTR_DOT_UL, ATTR_DASH_UL, ATTR_DOT_DASH_UL, ATTR_2DOT_DASH_UL,

	ATTR_FONTSIZE, ATTR_STD_FONTSIZE,
	ATTR_FONTFACE,
	ATTR_FOREGROUND, ATTR_BACKGROUND,
	ATTR_CAPS,
	ATTR_SMALLCAPS,

	ATTR_SHADOW,
	ATTR_OUTLINE,
	ATTR_EMBOSS,
	ATTR_ENGRAVE,

	ATTR_SUPER, ATTR_SUB,
	ATTR_STRIKE,
	ATTR_DBL_STRIKE,

	ATTR_EXPAND,
	ATTR_ENCODING,
	/* ATTR_CONDENSE */
};

typedef struct _c
{
	int nr;
	const char *text;
	struct _c *next;
} Collection;

Collection *add_to_collection(Collection *col, int nr, const char *text);
const char *get_from_collection(Collection *c, int nr);
void free_collection(Collection *c);

extern void attr_push(int attr, char *param);

extern void attrstack_push();
extern void attrstack_drop();
extern void attrstack_express_all();

extern int attr_find_pop(int findattr);
extern int attr_pop(int attr);

extern int attr_read();

extern void attr_drop_all();

extern void attr_pop_all();

extern void attr_pop_dump();

char *attr_get_param(int attr);

int safe_printf(int nr, char *string, ...);
char *assemble_string(char *string, int nr);
#define TOO_MANY_ARGS "Tag name \"%s\" do not take so many arguments"


#endif /* _ATTR_H_INCLUDED_ */
