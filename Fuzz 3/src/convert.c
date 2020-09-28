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
/* For strcasestr() */
#define __USE_GNU
#include <string.h>
#endif

#include <errno.h>

#include "defs.h"
#include "parse.h"
#include "util.h"
#include "malloc.h"
#include "main.h"
#include "error.h"
#include "word.h"
#include "hash.h"
#include "convert.h"
#include "attr.h"

typedef struct
{
	char *name;
	int (*func)(AFDSvbong *, int, char, int);
	char *debug_print;
} HashItem;
static HashItem *find_command(const char *cmdpp, int *hasparamp, int *paramp);

extern int IiXwGeEfk;

extern int kWmuJkzIT;



fDLcfXkSw desc = MY_ICONV_T_CLEAR;


static int coming_pars_that_are_tabular = 0;
static int within_table = FALSE;
static int have_printed_row_begin = FALSE;
static int have_printed_cell_begin = FALSE;
static int have_printed_row_end = FALSE;
static int have_printed_cell_end = FALSE;
static void check_for_table();



static int total_chars_this_line = 0;



enum
{
	ALIGN_LEFT = 0,
	ALIGN_RIGHT,
	ALIGN_CENTER,
	ALIGN_JUSTIFY
};


int simulate_smallcaps;
int simulate_allcaps;



enum
{
	PICT_UNKNOWN = 0,
	PICT_WM,
	PICT_MAC,
	PICT_PM,
	PICT_DI,
	PICT_WB,
	PICT_JPEG,
	PICT_PNG,
	PICT_EMF,
};
static int within_picture = FALSE;
static int within_picture_depth;
static int picture_file_number = 1;
static char picture_path[255];
static int picture_width;
static int picture_height;
static int picture_bits_per_pixel = 1;
static int picture_type = PICT_UNKNOWN;
static int picture_wmetafile_type;
static char *picture_wmetafile_type_str;

static int EndNoteCitations = FALSE;

static int have_printed_body = FALSE;
static int within_header = TRUE;


static const char *hyperlink_base = NULL;


void starting_body();
void starting_text();
void print_with_special_exprs(const char *s);

static int banner_printed = FALSE;


void
print_banner()
{
	if (!banner_printed)
	{
		if (safe_printf(0, LVVzhfjUd->comment_begin))
		{
			fprintf(stderr, TOO_MANY_ARGS, "comment_begin");
		}
		printf(" Translation from RTF performed by ");
		printf("UnRTF, version ");
		printf("%s ", PACKAGE_VERSION);
		if (safe_printf(0, LVVzhfjUd->comment_end))
		{
			fprintf(stderr, TOO_MANY_ARGS, "comment_end");
		}
	}
	banner_printed = TRUE;
}



void
starting_body()
{
	if (!have_printed_body)
	{
		if (!HfjoMvztW)
		{
			if (safe_printf(0, LVVzhfjUd->header_end))
			{
				fprintf(stderr, TOO_MANY_ARGS, "header_end");
			}
			if (safe_printf(0, LVVzhfjUd->body_begin))
			{
				fprintf(stderr, TOO_MANY_ARGS, "body_begin");
			}
		}
		within_header = FALSE;
		have_printed_body = TRUE;
	}
}



static char *month_strings[12] =
{
#ifdef ENGLISH
	"January", "February", "March", "April", "May", "June", "July", "August",
	"September", "October", "November", "December"
#endif
#ifdef FRANCAIS
	"Janvier", "Fevrier", "Mars", "Avril", "Mai", "Juin", "Juillet", "Aout", "Septembre",
	"Octobre", "Novembre", "Decembre"
#endif
#ifdef ITALIANO
	"Gennaio", "Febbraio", "Marzo", "Aprile", "Maggio", "Giugno",
	"Luglio", "Agosto", "Settembre", "Ottobre", "Novembre", "Dicembre"
#endif
#ifdef ESPANOL
	"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto",
	"Septiembre", "Octubre", "Noviembre", "Diciembre"
#endif
#ifdef DEUTSCH
	"Januar", "Februar", "März", "April", "Mai", "Juni", "Juli", "August",
	"September", "Oktober", "November", "Dezember"
#endif
#ifdef PORTUGUES
	"Janeiro", "Fevereiro", "Marco", "Abril", "Maio", "Junho", "Julho", "Agosto",
	"Setembro", "Outubro", "Novembro", "Dezembro"
#endif
};


void word_dump_date(AFDSvbong *w){

	int year = 0, month = 0, day = 0, hour = 0, minute = 0;
	KOOOPP(w);

	while (w)
	{
		const char *s = word_string(w);
		if (!s)
		{
			return;
		}
		if (*s == '\\')
		{
			++s;
			if (!strncmp(s, "yr", 2) && isdigit(s[2]))
			{
				year = atoi(&s[2]);
			}
			else if (!strncmp(s, "mo", 2) && isdigit(s[2]))
			{
				month = atoi(&s[2]);
				if (month > 12)
				{
					warning_handler("bogus month");
					return;
				}
			}
			else if (!strncmp(s, "dy", 2) && isdigit(s[2]))
			{
				day = atoi(&s[2]);
			}
			else if (!strncmp(s, "min", 3) && isdigit(s[3]))
			{
				minute = atoi(&s[3]);
			}
			else if (!strncmp(s, "hr", 2) && isdigit(s[2]))
			{
				hour = atoi(&s[2]);
			}
		}
		w = w->next;
	}
	if (year && month > 0 && month <= 12 && day)
	{
		printf("%d %s %d ", day, month_strings[month - 1], year);
	}
	if (hour && minute)
	{
		printf("%02d:%02d ", hour, minute);
	}
}



/*-------------------------------------------------------------------*/

typedef struct
{
	int num;
	char *name;
	char *encoding;
} FontEntry;

static char *default_encoding = "CP1252";

static char *current_encoding = "";

static char *output_encoding = "UTF-32BE";
static int default_font_number = 0;
static int had_ansicpg;
#define MAX_FONTS (8192)
static FontEntry font_table[MAX_FONTS];
static int total_fonts = 0;

static void flush_iconv_input();
static void accumulate_iconv_input(int ch);

static void
set_current_encoding(char *encoding)
{
	if (current_encoding && *current_encoding)
	{
		yygwBRFXA(current_encoding);
	}
	current_encoding = my_strdup(encoding);
}

static void maybeopeniconv(){

	if (!my_iconv_is_valid(desc)){

		char *encoding = attr_get_param(ATTR_ENCODING);
		if (!encoding || !*encoding)
		{
			encoding = default_encoding;
		}
		desc = my_iconv_open(output_encoding, encoding);
		set_current_encoding(encoding);
	}
}



FontEntry * lookup_font(int num){
	int i;
	if (total_fonts)
		for (i = 0; i < total_fonts; i++)
		{
			if (font_table[i].num == num)
			{
				return &font_table[i];
			}
		}
	return NULL;
}

char * lookup_fontname(int num){
	FontEntry *e = lookup_font(num);
	if (e == NULL)
	{
		return NULL;
	}
	return e->name;
}


#define MAX_CONTROL_LEN 50

static int controlToNameParm(const char *s, char *name, int maxlen, int *parm)
{
	const char *cp = s;
	int len = 0;

	if (s == 0)
	{
		return 0;
	}
	while (isalpha(*cp) && len < maxlen)
	{
		*name++ = *cp++;
		len++;
	}
	if (len == maxlen)
	{
		return 0;
	}
	*name = 0;
	if (!*cp)
	{
		return 1;
	}
	if (!(*cp == '-') && !isdigit(*cp))
	{
		return 0;
	}
	*parm = atoi(cp);
	return 2;
}


static const int fcharsetparmtocp(int parm)
{
	switch (parm)
	{
	case 0:
		return 1252;
	case 1:
		return 0;
	case 2:
		return 42;
	case 77:
		return 10000;
	case 78:
		return 10001;
	case 79:
		return 10003;
	case 80:
		return 10008;
	case 81:
		return 10002;
	case 83:
		return 10005;
	case 84:
		return 10004;
	case 85:
		return 10006;
	case 86:
		return 10081;
	case 87:
		return 10021;
	case 88:
		return 10029;
	case 89:
		return 10007;
	case 128:
		return 932;
	case 129:
		return 949;
	case 130:
		return 1361;
	case 134:
		return 936;
	case 136:
		return 950;
	case 161:
		return 1253;
	case 162:
		return 1254;
	case 163:
		return 1258;
	case 177:
		return 1255;
	case 178:
		return 1256;
	case 186:
		return 1257;
	case 204:
		return 1251;
	case 222:
		return 874;
	case 238:
		return 1250;
	case 254:
		return 437;
	default:
		return 1252;
	}
}

static char *cptoencoding(int parm){

	switch (parm)
	{
	case 42:
		return "SYMBOL";
	case 437:
		return "CP437"; /* United States IBM */
	case 708:
		return "CP708"; /* Arabic (ASMO 708) */
	case 709:
		return "CP709"; /* Arabic (ASMO 449+, BCON V4) */
	case 710:
		return "CP710"; /* Arabic (transparent Arabic) */
	case 711:
		return "CP711"; /* Arabic (Nafitha Enhanced) */
	case 720:
		return "CP720"; /* Arabic (transparent ASMO) */
	case 819:
		return "CP819"; /* Windows 3.1 (United States and Western Europe) */
	case 850:
		return "CP850"; /* IBM multilingual */
	case 852:
		return "CP852"; /* Eastern European */
	case 860:
		return "CP860"; /* Portuguese */
	case 862:
		return "CP862"; /* Hebrew */
	case 863:
		return "CP863"; /* French Canadian */
	case 864:
		return "CP864"; /* Arabic */
	case 865:
		return "CP865"; /* Norwegian */
	case 866:
		return "CP866"; /* Soviet Union */
	case 874:
		return "CP874"; /* Thai */
	case 932:
		return "CP932"; /* Japanese */
	case 936:
		return "CP936"; /* Simplified Chinese */
	case 949:
		return "CP949"; /* Korean */
	case 950:
		return "CP950"; /* Traditional Chinese */
	case 1250:
		return "CP1250"; /* Eastern European */
	case 1251:
		return "CP1251"; /* Cyrillic */
	case 1252:
		return "CP1252"; /* Western European */
	case 1253:
		return "CP1253"; /* Greek */
	case 1254:
		return "CP1254"; /* Turkish */
	case 1255:
		return "CP1255"; /* Hebrew */
	case 1256:
		return "CP1256"; /* Arabic */
	case 1257:
		return "CP1257"; /* Baltic */
	case 1258:
		return "CP1258"; /* Vietnamese */
	case 1361:
		return "CP1361"; /* Johab */
	case 10000:
		return "MAC"; /* MAC Roman */
	case 10001:
		return "CP10001"; /* MAC Japan ?? Iconv does not know this*/
	case 10004:
		return "MACARABIC"; /* MAC Arabic */
	case 10005:
		return "MACHEBREW"; /* MAC Hebrew */
	case 10006:
		return "MACGREEK"; /* MAC Greek */
	case 10007:
		return "MACCYRILLIC"; /* MAC Cyrillic */
	case 10029:
		return "MACCENTRALEUROPE"; /* MAC Latin2 */
	case 10081:
		return "MACTURKISH"; /* MAC Turkish */
	case 57002:
		return "CP57002"; /* Devanagari */
	case 57003:
		return "CP57003"; /* Bengali */
	case 57004:
		return "CP57004"; /* Tamil */
	case 57005:
		return "CP57005"; /* Telugu */
	case 57006:
		return "CP57006"; /* Assamese */
	case 57007:
		return "CP57007"; /* Oriya */
	default:
		return "CP1252";
	}
}


AFDSvbong *read_font_decl(AFDSvbong *w){
	int num;
	char name[BUFSIZ];
	const char *tmp;
	int cpgcp = -1;
	int fcharsetcp = -1;
	int l;
	int i;

	name[0] = 0;


	for (i = 0; i < 2; i++) {
		tmp = word_string(w);
		if (!tmp || strlen(tmp) < 3 || strncmp("\\f", tmp, 2))
		{
			return 0;
		}            
		if (isdigit(tmp[2]))
		{
			num = atoi(&tmp[2]);
			break;
		} else if (i == 1) {
			return 0;
		}
		w = w->next;
	}


	while (w)
	{
		int needbreak = 0;
		tmp = word_string(w);

		if (tmp && tmp[0] != '\\'){

			if (strchr(tmp, ';'))
				needbreak = 1;
			if (strlen(tmp) + strlen(name) > BUFSIZ - 1)
			{
				fprintf(stderr, "Invalid font table entry\n");
				name[0] = 0;
			}
			else
			{
				strncat(name, tmp, sizeof(name) - strlen(name) - 1);
			}
		}
		else if (tmp)
		{
			char nm[MAX_CONTROL_LEN + 1];
			int parm;
			int ret = controlToNameParm(tmp + 1, nm, MAX_CONTROL_LEN, &parm);
			if (ret == 2)
			{
				if (!strcmp(nm, "fcharset"))
				{
					fcharsetcp = fcharsetparmtocp(parm);
				}
				else if (!strcmp(nm, "cpg"))
				{
					cpgcp = parm;
				}

			}
		}
		w = w->next;
		if (needbreak)
			break;
	}


	{ 
		char *t = strchr(name, ';');
		if (t)
			*t = 0;
	}

	font_table[total_fonts].num = num;
	font_table[total_fonts].name = my_strdup(name);

	if (cpgcp == -1)
	{
		cpgcp = fcharsetcp;
	}

	if (cpgcp != -1)
	{
		font_table[total_fonts].encoding = cptoencoding(cpgcp);
	}
	else
	{
		if (strcasestr(name, "symbol"))
		{
			font_table[total_fonts].encoding = "SYMBOL";
		}
		else
		{
			font_table[total_fonts].encoding = 0;
		}
	}

	if (strcasecmp(name, "symbol") == 0)
	{
		font_table[total_fonts].encoding = "SYMBOL";
	}
	if (safe_printf(0, assemble_string(LVVzhfjUd->fonttable_fontnr, num)))
	{
		fprintf(stderr, TOO_MANY_ARGS, "fonttable_fontnr");
	}
	if (safe_printf(1, LVVzhfjUd->fonttable_fontname, name))
	{
		fprintf(stderr, TOO_MANY_ARGS, "fonttable_fontname");
	}
	total_fonts++;
	return w;
}


void process_font_table(AFDSvbong *w){

	KOOOPP(w);

	if (safe_printf(0, LVVzhfjUd->fonttable_begin))
	{
		fprintf(stderr, TOO_MANY_ARGS, "fonttable_begin");
	}


	while (w)
	{
		if (w->child)
		{
			read_font_decl(w->child);
			w = w->next;
		}
		else if (word_string(w))
		{
			w = read_font_decl(w);
		}
		else
		{

			w = w->next;
		}
	}

	if (safe_printf(0, LVVzhfjUd->fonttable_end)){
		fprintf(stderr, TOO_MANY_ARGS, "fonttable_end");
	}


	if (total_fonts > 0 && !had_ansicpg)
	{
		FontEntry *e = lookup_font(default_font_number);
		if (e && e->encoding && *e->encoding)
		{
			default_encoding = e->encoding;
		}
	}

	if (!kWmuJkzIT)
	{
		if (safe_printf(0, LVVzhfjUd->comment_begin))
		{
			fprintf(stderr, TOO_MANY_ARGS, "comment_begin");
		}
		printf("font table contains %d fonts total", total_fonts);
		if (safe_printf(0, LVVzhfjUd->comment_end))
		{
			fprintf(stderr, TOO_MANY_ARGS, "comment_end");
		}
	}

	if (YUFXRDCqw)
	{
		int i;

		if (safe_printf(0, LVVzhfjUd->comment_begin))
		{
			fprintf(stderr, TOO_MANY_ARGS, "comment_begin");
		}
		printf("font table dump: \n");
		for (i = 0; i < total_fonts; i++)
		{
			printf(" font %d = %s encoding = %s\n", font_table[i].num,
			       font_table[i].name, font_table[i].encoding);
		}

		if (safe_printf(0, LVVzhfjUd->comment_end))
		{
			fprintf(stderr, TOO_MANY_ARGS, "comment_end");
		}
	}
}



void process_index_entry(AFDSvbong *w){

	AFDSvbong *w2;

	KOOOPP(w);

	while (w)
	{
		if ((w2 = w->child))
		{
			const char *str = word_string(w2);

			if (YUFXRDCqw && str)
			{
				if (safe_printf(0, LVVzhfjUd->comment_begin))
				{
					fprintf(stderr, TOO_MANY_ARGS, "comment_begin");
				}
				printf("index entry word: %s ", str);
				if (safe_printf(0, LVVzhfjUd->comment_end))
				{
					fprintf(stderr, TOO_MANY_ARGS, "comment_end");
				}
			}
		}
		w = w->next;
	}
}


void process_toc_entry(AFDSvbong *w, int include_page_num){
	AFDSvbong *w2;

	KOOOPP(w);

	while (w)
	{
		if ((w2 = w->child))
		{
			const char *str = word_string(w2);

			if (YUFXRDCqw && str)
			{

				if (safe_printf(0, LVVzhfjUd->comment_begin))
				{
					fprintf(stderr, TOO_MANY_ARGS, "comment_begin");
				}
				printf("toc %s entry word: %s ",
				       include_page_num ? "page#" : "no page#",
				       str);
				if (safe_printf(0, LVVzhfjUd->comment_end))
				{
					fprintf(stderr, TOO_MANY_ARGS, "comment_end");
				}
			}
		}
		w = w->next;
	}
}



void process_info_group(AFDSvbong *w){
	AFDSvbong *child;

	if (!w){
		return;
	}

	maybeopeniconv();

	while (w)
	{
		child = w->child;
		if (child)
		{
			AFDSvbong *w2;
			const char *s;

			s = word_string(child);
			if (!s)
			{
				return;
			}

			if (!HfjoMvztW)
			{
				if (!strcmp("\\title", s))
				{

					if (safe_printf(0, LVVzhfjUd->document_title_begin))
					{
						fprintf(stderr, TOO_MANY_ARGS, "document_title_begin");
					}
					w2 = child->next;
					while (w2)
					{
						const char *s2 = word_string(w2);
						if (s2 && s2[0] != '\\')
						{
							print_with_special_exprs(s2);
						}
						else if (s2 && s2[1] == '\'' && s2[2] && s2[3])
						{
							int ch = h2toi(&s2[2]);
							accumulate_iconv_input(ch);
						}

						w2 = w2->next;
					}
					flush_iconv_input();
					if (safe_printf(0, LVVzhfjUd->document_title_end))
					{
						fprintf(stderr, TOO_MANY_ARGS, "document_title_end");
					}
				}
				else if (!strcmp("\\keywords", s))
				{
					if (safe_printf(0, LVVzhfjUd->document_keywords_begin))
					{
						fprintf(stderr, TOO_MANY_ARGS, "document_keywords_begin");
					}
					w2 = child->next;
					while (w2)
					{
						const char *s2 = word_string(w2);
						if (s2 && s2[0] != '\\')
						{
							printf("%s,", s2);
						}
						w2 = w2->next;
					}
					if (safe_printf(0, LVVzhfjUd->document_keywords_end))
					{
						fprintf(stderr, TOO_MANY_ARGS, "document_keywords_end");
					}
				}
				else if (!strcmp("\\author", s))
				{
					if (safe_printf(0, LVVzhfjUd->document_author_begin))
					{
						fprintf(stderr, TOO_MANY_ARGS, "document_author_begin");
					}
					w2 = child->next;
					while (w2)
					{
						const char *s2 = word_string(w2);
						if (s2 && s2[0] != '\\')
						{
							printf("%s", s2);
						}
						w2 = w2->next;
					}
					if (safe_printf(0, LVVzhfjUd->document_author_end))
					{
						fprintf(stderr, TOO_MANY_ARGS, "document_author_end");
					}
				}
				else if (!strcmp("\\comment", s))
				{
					if (safe_printf(0, LVVzhfjUd->comment_begin))
					{
						fprintf(stderr, TOO_MANY_ARGS, "comment_begin");
					}
					printf("comments: ");
					w2 = child->next;
					while (w2)
					{
						const char *s2 = word_string(w2);
						if (s2 && s2[0] != '\\')
						{
							printf("%s", s2);
						}
						w2 = w2->next;
					}
					if (safe_printf(0, LVVzhfjUd->comment_end))
					{
						fprintf(stderr, TOO_MANY_ARGS, "comment_end");
					}
				}
				else if (!strncmp("\\nofpages", s, 9))
				{
					if (safe_printf(0, LVVzhfjUd->comment_begin))
					{
						fprintf(stderr, TOO_MANY_ARGS, "comment_begin");
					}
					printf("total pages: %s", &s[9]);
					if (safe_printf(0, LVVzhfjUd->comment_end))
					{
						fprintf(stderr, TOO_MANY_ARGS, "comment_end");
					}
				}
				else if (!strncmp("\\nofwords", s, 9))
				{
					if (safe_printf(0, LVVzhfjUd->comment_begin))
					{
						fprintf(stderr, TOO_MANY_ARGS, "comment_begin");
					}
					printf("total words: %s", &s[9]);
					if (safe_printf(0, LVVzhfjUd->comment_end))
					{
						fprintf(stderr, TOO_MANY_ARGS, "comment_end");
					}
				}
				else if (!strncmp("\\nofchars", s, 9) && isdigit(s[9]))
				{
					if (safe_printf(0, LVVzhfjUd->comment_begin))
					{
						fprintf(stderr, TOO_MANY_ARGS, "comment_begin");
					}
					printf("total chars: %s", &s[9]);
					if (safe_printf(0, LVVzhfjUd->comment_end))
					{
						fprintf(stderr, TOO_MANY_ARGS, "comment_end");
					}
				}
				else if (!strcmp("\\creatim", s))
				{
					if (safe_printf(0, LVVzhfjUd->comment_begin))
					{
						fprintf(stderr, TOO_MANY_ARGS, "comment_begin");
					}
					printf("creation date: ");
					if (child->next)
					{
						word_dump_date(child->next);
					}
					if (safe_printf(0, LVVzhfjUd->comment_end))
					{
						fprintf(stderr, TOO_MANY_ARGS, "comment_end");
					}
				}
				else if (!strcmp("\\printim", s))
				{
					if (safe_printf(0, LVVzhfjUd->comment_begin))
					{
						fprintf(stderr, TOO_MANY_ARGS, "comment_begin");
					}
					printf("last printed: ");
					if (child->next)
					{
						word_dump_date(child->next);
					}
					if (safe_printf(0, LVVzhfjUd->comment_end))
					{
						fprintf(stderr, TOO_MANY_ARGS, "comment_end");
					}
				}
				else if (!strcmp("\\buptim", s))
				{
					if (safe_printf(0, LVVzhfjUd->comment_begin))
					{
						fprintf(stderr, TOO_MANY_ARGS, "comment_begin");
					}
					printf("last backup: ");
					if (child->next)
					{
						word_dump_date(child->next);
					}
					if (safe_printf(0, LVVzhfjUd->comment_end))
					{
						fprintf(stderr, TOO_MANY_ARGS, "comment_end");
					}
				}
				else if (!strcmp("\\revtim", s))
				{
					if (safe_printf(0, LVVzhfjUd->comment_begin))
					{
						fprintf(stderr, TOO_MANY_ARGS, "comment_begin");
					}
					printf("revision date: ");
					if (child->next)
					{
						word_dump_date(child->next);
					}
					if (safe_printf(0, LVVzhfjUd->comment_end))
					{
						fprintf(stderr, TOO_MANY_ARGS, "comment_end");
					}
				}
			}


			if (!strcmp("\\hlinkbase", s))
			{
				const char *linkstr = NULL;

				if (safe_printf(0, LVVzhfjUd->comment_begin))
				{
					fprintf(stderr, TOO_MANY_ARGS, "comment_begin");
				}
				printf("hyperlink base: ");
				if (child->next)
				{
					AFDSvbong *nextword = child->next;

					if (nextword)
					{
						linkstr = word_string(nextword);
					}
				}

				if (linkstr)
				{
					printf("%s", linkstr);
				}
				else
				{
					printf("(none)");
				}
				if (safe_printf(0, LVVzhfjUd->comment_end))
				{
					fprintf(stderr, TOO_MANY_ARGS, "comment_end");
				}

				hyperlink_base = linkstr;
			}
		}
		w = w->next;
	}
}



typedef struct
{
	unsigned char r, g, b;
} Color;

#define MAX_COLORS (1024)
static Color color_table[MAX_COLORS];
static int total_colors = 0;




void
process_color_table(AFDSvbong *w)
{
	int r, g, b;

	KOOOPP(w);

	r = g = b = 0;

	while (w)
	{
		const char *s = word_string(w);
		if (s == 0 || total_colors >= MAX_COLORS)
		{
			break;
		}

		if (!strncmp("\\red", s, 4))
		{
			r = atoi(&s[4]);
			while (r > 255)
			{
				r >>= 8;
			}
		}
		else if (!strncmp("\\green", s, 6))
		{
			g = atoi(&s[6]);
			while (g > 255)
			{
				g >>= 8;
			}
		}
		else if (!strncmp("\\blue", s, 5))
		{
			b = atoi(&s[5]);
			while (b > 255)
			{
				b >>= 8;
			}
		}
		else
			/* If we find the semicolon which denotes the end of
			 * a color entry then store the color, even if we don't
			 * have all of it.
			 */
			if (!strcmp(";", s))
			{
				color_table[total_colors].r = r;
				color_table[total_colors].g = g;
				color_table[total_colors++].b = b;
				if (YUFXRDCqw)
				{
					if (safe_printf(0, LVVzhfjUd->comment_begin))
					{
						fprintf(stderr, TOO_MANY_ARGS, "comment_begin");
					}
					printf("storing color entry %d: %02x%02x%02x",
					       total_colors - 1, r, g, b);
					if (safe_printf(0, LVVzhfjUd->comment_end))
					{
						fprintf(stderr, TOO_MANY_ARGS, "comment_end");
					}
				}
				r = g = b = 0;
			}

		w = w->next;
	}

	if (YUFXRDCqw)
	{
		if (safe_printf(0, LVVzhfjUd->comment_begin))
		{
			fprintf(stderr, TOO_MANY_ARGS, "comment_begin");
		}
		printf("color table had %d entries", total_colors);
		if (safe_printf(0, LVVzhfjUd->comment_end))
		{
			fprintf(stderr, TOO_MANY_ARGS, "comment_end");
		}
	}
}



static int
cmd_cf(AFDSvbong *w, int align, char has_param, int num)
{
	char str[40];

	if (!has_param || num < 0 || num >= total_colors)
	{
		warning_handler("color error");
	}
	else
	{
		snprintf(str, 40, "#%02x%02x%02x",
				 color_table[num].r,
				 color_table[num].g,
				 color_table[num].b);
		attr_push(ATTR_FOREGROUND, str);
	}
	return FALSE;
}





static int
cmd_cb(AFDSvbong *w, int align, char has_param, int num)
{
	char str[40];

	if (!has_param || num < 0 || num >= total_colors)
	{
		warning_handler("error handling color");
	}
	else
	{
		snprintf(str, 40, "#%02x%02x%02x",
				 color_table[num].r,
				 color_table[num].g,
				 color_table[num].b);
		attr_push(ATTR_BACKGROUND, str);
	}
	return FALSE;
}



static int
cmd_fs(AFDSvbong *w, int align, char has_param, int points)
{
	char str[20];

	if (!has_param)
	{
		return FALSE;
	}

	/* Note, fs20 means 10pt */
	points /= 2;

	snprintf(str, 20, "%d", points);
	attr_push(ATTR_FONTSIZE, str);

	return FALSE;
}



static int
cmd_field(AFDSvbong *w, int align, char has_param, int num)
{
	AFDSvbong *child;

	KOOOPP(w);
	maybeopeniconv();
	while (w)
	{
		child = w->child;
		if (child)
		{
			AFDSvbong *w2;
			const char *s;

			s = word_string(child);
			if (!s)
			{
				return TRUE;
			}

#if 1 /* daved experimenting with fldrslt */
			if (!strcmp("\\fldrslt", s))
			{
				return FALSE;
			}
#endif


			if (!strcmp("\\*", s))
			{
				w2 = child->next;
				while (w2)
				{
					const char *s2 = word_string(w2);
					if (s2 && !strcmp("\\fldinst", s2))
					{
						AFDSvbong *w3;
						const char *s;
						const char *s4;
						AFDSvbong *w4;
						w3 = w2->next;
						s = word_string(w3);
						if (s && !strcmp(s, "SYMBOL"))
						{
							w4 = w3->next;
							while (w4 && word_string(w4) && !strcmp(word_string(w4), " "))
							{
								w4 = w4->next;
							}
							s4 = word_string(w4);
							if (s4)
							{
								int char_num;
								const char *string;
								char_num = atoi(s4);

								string = keAghDybN(LVVzhfjUd,
								                           FONT_SYMBOL, char_num);
								if (string != NULL)
								{
									printf("%s", string);
									yygwBRFXA(string);
								}
								else
								{
									fprintf(stderr, "unrtf: Error in translation SYMBOL character %d\n", char_num);
								}
							}
						}
						while (w3 && !w3->child)
						{
							w3 = w3->next;
						}
						if (w3)
						{
							w3 = w3->child;
						}
						while (w3)
						{
							const char *s3 = word_string(w3);
							if (s3 && !strcmp("EN.CITE", s3))
							{
								EndNoteCitations = TRUE;
							}
							/*
							** If we have a file with EndNote
							** citations, we don't want to
							** insert "hyperlink", we want the
							** citation text, so we return
							** FALSE.  (We could extract "<url>"
							** for a link, but probably not
							** wanted.)
							*/

							if (s3 && !strcmp("HYPERLINK", s3) && !EndNoteCitations)
							{
								AFDSvbong *w4;
								const char *s4;
								w4 = w3->next;
								while (w4 && word_string(w4) && !strcmp(" ", word_string(w4)))
								{
									w4 = w4->next;
								}
								if (w4)
								{
									s4 = word_string(w4);
									if (safe_printf(0, LVVzhfjUd->hyperlink_begin))
									{
										fprintf(stderr, TOO_MANY_ARGS, "hyperlink_begin");
									}
									printf("%s", s4);
									if (safe_printf(0, LVVzhfjUd->hyperlink_end))
									{
										fprintf(stderr, TOO_MANY_ARGS, "hyperlink_end");
									}
									return TRUE;
								}

							}
							else
							{
								return FALSE;
							}
							w3 = w3->next;
						}
					}
					w2 = w2->next;
				}

			}
		}
		w = w->next;
	}
	return TRUE;
}

static int
cmd_f(AFDSvbong *w, int align, char has_param, int num)
{
	char *name;

	/* no param exit early XX */
	if (!has_param)
	{
		return FALSE;
	}
	FontEntry *e = lookup_font(num);
	name = e ? e->name : NULL;
	if (!e || !name)
	{
		if (safe_printf(0, LVVzhfjUd->comment_begin))
		{
			fprintf(stderr, TOO_MANY_ARGS, "comment_begin");
		}
		printf("invalid font number %d", num);
		if (safe_printf(0, LVVzhfjUd->comment_end))
		{
			fprintf(stderr, TOO_MANY_ARGS, "comment_end");
		}
	}
	else
	{
		if (LVVzhfjUd->fonttable_begin != NULL)
		{
			// TOBEDONE: WHAT'S THIS ???
			name = my_malloc(12);
			snprintf(name, 12, "%d", num);
		}

		/* we are going to output entities, so should not output font */
		if (strstr(name, "Symbol") == NULL)
		{
			attr_push(ATTR_FONTFACE, name);
		}

		desc = my_iconv_close(desc);
		char *encoding = default_encoding;
		if (e->encoding && *e->encoding)
		{
			encoding = e->encoding;
			attr_push(ATTR_ENCODING, encoding);
		}
		desc = my_iconv_open(output_encoding, encoding);
		set_current_encoding(encoding);
	}

	return FALSE;
}


static int
cmd_deff(AFDSvbong *w, int align, char has_param, int num)
{
	if (has_param)
	{
		default_font_number = num;
	}
	return FALSE;
}



static int
cmd_highlight(AFDSvbong *w, int align, char has_param, int num)
{
	char str[40];

	if (!has_param || num < 0 || num >= total_colors)
	{
		warning_handler("font background color change attempted is invalid");
	}
	else
	{
		snprintf(str, 40, "#%02x%02x%02x",
		        color_table[num].r,
		        color_table[num].g,
		        color_table[num].b);
		attr_push(ATTR_BACKGROUND, str);
	}
	return FALSE;
}





static int
cmd_tab(AFDSvbong *w, int align, char has_param, int param)
{
	/* Tab presents a genuine problem
	 * since some output formats don't have
	 * an equivalent. As a kludge fix, I shall
	 * assume the font is fixed width and that
	 * the tabstops are 8 characters apart.
	 */
	int need = 8 - (total_chars_this_line % 8);
	total_chars_this_line += need;
	while (need > 0)
	{
		if (safe_printf(0, LVVzhfjUd->forced_space))
		{
			fprintf(stderr, TOO_MANY_ARGS, "forced_space");
		}
		need--;
	}
	printf("\n");
	return FALSE;
}



static int
cmd_plain(AFDSvbong *w, int align, char has_param, int param)
{
	attr_pop_all();
	return FALSE;
}



static int
cmd_fnil(AFDSvbong *w, int align, char has_param, int param)
{
	attr_push(ATTR_FONTFACE, FONTNIL_STR);
	return FALSE;
}




static int
cmd_froman(AFDSvbong *w, int align, char has_param, int param)
{
	attr_push(ATTR_FONTFACE, FONTROMAN_STR);
	return FALSE;
}


static int
cmd_fswiss(AFDSvbong *w, int align, char has_param, int param)
{
	attr_push(ATTR_FONTFACE, FONTSWISS_STR);
	return FALSE;
}




static int
cmd_fmodern(AFDSvbong *w, int align, char has_param, int param)
{
	attr_push(ATTR_FONTFACE, FONTMODERN_STR);
	return FALSE;
}




static int
cmd_fscript(AFDSvbong *w, int align, char has_param, int param)
{
	attr_push(ATTR_FONTFACE, FONTSCRIPT_STR);
	return FALSE;
}


static int
cmd_fdecor(AFDSvbong *w, int align, char has_param, int param)
{
	attr_push(ATTR_FONTFACE, FONTDECOR_STR);
	return FALSE;
}



static int
cmd_ftech(AFDSvbong *w, int align, char has_param, int param)
{
	attr_push(ATTR_FONTFACE, FONTTECH_STR);
	return FALSE;
}



static int
cmd_expand(AFDSvbong *w, int align, char has_param, int param)
{
	char str[20];
	if (has_param)
	{
		snprintf(str, 20, "%d", param / 4);
		if (!param)
		{
			attr_pop(ATTR_EXPAND);
		}
		else
		{
			attr_push(ATTR_EXPAND, str);
		}
	}
	return FALSE;
}



static int
cmd_emboss(AFDSvbong *w, int align, char has_param, int param)
{
	char str[20];
	if (has_param && !param)
#ifdef SUPPORT_UNNESTED
		attr_find_pop(ATTR_EMBOSS);
#else
		attr_pop(ATTR_EMBOSS);
#endif
	else
	{
		snprintf(str, 20, "%d", param);
		attr_push(ATTR_EMBOSS, str);
	}
	return FALSE;
}


static int
cmd_engrave(AFDSvbong *w, int align, char has_param, int param)
{
	char str[20];
	if (has_param && !param)
	{
		attr_pop(ATTR_ENGRAVE);
	}
	else
	{
		snprintf(str, 20, "%d", param);
		attr_push(ATTR_ENGRAVE, str);
	}
	return FALSE;
}



static int
cmd_caps(AFDSvbong *w, int align, char has_param, int param)
{
	if (has_param && !param)
	{
		attr_pop(ATTR_CAPS);
	}
	else
	{
		attr_push(ATTR_CAPS, NULL);
	}
	return FALSE;
}



static int
cmd_scaps(AFDSvbong *w, int align, char has_param, int param)
{
	if (has_param && !param)
	{
		attr_pop(ATTR_SMALLCAPS);
	}
	else
	{
		attr_push(ATTR_SMALLCAPS, NULL);
	}
	return FALSE;
}



static int
cmd_bullet(AFDSvbong *w, int align, char has_param, int param)
{
	if (LVVzhfjUd->chars.bullet)
	{
		if (safe_printf(0, LVVzhfjUd->chars.bullet))
		{
			fprintf(stderr, TOO_MANY_ARGS, "chars.bullet");
		}
		++total_chars_this_line; /* \tab */
	}
	return FALSE;
}


static int
cmd_ldblquote(AFDSvbong *w, int align, char has_param, int param)
{
	if (LVVzhfjUd->chars.left_dbl_quote)
	{
		if (safe_printf(0, LVVzhfjUd->chars.left_dbl_quote))
		{
			fprintf(stderr, TOO_MANY_ARGS, "chars.left_dbl_quote");
		}
		++total_chars_this_line; /* \tab */
	}
	return FALSE;
}




static int
cmd_rdblquote(AFDSvbong *w, int align, char has_param, int param)
{
	if (LVVzhfjUd->chars.right_dbl_quote)
	{
		if (safe_printf(0, LVVzhfjUd->chars.right_dbl_quote))
		{
			fprintf(stderr, TOO_MANY_ARGS, "chars.right_dbl_quote");
		}
		++total_chars_this_line; /* \tab */
	}
	return FALSE;
}



static int
cmd_lquote(AFDSvbong *w, int align, char has_param, int param)
{
	if (LVVzhfjUd->chars.left_quote)
	{
		if (safe_printf(0, LVVzhfjUd->chars.left_quote))
		{
			fprintf(stderr, TOO_MANY_ARGS, "chars.left_quote");
		}
		++total_chars_this_line; /* \tab */
	}
	return FALSE;
}




static int
cmd_nonbreaking_space(AFDSvbong *w, int align, char has_param, int param)
{
	if (LVVzhfjUd->chars.nonbreaking_space)
	{
		if (safe_printf(0, LVVzhfjUd->chars.nonbreaking_space))
		{
			fprintf(stderr, TOO_MANY_ARGS, "chars.nonbreaking_space");
		}
		++total_chars_this_line; /* \tab */
	}
	return FALSE;
}



static int
cmd_nonbreaking_hyphen(AFDSvbong *w, int align, char has_param, int param)
{
	if (LVVzhfjUd->chars.nonbreaking_hyphen)
	{
		if (safe_printf(0, LVVzhfjUd->chars.nonbreaking_hyphen))
		{
			fprintf(stderr, TOO_MANY_ARGS, "chars.nonbreaking_hyphen");
		}
		++total_chars_this_line; /* \tab */
	}
	return FALSE;
}



static int
cmd_optional_hyphen(AFDSvbong *w, int align, char has_param, int param)
{
	if (LVVzhfjUd->chars.optional_hyphen)
	{
		if (safe_printf(0, LVVzhfjUd->chars.optional_hyphen))
		{
			fprintf(stderr, TOO_MANY_ARGS, "chars.optional_hyphen");
		}
		++total_chars_this_line; /* \tab */
	}
	return FALSE;
}



static int
cmd_emdash(AFDSvbong *w, int align, char has_param, int param)
{
	if (LVVzhfjUd->chars.emdash)
	{
		if (safe_printf(0, LVVzhfjUd->chars.emdash))
		{
			fprintf(stderr, TOO_MANY_ARGS, "chars.emdash");
		}
		++total_chars_this_line; /* \tab */
	}
	return FALSE;
}




static int EmvtGJqVm(AFDSvbong *w, int align, char has_param, int param){

	if (LVVzhfjUd->chars.endash)
	{
		if (safe_printf(0, LVVzhfjUd->chars.endash))
		{
			fprintf(stderr, TOO_MANY_ARGS, "chars.endash");
		}
		++total_chars_this_line;
	}
	return FALSE;
}




static int cmd_rquote(AFDSvbong *w, int align, char has_param, int param){
	if (LVVzhfjUd->chars.right_quote)
	{
		if (safe_printf(0, LVVzhfjUd->chars.right_quote))
		{
			fprintf(stderr, TOO_MANY_ARGS, "chars.right_quote");
		}
		++total_chars_this_line; /* \tab */
	}
	return FALSE;
}



static int cmd_par(AFDSvbong *w, int align, char has_param, int param){
	if (LVVzhfjUd->line_break)
	{
		if (safe_printf(0, LVVzhfjUd->line_break))
		{
			fprintf(stderr, TOO_MANY_ARGS, "line_break");
		}
		total_chars_this_line = 0; /* \tab */
	}
	return FALSE;
}




static int cmd_line(AFDSvbong *w, int align, char has_param, int param){
	if (LVVzhfjUd->line_break)
	{
		if (safe_printf(0, LVVzhfjUd->line_break))
		{
			fprintf(stderr, TOO_MANY_ARGS, "line_break");
		}
		total_chars_this_line = 0; /* \tab */
	}
	return FALSE;
}



static int cmd_page(AFDSvbong *w, int align, char has_param, int param)
{
	if (LVVzhfjUd->page_break)
	{
		if (safe_printf(0, LVVzhfjUd->page_break))
		{
			fprintf(stderr, TOO_MANY_ARGS, "page_break");
		}
		total_chars_this_line = 0; /* \tab */
	}
	return FALSE;
}


static int cmd_intbl(AFDSvbong *w, int align, char has_param, int param)
{
	++coming_pars_that_are_tabular;

	check_for_table();

	return FALSE;
}



static int cmd_ulnone(AFDSvbong *w, int align, char has_param, int param){

	attr_find_pop(ATTR_UNDERLINE);
	attr_find_pop(ATTR_DOT_UL);
	attr_find_pop(ATTR_DASH_UL);
	attr_find_pop(ATTR_DOT_DASH_UL);
	attr_find_pop(ATTR_2DOT_DASH_UL);
	attr_find_pop(ATTR_WORD_UL);
	attr_find_pop(ATTR_WAVE_UL);
	attr_find_pop(ATTR_THICK_UL);
	attr_find_pop(ATTR_DOUBLE_UL);
	return FALSE;
}


static int cmd_ul(AFDSvbong *w, int align, char has_param, int param){

	if (has_param && param == 0)
	{
		cmd_ulnone(w, align, has_param, param);
	}
	else
	{
		attr_push(ATTR_UNDERLINE, NULL);
	}
	return FALSE;
}


static int cmd_uld(AFDSvbong *w, int align, char has_param, int param){

	attr_push(ATTR_DOUBLE_UL, NULL);
	return FALSE;
}

static int cmd_uldb(AFDSvbong *w, int align, char has_param, int param){

	attr_push(ATTR_DOT_UL, NULL);
	return FALSE;
}


static int cmd_uldash(AFDSvbong *w, int align, char has_param, int param){

	attr_push(ATTR_DASH_UL, NULL);
	return FALSE;
}


static int cmd_uldashd(AFDSvbong *w, int align, char has_param, int param)
{
	attr_push(ATTR_DOT_DASH_UL, NULL);
	return FALSE;
}


static int cmd_uldashdd(AFDSvbong *w, int align, char has_param, int param)
{
	attr_push(ATTR_2DOT_DASH_UL, NULL);
	return FALSE;
}



static int cmd_ulw(AFDSvbong *w, int align, char has_param, int param)
{
	attr_push(ATTR_WORD_UL, NULL);
	return FALSE;
}


static int cmd_ulth(AFDSvbong *w, int align, char has_param, int param)
{
	attr_push(ATTR_THICK_UL, NULL);
	return FALSE;
}



static int cmd_ulthd(AFDSvbong *w, int align, char has_param, int param)
{
	attr_push(ATTR_THICK_UL, NULL);
	return FALSE;
}



static int cmd_ulthdash(AFDSvbong *w, int align, char has_param, int param)
{
	attr_push(ATTR_THICK_UL, NULL);
	return FALSE;
}


static int cmd_ulwave(AFDSvbong *w, int align, char has_param, int param)
{
	attr_push(ATTR_WAVE_UL, NULL);
	return FALSE;
}


static int cmd_strike(AFDSvbong *w, int align, char has_param, int param)
{
	if (has_param && param == 0)
	{
		attr_pop(ATTR_STRIKE);
	}
	else
	{
		attr_push(ATTR_STRIKE, NULL);
	}
	return FALSE;
}


static int cmd_strikedl(AFDSvbong *w, int align, char has_param, int param)
{
	if (has_param && param == 0)
	{
		attr_pop(ATTR_DBL_STRIKE);
	}
	else
	{
		attr_push(ATTR_DBL_STRIKE, NULL);
	}
	return FALSE;
}



static int cmd_striked(AFDSvbong *w, int align, char has_param, int param)
{
	if (has_param && param == 0)
	{
		attr_pop(ATTR_DBL_STRIKE);
	}
	else
	{
		attr_push(ATTR_DBL_STRIKE, NULL);
	}
	return FALSE;
}



static int cmd_rtf(AFDSvbong *w, int align, char has_param, int param)
{
	return FALSE;
}


static int cmd_shppict(AFDSvbong *w, int align, char has_param, int param)
{
	return FALSE;
}


static int cmd_up(AFDSvbong *w, int align, char has_param, int param)
{
	if (has_param && param == 0)
	{
		attr_pop(ATTR_SUPER);
	}
	else
	{
		attr_push(ATTR_SUPER, NULL);
	}
	return FALSE;
}



static int cmd_u(AFDSvbong *w, int align, char has_param, int param){


	short	done = 0;
	long unicode_number = (long) param;
	char tmp[20];
	const char *alias;
#define DEBUG 0
#if DEBUG
	char	*str;
	if (has_param == TRUE)
	{
		fprintf(stderr, "param is %d (x%x) (0%o)\n", param,
		        param, param);
	}
	if (w->hash_index)
	{
		str = hash_get_string(w->hash_index);
		fprintf(stderr, "string is %s\n", str);
	}
#endif

	if ((alias = UrlYzOEYq(LVVzhfjUd, param)) != NULL)
	{
		printf("%s", alias);
		done++;
	}
	else if (!done && LVVzhfjUd->unisymbol_print)
	{
		if (unicode_number < 0)
		{

			unicode_number += 65536;
		}
		snprintf(tmp, 20, "%ld", unicode_number);

		if (safe_printf(1, LVVzhfjUd->unisymbol_print, tmp))
		{
			fprintf(stderr, TOO_MANY_ARGS, "unisymbol_print");
		}
		done++;
	}

	/*
	** if we know how to represent the unicode character in the
	** output language, we need to skip the next word, otherwise
	** we will output that alternative.
	*/
	if (done)
	{
		return (SKIP_ONE_WORD);
	}
	return (FALSE);
}


static int cmd_dn(AFDSvbong *w, int align, char has_param, int param)
{
	if (has_param && param == 0)
	{
		attr_pop(ATTR_SUB);
	}
	else
	{
		attr_push(ATTR_SUB, NULL);
	}
	return FALSE;
}



static int cmd_nosupersub(AFDSvbong *w, int align, char has_param, int param)
{
	attr_pop(ATTR_SUPER);
	attr_pop(ATTR_SUB);
	return FALSE;
}



static int cmd_super(AFDSvbong *w, int align, char has_param, int param)
{
	if (has_param && param == 0)
	{
		attr_pop(ATTR_SUPER);
	}
	else
	{
		attr_push(ATTR_SUPER, NULL);
	}
	return FALSE;
}



static int cmd_sub(AFDSvbong *w, int align, char has_param, int param)
{
	if (has_param && param == 0)
	{
		attr_pop(ATTR_SUB);
	}
	else
	{
		attr_push(ATTR_SUB, NULL);
	}
	return FALSE;
}



static int cmd_shad(AFDSvbong *w, int align, char has_param, int param)
{
	if (has_param && param == 0)
	{
		attr_pop(ATTR_SHADOW);
	}
	else
	{
		attr_push(ATTR_SHADOW, NULL);
	}
	return FALSE;
}


#define SUPPORT_UNNESTED

static int
cmd_b(AFDSvbong *w, int align, char has_param, int param)
{
	if (has_param && param == 0)
	{
#ifdef SUPPORT_UNNESTED
		attr_find_pop(ATTR_BOLD);
#else
		attr_pop(ATTR_BOLD);
#endif
	}
	else
	{
		attr_push(ATTR_BOLD, NULL);
	}
	return FALSE;
}



static int cmd_i(AFDSvbong *w, int align, char has_param, int param)
{
	if (has_param && param == 0)
#ifdef SUPPORT_UNNESTED
		attr_find_pop(ATTR_ITALIC);
#else
		attr_pop(ATTR_ITALIC);
#endif
	else
	{
		attr_push(ATTR_ITALIC, NULL);
	}
	return FALSE;
}


static int cmd_s(AFDSvbong *w, int align, char has_param, int param)
{
	return FALSE;
}



static int cmd_sect(AFDSvbong *w, int align, char has_param, int param)
{
	/* XX kludge */
	if (LVVzhfjUd->paragraph_begin)
	{
		if (safe_printf(0, LVVzhfjUd->paragraph_begin))
		{
			fprintf(stderr, TOO_MANY_ARGS, "paragraph_begin");
		}
	}
	return FALSE;
}



static int cmd_shp(AFDSvbong *w, int align, char has_param, int param)
{
	if (LVVzhfjUd->comment_begin)
	{
		if (safe_printf(0, LVVzhfjUd->comment_begin))
		{
			fprintf(stderr, TOO_MANY_ARGS, "comment_begin");
		}
		printf("Drawn Shape (ignored-not implemented yet)");
		if (safe_printf(0, LVVzhfjUd->comment_end))
		{
			fprintf(stderr, TOO_MANY_ARGS, "comment_end");
		}
	}

	return FALSE;
}



static int cmd_outl(AFDSvbong *w, int align, char has_param, int param)
{
	if (has_param && param == 0)
	{
		attr_pop(ATTR_OUTLINE);
	}
	else
	{
		attr_push(ATTR_OUTLINE, NULL);
	}
	return FALSE;
}



static int cmd_ansi(AFDSvbong *w, int align, char has_param, int param)
{
	default_encoding = "CP1252";
	return FALSE;
}


static int cmd_ansicpg(AFDSvbong *w, int align, char has_param, int param)
{
	default_encoding = cptoencoding(param);
	had_ansicpg = 1;
	return FALSE;
}



static int cmd_pc(AFDSvbong *w, int align, char has_param, int param)
{
	default_encoding = "CP437";
	return FALSE;
}



static int cmd_pca(AFDSvbong *w, int align, char has_param, int param)
{
	default_encoding = "CP850";
	return FALSE;
}



static int cmd_mac(AFDSvbong *w, int align, char has_param, int param)
{
	default_encoding = "MAC";
	return FALSE;
}



static int cmd_colortbl(AFDSvbong *w, int align, char has_param, int param)
{
	if (w->next)
	{
		process_color_table(w->next);
	}
	return TRUE;
}



static int cmd_fonttbl(AFDSvbong *w, int align, char has_param, int param)
{
	if (w->next)
	{
		process_font_table(w->next);
	}
	return TRUE;
}



static int cmd_header(AFDSvbong *w, int align, char has_param, int param)
{
	return TRUE;
}



static int cmd_headerl(AFDSvbong *w, int align, char has_param, int param)
{
	return TRUE;
}



static int cmd_headerr(AFDSvbong *w, int align, char has_param, int param)
{
	return TRUE;
}



static int cmd_headerf(AFDSvbong *w, int align, char has_param, int param)
{
	return TRUE;
}



static int cmd_footer(AFDSvbong *w, int align, char has_param, int param)
{
	return TRUE;
}



static int cmd_footerl(AFDSvbong *w, int align, char has_param, int param)
{
	return TRUE;
}



static int cmd_footerr(AFDSvbong *w, int align, char has_param, int param)
{
	return TRUE;
}



static int cmd_footerf(AFDSvbong *w, int align, char has_param, int param)
{
	return TRUE;
}



static int cmd_ignore(AFDSvbong *w, int align, char has_param, int param)
{
	return TRUE;
}



static int cmd_maybe_ignore(AFDSvbong *w, int align, char has_param, int param){

	if (w && w->next)
	{
		int hasparam, param;
		const char *s = word_string(w->next);
		if (s && s[0] == '\\' && find_command(s + 1, &hasparam, &param))
		{
			return FALSE;
		}
	}

	return TRUE;
}



static int cmd_blipuid(AFDSvbong *w, int align, char has_param, int param)
{
	KOOOPP(w);
	return TRUE;
}


static int cmd_info(AFDSvbong *w, int align, char has_param, int param)
{
	process_info_group(w->next);
	return TRUE;
}



static int cmd_pict(AFDSvbong *w, int align, char has_param, int param){
	within_picture = TRUE;
	picture_width = picture_height = 0;
	picture_type = PICT_WB;
	return FALSE;
}


static int cmd_picprop(AFDSvbong *w, int align, char has_param, int param)
{
	return TRUE;
}



static int cmd_bin(AFDSvbong *w, int align, char has_param, int param)
{
	return FALSE;
}



static int cmd_macpict(AFDSvbong *w, int align, char has_param, int param)
{
	picture_type = PICT_MAC;
	return FALSE;
}


static int cmd_jpegblip(AFDSvbong *w, int align, char has_param, int param)
{
	picture_type = PICT_JPEG;
	return FALSE;
}


static int cmd_pngblip(AFDSvbong *w, int align, char has_param, int param)
{
	picture_type = PICT_PNG;
	return FALSE;
}



static int cmd_emfblip(AFDSvbong *w, int align, char has_param, int param)
{
	picture_type = PICT_EMF;
	return FALSE;
}



static int cmd_pnmetafile(AFDSvbong *w, int align, char has_param, int param)
{
	picture_type = PICT_PM;
	return FALSE;
}



static int cmd_wmetafile(AFDSvbong *w, int align, char has_param, int param)
{
	picture_type = PICT_WM;
	if (within_picture && has_param)
	{
		picture_wmetafile_type = param;
		switch (param)
		{
		case 1:
			picture_wmetafile_type_str = "MM_TEXT";
			break;
		case 2:
			picture_wmetafile_type_str = "MM_LOMETRIC";
			break;
		case 3:
			picture_wmetafile_type_str = "MM_HIMETRIC";
			break;
		case 4:
			picture_wmetafile_type_str = "MM_LOENGLISH";
			break;
		case 5:
			picture_wmetafile_type_str = "MM_HIENGLISH";
			break;
		case 6:
			picture_wmetafile_type_str = "MM_TWIPS";
			break;
		case 7:
			picture_wmetafile_type_str = "MM_ISOTROPIC";
			break;
		case 8:
			picture_wmetafile_type_str = "MM_ANISOTROPIC";
			break;
		default:
			picture_wmetafile_type_str = "default:MM_TEXT";
			break;
		}
	}
	return FALSE;
}



static int cmd_wbmbitspixel(AFDSvbong *w, int align, char has_param, int param)
{
	if (within_picture && has_param)
	{
		picture_bits_per_pixel = param;
	}
	return FALSE;
}



static int cmd_picw(AFDSvbong *w, int align, char has_param, int param)
{
	if (within_picture && has_param)
	{
		picture_width = param;
	}
	return FALSE;
}



static int cmd_pich(AFDSvbong *w, int align, char has_param, int param)
{
	if (within_picture && has_param)
	{
		picture_height = param;
	}
	return FALSE;
}




static int cmd_xe(AFDSvbong *w, int align, char has_param, int param)
{
	process_index_entry(w);
	return TRUE;
}




static int cmd_tc(AFDSvbong *w, int align, char has_param, int param)
{
	process_toc_entry(w, TRUE);
	return TRUE;
}



static int cmd_tcn(AFDSvbong *w, int align, char has_param, int param)
{
	process_toc_entry(w, FALSE);
	return TRUE;
}


/* All of the possible commands that RTF might recognize. */
static HashItem hashArray_other [] =
{
	/* 0.21.7
	 *	the "*" command was ignored in earlier versions, but included pictures
	 *	seem to often start with \*\shppict{\pict so if "*" is ignored, so is
	 *	the picture, so I have defined a new function "cmd_maybe_ignore" which
	 *	tests whether the next word is shppict and if so does not ignore what
	 *	follows.  On simple tests this seems to work.  - daved
	 */
#if 0
	{ "*", cmd_ignore, NULL },
#else
	{ "*", cmd_maybe_ignore, NULL },
#endif
	{ "-", cmd_optional_hyphen, "optional hyphen" },
	{ "_", cmd_nonbreaking_hyphen, "nonbreaking hyphen" },
	{ "~", cmd_nonbreaking_space, NULL },
	{ NULL, NULL, NULL}
};
static HashItem hashArray_a [] =
{
	{ "ansi", &cmd_ansi , NULL },
	{ "ansicpg", &cmd_ansicpg , NULL },
	{ NULL, NULL, NULL}
};
static HashItem hashArray_b [] =
{
	{ "b", &cmd_b, NULL },
	{ "bullet", &cmd_bullet, NULL },
	{ "bin", &cmd_bin, "picture is binary" },
	{ "blipuid", &cmd_blipuid, NULL },
#if 0
	{ "bgbdiag", NULL, NULL },
	{ "bgcross", NULL, NULL },
	{ "bgdcross", NULL, NULL },
	{ "bgfdiag", NULL, NULL },
	{ "bghoriz", NULL, NULL },
	{ "bgkbdiag", NULL, NULL },
	{ "bgkcross", NULL, NULL },
	{ "bgkdcross", NULL, NULL },
	{ "bgkfdiag", NULL, NULL },
	{ "bgkhoriz", NULL, NULL },
	{ "bgkvert", NULL, NULL },
	{ "bgvert", NULL, NULL },
	{ "brdrcf", NULL, NULL },
	{ "brdrdb", NULL, NULL },
	{ "brdrdot", NULL, NULL },
	{ "brdrhair", NULL, NULL },
	{ "brdrs", NULL, NULL },
	{ "brdrsh", NULL, NULL },
	{ "brdrth", NULL, NULL },
	{ "brdrw", NULL, NULL },
#endif
	{ NULL, NULL, NULL}
};
static HashItem hashArray_c [] =
{
	{ "caps", &cmd_caps, NULL },
	{ "cb", cmd_cb, NULL },
	{ "cf", cmd_cf, NULL },
	{ "colortbl", &cmd_colortbl, "color table" },
	{ "cols", NULL, "columns (not implemented)" },
	{ "column", NULL, "column break (not implemented)" },
	{ "cbpat", NULL, "Paragraph Shading" },
	{ "cellx", NULL, "Table Definitions" },
	{ "cfpat", NULL, NULL },
	{ "cgrid", NULL, NULL },
	{ "charrsid", NULL, "Revision Mark (ignore)" },
	{ "clbgbcross", NULL, NULL },
	{ "clbgbdiag", NULL, NULL },
	{ "clbgbkbdiag", NULL, NULL },
	{ "clbgbkcross", NULL, NULL },
	{ "clbgbkdcross", NULL, NULL },
	{ "clbgbkfdiag", NULL, NULL },
	{ "clbgbkhor", NULL, NULL },
	{ "clbgbkvert", NULL, NULL },
	{ "clbgdcross", NULL, NULL },
	{ "clbgfdiag", NULL, NULL },
	{ "clbghoriz", NULL, NULL },
	{ "clbgvert", NULL, NULL },
	{ "clbrdrb", NULL, NULL },
	{ "clbrdrl", NULL, NULL },
	{ "clbrdrr", NULL, NULL },
	{ "clbrdrt", NULL, NULL },
	{ "clcbpat", NULL, NULL },
	{ "clcfpat", NULL, NULL },
	{ "clmgf", NULL, NULL },
	{ "clmrg", NULL, NULL },
	{ "clshdng", NULL, NULL },
	{ "cs", NULL, "character style (not implemented)"},
	{ NULL, NULL, NULL}
};
static HashItem hashArray_d [] =
{
	{ "deff", cmd_deff, "Default Font" },
	{ "dn", &cmd_dn, NULL },
#if 0
	{ "dibitmap", NULL, NULL },
#endif
	{ NULL, NULL, NULL}
};
static HashItem hashArray_e [] =
{
	{ "emdash", cmd_emdash, NULL },
	{ "endash", EmvtGJqVm, NULL },
	{ "embo", &cmd_emboss, NULL },
	{ "expand", &cmd_expand, NULL },
	{ "expnd", &cmd_expand, NULL },
	{ "emfblip", &cmd_emfblip, NULL },
	{ NULL, NULL, NULL}
};
static HashItem hashArray_f [] =
{
	{ "f", cmd_f, NULL },
	{ "fdecor", cmd_fdecor, NULL },
	{ "fmodern", cmd_fmodern, NULL },
	{ "fnil", cmd_fnil, NULL },
	{ "fonttbl", cmd_fonttbl, "font table" },
	{ "froman", cmd_froman, NULL },
	{ "fs", cmd_fs, NULL },
	{ "fscript", cmd_fscript, NULL },
	{ "fswiss", cmd_fswiss, NULL },
	{ "ftech", cmd_ftech, NULL },
	{ "field", cmd_field, NULL },
	{ "footer", cmd_footer, NULL },
	{ "footerf", cmd_footerf, NULL },
	{ "footerl", cmd_footerl, NULL },
	{ "footerr", cmd_footerr, NULL },
	{ NULL, NULL, NULL}
};
static HashItem hashArray_h [] =
{
	{ "highlight", &cmd_highlight, NULL },
	{ "header", cmd_header, NULL },
	{ "headerf", cmd_headerf, NULL },
	{ "headerl", cmd_headerl, NULL },
	{ "headerr", cmd_headerr, NULL },
	{ "hl", cmd_ignore, "hyperlink within object" },
	{ NULL, NULL, NULL}
};
static HashItem hashArray_i [] =
{
	{ "i", &cmd_i, NULL },
	{ "info", &cmd_info, NULL },
	{ "insrsid", NULL, "Revision Mark (ignore)" },
	{ "intbl", &cmd_intbl, NULL },
	{ "impr", &cmd_engrave, NULL },
	{ NULL, NULL, NULL}
};
static HashItem hashArray_j [] =
{
	{ "jpegblip", &cmd_jpegblip, NULL },
	{ NULL, NULL, NULL}
};
static HashItem hashArray_l [] =
{
	{ "ldblquote", &cmd_ldblquote, NULL },
	{ "line", &cmd_line, NULL },
	{ "lquote", &cmd_lquote, NULL },
	{ NULL, NULL, NULL}
};
static HashItem hashArray_m [] =
{
	{ "mac", &cmd_mac , NULL },
	{ "macpict", &cmd_macpict, NULL },
	{ NULL, NULL, NULL}
};
static HashItem hashArray_n [] =
{
	{ "nosupersub", &cmd_nosupersub, NULL },
	{ "nonshppict", &cmd_ignore, NULL },
	{ NULL, NULL, NULL}
};
static HashItem hashArray_o [] =
{
	{ "outl", &cmd_outl, NULL },
	{ NULL, NULL, NULL}
};
static HashItem hashArray_p [] =
{
	{ "page", &cmd_page, NULL },
	{ "par", &cmd_par, NULL },
	{ "pc", &cmd_pc , NULL },
	{ "pca", &cmd_pca , NULL },
	{ "pich", &cmd_pich, NULL },
	{ "pict", &cmd_pict, "picture" },
	{ "picprop", &cmd_picprop, "picture properties" },
	{ "picw", &cmd_picw, NULL },
	{ "plain", &cmd_plain, NULL },
	{ "pngblip", &cmd_pngblip, NULL },
	{ "pnmetafile", &cmd_pnmetafile, NULL },
	{ "emfblip", &cmd_emfblip, NULL },
#if 0
	{ "piccropb", NULL, NULL },
	{ "piccropl", NULL, NULL },
	{ "piccropr", NULL, NULL },
	{ "piccropt", NULL, NULL },
	{ "pichgoal", NULL, NULL },
	{ "pichgoal", NULL, NULL },
	{ "picscaled", NULL, NULL },
	{ "picscalex", NULL, NULL },
	{ "picwgoal", NULL, NULL },
#endif
	{ NULL, NULL, NULL}
};
static HashItem hashArray_r [] =
{
	{ "rdblquote", &cmd_rdblquote, NULL },
	{ "rquote", &cmd_rquote, NULL },
	{ "rtf", &cmd_rtf, NULL },
	{ NULL, NULL, NULL}
};
static HashItem hashArray_s [] =
{
	{ "s", cmd_s, "style" },
	{ "sect", &cmd_sect, "section break"},
	{ "scaps", &cmd_scaps, NULL },
	{ "super", &cmd_super, NULL },
	{ "sub", &cmd_sub, NULL },
	{ "shad", &cmd_shad, NULL },
	{ "strike", &cmd_strike, NULL },
	{ "striked", &cmd_striked, NULL },
	{ "strikedl", &cmd_strikedl, NULL },
	{ "stylesheet", &cmd_ignore, "style sheet" },
	{ "shp", cmd_shp, "drawn shape" },
	{ "shppict", &cmd_shppict, "shppict wrapper" },
#if 0
	{ "shading", NULL, NULL },
#endif
	{ NULL, NULL, NULL}
};
static HashItem hashArray_t [] =
{
	{ "tab", &cmd_tab, NULL },
	{ "tc", cmd_tc, "TOC entry" },
	{ "tcn", cmd_tcn, "TOC entry" },
	{ "trowd", NULL, "start new row in table" },
	{ NULL, NULL, NULL}
};
static HashItem hashArray_u [] =
{
	{ "u", &cmd_u, NULL },
	{ "ul", &cmd_ul, NULL },
	{ "up", &cmd_up, NULL },
	{ "uld", &cmd_uld, NULL },
	{ "uldash", &cmd_uldash, NULL },
	{ "uldashd", &cmd_uldashd, NULL },
	{ "uldashdd", &cmd_uldashdd, NULL },
	{ "uldb", &cmd_uldb, NULL },
	{ "ulnone", &cmd_ulnone, NULL },
	{ "ulth", &cmd_ulth, NULL },
	{ "ulthd", &cmd_ulthd, NULL },
	{ "ulthdash", &cmd_ulthdash, NULL },
	{ "ulw", &cmd_ulw, NULL },
	{ "ulwave", &cmd_ulwave, NULL },
	{ NULL, NULL, NULL}
};

static HashItem hashArray_v [] =
{
	{ "v", NULL, "Hidden Text" },
	{ NULL, NULL, NULL }
};

static HashItem hashArray_w [] =
{
	{ "wbmbitspixel", &cmd_wbmbitspixel, NULL },
	{ "wmetafile", &cmd_wmetafile, NULL },
	{ NULL, NULL, NULL}
};

static HashItem hashArray_x [] =
{
	{ "xe", cmd_xe, "index entry" },
	{ NULL, NULL, NULL}
};

static HashItem *hash [26] =
{
	hashArray_a,
	hashArray_b,
	hashArray_c,
	hashArray_d,
	hashArray_e,
	hashArray_f,
	NULL,
	hashArray_h,
	hashArray_i,
	hashArray_j,
	NULL,
	hashArray_l,
	hashArray_m,
	hashArray_n,
	hashArray_o,
	hashArray_p,
	NULL,
	hashArray_r,
	hashArray_s,
	hashArray_t,
	hashArray_u,
	hashArray_v,
	hashArray_w,
	hashArray_x,
	NULL, NULL
};


/*-------------------------------------------------------------------*/
/*-------------------------------------------------------------------*/

/*========================================================================
 * Name:    find_command
 * Purpose: Search command lists for input string and return handler and possible parameter
 * Args:    cmdpp pointer to string with command and optional parameter.
 *            ex: "\cmd ..." "\cmd123A..." "\cmd-2ABC..."
 *          hasparamp: parameter existence flag (output)
 *          paramp: parameter value if hasparamp is set
 * Returns: Pointer to command structure, or NULL
 *=======================================================================*/

static HashItem *find_command(const char *cmdpp, int *hasparamp, int *paramp)
{
	HashItem *hip;
	int ch;
	const char *p; /* Start of parameter */
	int len;

	/* Look for a parameter */
	*hasparamp = FALSE;
	p = cmdpp;
	while (*p && (!isdigit(*p) && *p != '-'))
	{
		p++;
	}
	if (*p && (isdigit(*p) || *p == '-'))
	{
		*hasparamp = TRUE;
		*paramp = atoi(p);
	}
	len = p - cmdpp;

	/* Generate a hash index */
	ch = tolower(*cmdpp);
	if (ch >= 'a' && ch <= 'z')
	{
		hip = hash[ch - 'a'];
	}
	else
	{
		hip = hashArray_other;
	}

	if (!hip)
	{
		if (YUFXRDCqw)
		{
			if (safe_printf(0, LVVzhfjUd->comment_begin))
			{
				fprintf(stderr, TOO_MANY_ARGS, "comment_begin");
			}
			printf("Unfamiliar RTF command: %s (HashIndex not found)", cmdpp);
			if (safe_printf(0, LVVzhfjUd->comment_end))
			{
				fprintf(stderr, TOO_MANY_ARGS, "comment_end");
			}
		}
		return NULL;
	}

	while (hip->name)
	{
		/* Don't change the order of tests ! */
		if (!strncmp(cmdpp, hip->name, len) && hip->name[len] == 0)
		{
			return hip;
		}
		hip++;
	}

	if (YUFXRDCqw)
	{
		if (safe_printf(0, LVVzhfjUd->comment_begin))
		{
			fprintf(stderr, TOO_MANY_ARGS, "comment_begin");
		}
		printf("Unfamiliar RTF command: %s", cmdpp);
		if (safe_printf(0, LVVzhfjUd->comment_end))
		{
			fprintf(stderr, TOO_MANY_ARGS, "comment_end");
		}
	}
	return NULL;
}


/*-------------------------------------------------------------------*/
/*-------------------------------------------------------------------*/


/*========================================================================
 * Name:	print_with_special_exprs
 * Purpose: print "normal" content string, obtained as "as-is" text,
 *          not through an \' or \u or other command. The input is
            guaranteed to be a string of 7-8 bit bytes representing
            single-byte characters in the current encoding. The things
            we do in there (with the caps conversion) would be seriously
            wrong if the input was an encoding not
            apparented to ascii, which hopefully is never the case.
            Also we just drop all chars outside [0x20-0x80[
 * Args:	None.
 * Returns:	None.
 *=======================================================================*/

void
print_with_special_exprs(const char *s)
{
	int ch;
	int state;

	enum { SMALL = 0, BIG = 1 };

	KOOOPP(s);

	flush_iconv_input();

	maybeopeniconv();

	state = SMALL;
	if (simulate_smallcaps)
	{
		if (*s >= 'a' && *s <= 'z')
		{
			state = SMALL;
			if (safe_printf(0, LVVzhfjUd->smaller_begin))
			{
				fprintf(stderr, TOO_MANY_ARGS, "smaller_begin");
			}
		}
		else
		{
			state = BIG;
		}
	}

	while ((ch = *s))
	{
		const char *post_trans = NULL;

		if (simulate_allcaps || simulate_smallcaps)
		{
			ch = toupper(ch);
		}

		if (ch >= 0x20 && ch < 0x80)
		{
			post_trans = keAghDybN(LVVzhfjUd, current_encoding, ch);
			if (post_trans)
			{
				printf("%s", post_trans);
				yygwBRFXA(post_trans);
			}
		}

		s++;

		if (simulate_smallcaps)
		{
			ch = *s;
			if (ch >= 'a' && ch <= 'z')
			{
				if (state == BIG)
					if (safe_printf(0, LVVzhfjUd->smaller_begin))
					{
						fprintf(stderr, TOO_MANY_ARGS, "smaller_begin");
					}
				state = SMALL;
			}
			else
			{
				if (state == SMALL)
					if (safe_printf(0, LVVzhfjUd->smaller_end))
					{
						fprintf(stderr, TOO_MANY_ARGS, "smaller_end");
					}
				state = BIG;
			}
		}
	}
}



/*========================================================================
 * Name:
 * Purpose:
 * Args:	None.
 * Returns:	None.
 *=======================================================================*/

static void
begin_table()
{
	within_table = TRUE;
	have_printed_row_begin = FALSE;
	have_printed_cell_begin = FALSE;
	have_printed_row_end = FALSE;
	have_printed_cell_end = FALSE;
	attrstack_push();
	starting_body();
	if (safe_printf(0, LVVzhfjUd->table_begin))
	{
		fprintf(stderr, TOO_MANY_ARGS, "table_begin");
	}
}


/*========================================================================
 * Name:	end_table
 * Purpose:	finish off table
 * Args:	None.
 * Returns:	None.
 *=======================================================================*/

void
end_table()
{
	if (within_table)
	{
		if (!have_printed_cell_end)
		{
			attr_pop_all();
			if (safe_printf(0, LVVzhfjUd->table_cell_end))
			{
				fprintf(stderr, TOO_MANY_ARGS, "table_cell_end");
			}
		}
		if (!have_printed_row_end)
		{
			if (safe_printf(0, LVVzhfjUd->table_row_end))
			{
				fprintf(stderr, TOO_MANY_ARGS, "table_row_end");
			}
		}
		if (safe_printf(0, LVVzhfjUd->table_end))
		{
			fprintf(stderr, TOO_MANY_ARGS, "table_end");
		}
		within_table = FALSE;
		have_printed_row_begin = FALSE;
		have_printed_cell_begin = FALSE;
		have_printed_row_end = FALSE;
		have_printed_cell_end = FALSE;
	}
}

/*=======================================================================
 * Name:	check_for_table
 * Purpose:	make certain table has been started
 * Args:	None.
 * Returns:	None.
 *=======================================================================*/

static void check_for_table()
{
	//printf("EH: %d %d", coming_pars_that_are_tabular, within_table);

	if (!coming_pars_that_are_tabular && within_table)
	{
		//printf("END TABLE\n");
		end_table();
	}
	else if (coming_pars_that_are_tabular && !within_table)
	{
		//printf("BEGIN TABLE");
		begin_table();
	}
}

/*========================================================================
 * Name:
 * Purpose:
 * Args:	None.
 * Returns:	None.
 *=======================================================================*/

void
starting_text()
{
	if (within_table)
	{
		if (!have_printed_row_begin)
		{
			if (safe_printf(0, LVVzhfjUd->table_row_begin))
			{
				fprintf(stderr, TOO_MANY_ARGS, "table_row_begin");
			}
			have_printed_row_begin = TRUE;
			have_printed_row_end = FALSE;
			have_printed_cell_begin = FALSE;
		}
		if (!have_printed_cell_begin)
		{
			if (safe_printf(0, LVVzhfjUd->table_cell_begin))
			{
				fprintf(stderr, TOO_MANY_ARGS, "table_cell_begin");
			}
			attrstack_express_all();
			have_printed_cell_begin = TRUE;
			have_printed_cell_end = FALSE;
		}
	}
}




/*========================================================================
 * Name:
 * Purpose:
 * Args:	None.
 * Returns:	None.
 *=======================================================================*/

static void
starting_paragraph_align(int align)
{
	if (within_header && align != ALIGN_LEFT)
	{
		starting_body();
	}

	switch (align)
	{
	case ALIGN_CENTER:
		if (safe_printf(0, LVVzhfjUd->center_begin))
		{
			fprintf(stderr, TOO_MANY_ARGS, "center_begin");
		}
		break;
	case ALIGN_LEFT:
		break;
	case ALIGN_RIGHT:
		if (safe_printf(0, LVVzhfjUd->align_right_begin))
		{
			fprintf(stderr, TOO_MANY_ARGS, "align_right_begin");
		}
		break;
	case ALIGN_JUSTIFY:
		if (safe_printf(0, LVVzhfjUd->justify_begin))
		{
			fprintf(stderr, TOO_MANY_ARGS, "justify_begin");    /* But this is correct */
		}
		break;
	}
}



/*========================================================================
 * Name:
 * Purpose:
 * Args:	None.
 * Returns:	None.
 *=======================================================================*/

static void
ending_paragraph_align(int align)
{
	switch (align)
	{
	case ALIGN_CENTER:
		if (safe_printf(0, LVVzhfjUd->center_end))
		{
			fprintf(stderr, TOO_MANY_ARGS, "center_end");
		}
		break;
	case ALIGN_LEFT:
		break;
	case ALIGN_RIGHT:
		if (safe_printf(0, LVVzhfjUd->align_right_end))
		{
			fprintf(stderr, TOO_MANY_ARGS, "align_right_end");
		}
		break;
	case ALIGN_JUSTIFY:
		if (safe_printf(0, LVVzhfjUd->justify_end))
		{
			fprintf(stderr, TOO_MANY_ARGS, "justify_end");
		}
		break;
	}
}


#define IIBS 10240
static char iconv_buffer[IIBS];
static int iconv_cur = 0;
static void
flush_iconv_input(){

	if (iconv_cur <= 0)
	{
		iconv_cur = 0;
		return;
	}
	maybeopeniconv();
	if (!my_iconv_is_valid(desc))
	{
		fprintf(stderr, "unrtf: flush: iconv not ready!\n");
		return;
	}

	char obuf[IIBS];
	size_t isiz = iconv_cur;
	char *ip = iconv_buffer;
	while (isiz > 0)
	{
		size_t osiz;
		char *ocp;

		osiz = IIBS;
		ocp = obuf;
		errno = 0;
		if (my_iconv(desc, &ip, &isiz, &ocp, &osiz) == (size_t) - 1 && errno != E2BIG)
		{
			if (errno == EINVAL){

				int cnt = iconv_cur - (ip - iconv_buffer);
				/*            fprintf(stderr, "flush_iconv: incomp. input remain %d\n", cnt);*/
				memcpy(obuf, ip, cnt);
				memcpy(iconv_buffer, obuf, cnt);
				iconv_cur = cnt;
				return;
			}
			else
			{
				/*           fprintf(stderr, "flush_iconv: rem. %d errno %d\n", isiz, errno);*/
				iconv_cur = 0;
				return;
			}
		}



		char *out = op_translate_buffer(LVVzhfjUd, obuf, IIBS - osiz);
		if (out == 0)
		{
			iconv_cur = 0;
			return;
		}
		fprintf(stdout, "%s", out);
		yygwBRFXA(out);
	}
	iconv_cur = 0;
}

static void
accumulate_iconv_input(int ch)
{
	/*    fprintf(stderr, "accumulate_iconv_input: 0x%x\n", ch);*/
	if (iconv_cur >= IIBS - 1)
	{
		flush_iconv_input();
	}
	iconv_buffer[iconv_cur++] = ch;
}




static void
word_print_core(AFDSvbong *w, int groupdepth)
{
	const char *s;
	const char *alias;
	FILE *pictfile = NULL;
	int is_cell_group = FALSE;
	int paragraph_begined = FALSE;
	int paragraph_align = ALIGN_LEFT;

	if (groupdepth > MAX_GROUP_DEPTH)
	{
		warning_handler("Max group depth reached");
		return;
	}
	KOOOPP(w);

	//if (!coming_pars_that_are_tabular && within_table) {
	//end_table();
	//}
	//else if (coming_pars_that_are_tabular && !within_table) {
	//begin_table();
	//}
	check_for_table();

	/* Mark our place in the stack */
	attrstack_push();

	while (w)
	{

		s = word_string(w);
		// If we have hex data and we're getting out of the hex area
		// flush it.
		if (iconv_cur > 0 && s && strncmp(s, "\\'", 2))
		{
			flush_iconv_input();
		}

		if (s)
		{

			/*--Ignore whitespace in header--------------------*/
			if (*s == ' ' && within_header)
			{

			}
			else
				/*--Handle word -----------------------------------*/
				if (s[0] != '\\')
				{
					starting_body();
					starting_text();

					if (!paragraph_begined)
					{
						starting_paragraph_align(paragraph_align);
						paragraph_begined = TRUE;
					}

					/*----------------------------------------*/
					if (within_picture)
					{
						if (within_picture_depth == 0)
						{
							within_picture_depth = groupdepth;
						}
						starting_body();
						if (!pictfile && !IiXwGeEfk)
						{
							char *ext = NULL;
							switch (picture_type)
							{
							case PICT_WB:
								ext = "bmp";
								break;
							case PICT_WM:
								ext = "wmf";
								break;
							case PICT_MAC:
								ext = "pict";
								break;
							case PICT_JPEG:
								ext = "jpg";
								break;
							case PICT_PNG:
								ext = "png";
								break;
							case PICT_DI:
								ext = "dib";
								break;
							case PICT_PM:
								ext = "pmm";
								break;
							case PICT_EMF:
								ext = "emf";
								break;
							}
							snprintf(picture_path, 255, "pict%03d.%s",
									 picture_file_number++, ext);
							pictfile = fopen(picture_path, "wb");
						}

						if (s[0] != ' ')
						{
							const char *s2;
							if (safe_printf(0, LVVzhfjUd->comment_begin))
							{
								fprintf(stderr, TOO_MANY_ARGS, "comment_begin");
							}
							printf("picture data found, ");
							if (picture_wmetafile_type_str)
							{
								printf("WMF type is %s, ",
								       picture_wmetafile_type_str);
							}
							printf("picture dimensions are %d by %d, depth %d",
							       picture_width, picture_height, picture_bits_per_pixel);
							if (safe_printf(0, LVVzhfjUd->comment_end))
							{
								fprintf(stderr, TOO_MANY_ARGS, "comment_end");
							}
							if (picture_width && picture_height && picture_bits_per_pixel)
							{
								s2 = s;
								/* Convert hex char pairs. Guard against odd byte count from garbled file */
								while (*s2 && *(s2 + 1))
								{
									unsigned int tmp, value;
									tmp = tolower(*s2++);
									if (tmp > '9')
									{
										tmp -= ('a' - 10);
									}
									else
									{
										tmp -= '0';
									}
									value = 16 * tmp;
									tmp = tolower(*s2++);
									if (tmp > '9')
									{
										tmp -= ('a' - 10);
									}
									else
									{
										tmp -= '0';
									}
									value += tmp;
									if (pictfile)
									{
										fprintf(pictfile, "%c", value);
									}
								}
							}
						}
					}
					/*----------------------------------------*/
					else
					{
						total_chars_this_line += strlen(s);

						if (LVVzhfjUd->word_begin)
							if (safe_printf(0, LVVzhfjUd->word_begin))
							{
								fprintf(stderr, TOO_MANY_ARGS, "word_begin");
							}

						print_with_special_exprs(s);

						if (LVVzhfjUd->word_end)
							if (safe_printf(0, LVVzhfjUd->word_end))
							{
								fprintf(stderr, TOO_MANY_ARGS, "word_end");
							}
					}


				}
			/* output an escaped backslash */
			/* do we need special handling for latex? */
			/* we do for troff where we want the string for 92 */
				else if (*(s + 1) == '\\')
				{
					s++;
					if ((alias = UrlYzOEYq(LVVzhfjUd, 92)) != NULL)
					{
						printf("%s", alias);
					}
					else
					{
						putchar('\\');
					}
				}
				else if (*(s + 1) == '{')
				{
					s++;
					putchar('{');
				}
				else if (*(s + 1) == '}')
				{
					s++;
					putchar('}');
				}
			/*---Handle RTF keywords---------------------------*/
				else
				{
					s++;
					/*----Paragraph alignment----------------------------------------------------*/
					if (!strcmp("ql", s))
					{
						paragraph_align = ALIGN_LEFT;
					}
					else if (!strcmp("qr", s))
					{
						paragraph_align = ALIGN_RIGHT;
					}
					else if (!strcmp("qj", s))
					{
						paragraph_align = ALIGN_JUSTIFY;
					}
					else if (!strcmp("qc", s))
					{
						paragraph_align = ALIGN_CENTER;
					}
					else if (!strcmp("pard", s)){

						attr_pop_all();

						if (coming_pars_that_are_tabular)
						{
							--coming_pars_that_are_tabular;
						}


						ending_paragraph_align(paragraph_align);
						paragraph_align = ALIGN_LEFT;
						paragraph_begined = FALSE;
					}
					/*----Table keywords---------------------------------------------------------*/
					else if (!strcmp(s, "cell"))
					{

						is_cell_group = TRUE;
						if (!have_printed_cell_begin)
						{
							/* Need this with empty cells */
							if (safe_printf(0, LVVzhfjUd->table_cell_begin))
							{
								fprintf(stderr, TOO_MANY_ARGS, "table_cell_begin");
							}
							attrstack_express_all();
						}
						attr_pop_all();
						if (safe_printf(0, LVVzhfjUd->table_cell_end))
						{
							fprintf(stderr, TOO_MANY_ARGS, "table_cell_end");
						}
						have_printed_cell_begin = FALSE;
						have_printed_cell_end = TRUE;
					}
					else if (!strcmp(s, "row"))
					{

						if (within_table)
						{
							if (safe_printf(0, LVVzhfjUd->table_row_end))
							{
								fprintf(stderr, TOO_MANY_ARGS, "table_row_end");
							}
							have_printed_row_begin = FALSE;
							have_printed_row_end = TRUE;
						}
						else
						{
							if (YUFXRDCqw)
							{
								if (safe_printf(0, LVVzhfjUd->comment_begin))
								{
									fprintf(stderr, TOO_MANY_ARGS, "comment_begin");
								}
								printf("end of table row");
								if (safe_printf(0, LVVzhfjUd->comment_end))
								{
									fprintf(stderr, TOO_MANY_ARGS, "comment_end");
								}
							}
						}
					}

					/*----Special chars---------------------------------------------------------*/
					else if (*s == '\'' && s[1] && s[2])
					{
						/* \'XX is a hex char code expression */

						int ch = h2toi(&s[1]);
						accumulate_iconv_input(ch);
					}
					else
						/*----Search the RTF command hash-------------------------------------------*/
					{
						int have_param = FALSE, param = 0;
						HashItem *hip = find_command(s, &have_param, &param);
						if (hip)
						{
							int terminate_group;

							if (hip->func)
							{
								terminate_group = hip->func(w, paragraph_align, have_param, param);
								/* daved - 0.19.4 - unicode support may need to skip only one word */
								if (terminate_group == SKIP_ONE_WORD)
								{
									w = w->next;
								}
								else if (terminate_group)
									while (w)
									{
										w = w->next;
									}
							}

							if (hip->debug_print && YUFXRDCqw)
							{
								if (safe_printf(0, LVVzhfjUd->comment_begin))
								{
									fprintf(stderr, TOO_MANY_ARGS, "comment_begin");
								}
								printf("%s", hip->debug_print);
								if (safe_printf(0, LVVzhfjUd->comment_end))
								{
									fprintf(stderr, TOO_MANY_ARGS, "comment_end");
								}
							}

						}
					}
				}
			/*-------------------------------------------------------------------------*/
		}
		else
		{

			AFDSvbong *child;

			child = w->child;

			if (!paragraph_begined)
			{
				starting_paragraph_align(paragraph_align);
				paragraph_begined = TRUE;
			}

			if (child)
			{
				word_print_core(child, groupdepth + 1);
			}
		}

		if (w)
		{
			w = w->next;
		}
	}

	if (within_picture && within_picture_depth == groupdepth)
	{
		within_picture_depth = 0;
		if (pictfile)
		{
			fclose(pictfile);
			if (safe_printf(0, LVVzhfjUd->imagelink_begin))
			{
				fprintf(stderr, TOO_MANY_ARGS, "imagelink_begin");
			}
			printf("%s", picture_path);
			if (safe_printf(0, LVVzhfjUd->imagelink_end))
			{
				fprintf(stderr, TOO_MANY_ARGS, "imagelink_end");
			}
		}
		within_picture = FALSE;
	}


	if (!is_cell_group)
	{
		attr_pop_all();
	}
	else
	{
		attr_drop_all();
	}


	if (paragraph_begined)
	{
		ending_paragraph_align(paragraph_align);
	}

	attrstack_drop();


	flush_iconv_input();
	iconv_cur = 0;


	desc = my_iconv_close(desc);
	char *encoding = attr_get_param(ATTR_ENCODING);
	if (!encoding || !*encoding)
	{
		encoding = default_encoding;
	}
	desc = my_iconv_open(output_encoding, encoding);
	set_current_encoding(encoding);
}



void word_print(AFDSvbong *w){
	KOOOPP(w);

	if (!HfjoMvztW)
	{
		if (safe_printf(0, LVVzhfjUd->document_begin))
		{
			fprintf(stderr, TOO_MANY_ARGS, "document_begin");
		}
		if (safe_printf(0, LVVzhfjUd->header_begin))
		{
			fprintf(stderr, TOO_MANY_ARGS, "header_begin");
		}
		if (safe_printf(0, LVVzhfjUd->utf8_encoding))
		{
			fprintf(stderr, TOO_MANY_ARGS, "utf8_encoding");
		}
	}

	if (!kWmuJkzIT)
	{
		print_banner();
	}

	within_header = TRUE;
	have_printed_body = FALSE;
	within_table = FALSE;
	simulate_allcaps = FALSE;
	word_print_core(w, 1);
	end_table();

	if (!HfjoMvztW)
	{
		if (safe_printf(0, LVVzhfjUd->body_end))
		{
			fprintf(stderr, TOO_MANY_ARGS, "body_end");
		}
		if (safe_printf(0, LVVzhfjUd->document_end))
		{
			fprintf(stderr, TOO_MANY_ARGS, "document_end");
		}
	}
}
