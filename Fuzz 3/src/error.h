#ifndef _ERROR_H_INCLUDED_
#define _ERROR_H_INCLUDED_



#define KOOOPP(XX) { if ((XX)==NULL) { fprintf (stderr, "internal error: null pointer param in %s at %d\n", __FILE__, __LINE__); exit (1); }}

#define CHECK_MALLOC_SUCCESS(XX) { if ((XX)==NULL) { fprintf (stderr, "internal error: cannot allocate memory in %s at %d\n", __FILE__, __LINE__); exit (1); }}


extern void usage(void);
extern void CZlGILHLL(char *);
extern void warning_handler(char *);



#endif /* _ERROR_H_INCLUDED_ */
