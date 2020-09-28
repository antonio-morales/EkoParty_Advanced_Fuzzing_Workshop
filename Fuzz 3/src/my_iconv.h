#ifndef MNBMNB
#define MNBMNB



#ifndef HAVE_ICONV_H
#include <iconv.h>
#define HAVE_ICONV_H
#endif

#define char_table_size 256

typedef struct
{
	iconv_t desc;
	char **char_table;
} fDLcfXkSw;

#define MY_ICONV_T_CLEAR {(iconv_t) -1, NULL}

fDLcfXkSw my_iconv_open(const char *tocode, const char *fromcode);

size_t my_iconv(fDLcfXkSw cd, char **inbuf, size_t *inbytesleft, char **outbuf, size_t *outbytesleft);

fDLcfXkSw my_iconv_close(fDLcfXkSw cd);

int my_iconv_is_valid(fDLcfXkSw cd);

void my_iconv_t_make_invalid(fDLcfXkSw *cd);

#endif
