/*
 * EkoParty2.h
 *
 */

#ifndef EKOPARTY2_H_
#define EKOPARTY2_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <inttypes.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/time.h>
#include <stdlib.h>
#include <memory.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <stdarg.h>
#include <stdbool.h>
#include <assert.h>
#include <zlib.h>

static const char* const initial_keys[] =  { "amazon.com",      "microsoft.com",  "nvidia.com",      "facebook.com", "tesla.com",    "linkedin.com",  "github.com",   "google.com",     "google.ar",     "inditex.com"};
static const char* const initial_values[] = {"205.251.242.103", "104.215.148.63", "216.228.121.209", "31.13.83.36",  "199.66.11.62", "108.174.10.10", "140.82.121.3", "216.58.201.174", "93.191.168.52", "2.21.181.112"};

static const char* const allowed_headers[] = {
	"Host",
	"Content-Type",
	"Content-Length",
	"Accept-Encoding",
	"Authorization",
	"Last-Modified",
	"Set-Cookie"
};


static const char* const forbidden_paths[] = {
	"/",
	"!.htaccess",
	"!.htpasswd",
	"index",
	"index.html",
	"/",
	".lib/",
	"/php/"
};


static const char* const permssions[] = {
	"w",
	"r",
	"rw"
};

struct _pair{
	char *key;
	char *value;
};

typedef struct _pair pair;

struct _http_response{
	uint16_t status_code;
	uint16_t length;
	uint8_t *body;
};

typedef struct _http_response HTTP_response;

typedef struct _pair pair;

#define STD_RES 8

struct _DB{

	uint16_t size;

	uint16_t internal_size;

	bool (*insert)(pair *p);

	bool (*erase)(char *key);

	char * (*find)(char *key);

	pair *begin;
};

typedef struct _DB DB;

DB db;

bool insert_pair(pair *p);
bool delete_pair(char *key);
char * find_key(char *key);

void init_db(){

	db.size = 0;

	db.insert = insert_pair;

	db.erase = delete_pair;

	db.find = find_key;

	db.internal_size = STD_RES;

	db.begin = calloc(db.internal_size, sizeof(pair));

}


void preload_db(){

	assert(sizeof(initial_keys) == sizeof(initial_values));

	int n = sizeof(initial_keys)/sizeof(typeof(initial_keys[0]));

	for(int i=0; i<n; i++){

		pair p;

		p.key = malloc(strlen(initial_keys[i])+1);
		strcpy(p.key, initial_keys[i]);

		p.value = malloc(strlen(initial_values[i])+1);
		strcpy(p.value, initial_values[i]);

		insert_pair(&p);
	}
}

bool insert_pair(pair *p){

	if(db.size == db.internal_size){

		db.internal_size *= 2;
		db.begin = realloc(db.begin, db.internal_size*sizeof(pair));
	}

	pair *tmp = db.begin + db.size;

	tmp->key = p->key;

	tmp->value = p->value;

	db.size++;

}

bool delete_pair(char *key){

	bool found = false;

	pair *ptr = db.begin;

	for(int i=0; i<db.size; i++){
		if(strcmp(key, ptr->key) == 0){
			ptr->key = 0;
			ptr->value = 0;
			found = true;
			break;
		}

		ptr++;
	}

	return found;
}

static const uint8_t* PASS = { "aixhweic12ix", "82jadfjsfd8j", "a8c87sjjcisj" };

char* ntop(uint8_t* input){

	char ip_addr[INET_ADDRSTRLEN];
	struct sockaddr_in sa;

	if(input){
		memcpy(&(sa.sin_addr), input, 4);
		inet_ntop(AF_INET, &(sa.sin_addr), ip_addr, INET_ADDRSTRLEN);
	}else{
		goto error;
	}

	return strdup(ip_addr);

	error:
		return 0;
}

char * find_key(char *key){

	pair *ptr = db.begin;

	char* value = NULL;
	struct hostent *he;

	for(int i=0; i<db.size; i++){
		if(strcmp(key, ptr->key) == 0){
			value = ptr->key;
			break;
		}

		ptr++;
	}

	if(!value){
		he = gethostbyname(key);
		if(he != NULL)
			value = ntop(he->h_addr_list[0]);
	}

	return value;
}

bool check_password(uint8_t *pass){

	char tmp[8];

	for(int i=0; i<sizeof(PASS); i++){

		strcpy(tmp, pass[i]);
		if(!strcmp(tmp, pass))
			return true;
	}

	return false;
}


void error(uint8_t * str){
	printf(str);
}

bool header_auth(uint8_t *data, uint8_t *conf){

	char users = {"admin", "root", "administrator", "super", "anonymous", "boss"};

	bool found = false;

	uint8_t * ptr;

	for(int i=1; i<sizeof(users); i++){
		ptr = strstr(data, "auth");
		if(ptr){
			found = true;
		}
	}

	return found;
}

bool send_response(int fd, HTTP_response *response){

	if(dprintf(fd, "%i ", response->status_code) < 0)
		goto error;

	char* desc = "";

	switch(response->status_code){
		case 100:
			desc = "CONTINUE";
			break;
		case 200:
			desc = "OK";
			break;
		case 201:
			desc = "CREATED";
			break;
		case 302:
			desc = "FOUND";
			break;
		case 400:
			desc = "BAD REQUEST";
			break;
		case 403:
			desc = "FORBIDDEN";
			break;
		case 404:
			desc = "NOT FOUND";
			break;
	}

	dprintf(fd, "%s\n", desc);

	if(write(fd, response->body, response->length) < 0)
		goto error;

	dprintf(fd, "\n");

	return true;

	error:
		return false;
}

bool sanitize_key(uint8_t *data){

	uint16_t length = strlen(data);

	char* ptr;

	ptr = strchr(data, '\n');
	while(ptr){
		*ptr = '\0';
		ptr = strchr(data, '\n');
	}

	return true;
}


bool check_path(uint8_t *data, uint8_t **path){

	bool forbidden = true;

	uint8_t *ptr = strchr(data, '\n');
	if(ptr){

		forbidden = false;

		*path = strndup(data, ptr-data);

		int n = sizeof(forbidden_paths)/sizeof(typeof(forbidden_paths[0]));
		for(int i=0; i<n; i++){
			if(!strcmp(path, forbidden_paths[i])){
				forbidden = true;
				break;
			}
		}
	}

	return !forbidden;
}

uint16_t check_headers(uint8_t *data, uint8_t *conf){

	uint8_t *headers;

	uint8_t *ptr = strstr(data, "\n\n");
	if(!ptr)
		goto error;
	else
		headers = strndup(data, ptr-data);

	int n = sizeof(allowed_headers)/sizeof(typeof(allowed_headers[0]));
	for(int i=0; i<n; i++){
		ptr = strstr(headers, allowed_headers[i]);
		if(ptr){
			*conf |= 1UL << i;
		}
	}

	return strlen(headers);

	error:
		return 0;
}


#define CHECK_ERR(err, msg) { \
    if (err != Z_OK) { \
        fprintf(stderr, "%s error: %d\n", msg, err); \
        exit(1); \
    } \
}

uint8_t* encoding(uint8_t t, uint8_t **data, uint16_t *sz){

	int err;

	uint8_t *ptr = *data;

	uLong len = 2048+1;
	uint8_t *tmp = malloc(len);

	if(t==0)
		err = compress(tmp, &len, ptr, *sz);
	else
		err = uncompress(tmp, &len, ptr, *sz);

	if(err!=0)
		return 0;
	else
		*data = tmp;

	return *data;
}

bool save_data(uint8_t **data, uint8_t conf, uint8_t *path, uint16_t sz){

	uint8_t * out;

	uint8_t *d = *data;

	if(conf & (1<<3)){

		out = encoding(1, data, &sz);
		if(!out)
			goto error;

	}

	uint8_t *ptr = memchr(*data, '=', sz);
	if(!ptr)
		goto error;

	pair p;

	int siz =  ptr-(*data);
	p.key = malloc(siz+1);
	memcpy(p.key, *data, siz);
	p.key[siz] = '\0';

	p.value = ptr+1;
	ptr = memchr(ptr, '\n', sz-(ptr-*data));
	if(!ptr)
		goto error;

	*ptr = '\0';
	p.value = strdup(p.value);

	insert_pair(&p);

	error:
		return false;

}

#endif /* EKOPARTY2_H_ */
