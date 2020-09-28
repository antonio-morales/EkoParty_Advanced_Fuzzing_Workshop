#ifndef _UNICODE_H_INCLUDED_
#define _UNICODE_H_INCLUDED_

/*----------------------------------------------------------------------
 * Module name:    unicode
 * Author name:    Arkadiusz Firus
 * Create date:    09 Nov 08
 * Purpose:        unicode translations
 *----------------------------------------------------------------------
 * Changes:
 * 07 Oct 11, jf@dockes.org: added _UNICODE_H_INCLUDED_, changed
 *	get_unicode_char to get_unicode_utf8
 *--------------------------------------------------------------------*/
/* Translate Uxxx or xxx as from charmap file to unicode value as integer */
extern int get_unicode(char *string);
/* Translate charmap line ('<' already read) to unicode or UTF-8 string */
extern int get_unicode_int(FILE *file);
extern char *get_unicode_utf8(FILE *file);
#endif /* _UNICODE_H_INCLUDED_ */
