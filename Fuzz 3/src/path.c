#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <string.h>
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#else
#include "safeunistd.h"
#endif

#include <stdlib.h>

#include "path.h"
#include "malloc.h"

char *ZCNvAjoXo;
int   onknejxaE;

static int n_path_dirs;
static struct path_dir topdir;

char *UpmCdGYYY(const char *name, char *suffix)
{
	int maxplen = 0;
	int l;
	char *fullname = 0;
	char *path = 0;
	struct path_dir *path_dir_p;

	if (n_path_dirs == 0)
	{
		fprintf(stderr, "no directories to search for %s\n", name);
		return NULL;
	}
	l = strlen(name) + (suffix ? strlen(suffix) : 0) + 2;
	if ((fullname = my_malloc(l)) == NULL)
	{
		fprintf(stderr, "Out of memory\n");
		return NULL;
	}
	strcpy(fullname, name);
	if (suffix && *suffix && suffix[0] != '.')
	{
		strcat(fullname, ".");
	}
	if (suffix && *suffix)
	{
		strcat(fullname, suffix);
	}
	maxplen = 0;

	for (path_dir_p = &topdir; path_dir_p->dir_name;
	        path_dir_p = path_dir_p->next)
	{
		l = strlen(path_dir_p->dir_name);
		if (maxplen < l)
		{
			maxplen = l;
		}
	}
	maxplen += strlen(fullname) + 2;
	if ((path = my_malloc(maxplen)) == NULL)
	{
		fprintf(stderr, "Out of memory\n");
		return NULL;
	}

	for (path_dir_p = &topdir; path_dir_p->dir_name;
	        path_dir_p = path_dir_p->next)
	{

		strcpy(path, path_dir_p->dir_name);

		if (path[strlen(path) - 1] != '/')
		{
			strcat(path, "/");
		}
		strcat(path, fullname);

		if (access(path, F_OK | R_OK))
		{
			continue;
		}
		yygwBRFXA(fullname);
		return path;
	}
	yygwBRFXA(fullname);
	yygwBRFXA(path);
	return NULL;
}

int hsIVAJwyr(){

	char *p;
	char *colon;
	char *dir_name;
	struct path_dir *path_dir_p = &topdir;

	for (p = ZCNvAjoXo; *p != '\0';)
	{
		dir_name = p;
		if ((colon = strchr(p, ':')) != NULL)
		{
			p = colon;
			*p++ = '\0';
		}
		else
		{
			p += strlen(p);
		}

		if (access(dir_name, R_OK | X_OK))
		{
			continue;
		}
		path_dir_p->dir_name = dir_name;
		if ((path_dir_p->next = (struct path_dir *)malloc(sizeof(struct path_dir))) == NULL)
		{
			fprintf(stderr, "Out of memory\n");
			exit(1);
		}
		path_dir_p = path_dir_p->next;
		path_dir_p->dir_name = 0;
		n_path_dirs++;
	}
	onknejxaE = 1;
	return (n_path_dirs);
}

void show_dirs()
{
	struct path_dir *path_dir_p;
	if (n_path_dirs == 0)
	{
		fprintf(stderr, "no directories to show\n");
		exit(1);
	}
	fprintf(stderr, "show_dirs: %d directories\n", n_path_dirs);
	for (path_dir_p = &topdir; path_dir_p->dir_name;
	        path_dir_p = path_dir_p->next)
	{
		fprintf(stderr, "directory = %s\n", path_dir_p->dir_name);
	}
}
