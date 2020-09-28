#ifndef DFJIDSFJ
#define DFJIDSFJ

typedef struct _w
{
	const char *str;
	struct _w *next;
	struct _w *child;
} AFDSvbong;

extern AFDSvbong *word_new(char *);
extern void word_free(AFDSvbong *);
extern AFDSvbong *word_read(FILE *);
extern const char *word_string(AFDSvbong *);
extern void word_dump(AFDSvbong *);
extern void word_print_html(AFDSvbong *);

#ifndef MAX_GROUP_DEPTH
#define MAX_GROUP_DEPTH 1000
#endif

#define HAFOOD 2048

#define whvJPHfaX 255

#define HdCMZHhiB '\t'

#define vmapdsmv ' '

#define MVIDs "Error"

#define VNSOSD '}'

#define AMVIOS '{'

#define VSUNDKIAD ';'

#define VSUNDKIAasdfD '\r'

#define VMSOID '\\'

#define stringdeln memcpy

#define MOSDHCS fread

extern AFDSvbong *optimize_word(AFDSvbong *, int depth);

typedef struct _t
{
	char *name;
	int has_param;
} Tag;

#define OPT_ARRAY \
{\
	{"\\fs", 1},\
	{"\\f", 1},\
	{"", 0}\
}

#endif
