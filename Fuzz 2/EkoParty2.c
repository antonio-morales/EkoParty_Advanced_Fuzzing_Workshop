/*
 ============================================================================
EkoParty - Advanced fuzzing workshop

 Name        : Fuzz Challenge 2 - Crazy HTTP Server
 Author      : Antonio Morales
 Twitter     : @Nosoynadiemas

 ============================================================================
 */

#include "EkoParty2.h"

#define MAX_PACKET 2048


bool GET(uint8_t *data, HTTP_response *response){

	sanitize_key(data);

	response->body = find_key(data);
	if(response->body){
		response->status_code = 200;
		response->length = strlen(response->body);
	}else{
		response->status_code = 404;
		response->length = 0;
	}

	return true;
}

bool PUT(uint8_t *data, HTTP_response *response){

	pair p;

	uint8_t *tmp;
	uint8_t *ptr = strstr(data, "\n\n");
	if(!ptr)
		goto error;

	if(strlen(ptr) < 20)
		goto error;

	ptr += 2;

	if(*ptr != '{' || *(ptr+1) != '"')
		goto error;

	ptr += 2;

	tmp = ptr;
	ptr = strstr(ptr, "\x22\x20\x3A\x20\x22");
	if(!ptr)
		goto error;

	p.key = strndup(tmp, ptr-tmp);

	ptr += 5;

	tmp = ptr;
	ptr = strchr(ptr, '"');
	if(!ptr)
		goto error;

	p.value = strndup(tmp, ptr-tmp);

	insert_pair(&p);

	response->status_code = 200;
	response->body = data;
	response->length = strlen(data);

	return true;

	error:
		response->status_code = 400;
		response->length = 0;

		return false;
}



bool POST(uint8_t *data, HTTP_response *response){

	uint8_t conf = 0;
	uint16_t sz;
	memcpy(&sz, data-5, sizeof(sz));
	sz -= 5;

	uint8_t *path;

	if(!check_path(data, &path)){
		goto error;

	}else{

		data += strlen(path)+1;
		sz -= (strlen(path)+1);

		uint16_t sz_headers = check_headers(data, &conf);
		if(!sz_headers)
			goto error;

		if(header_auth(data, conf))
			if(!check_password(data))
				goto error;

		data += sz_headers+2;
		sz -= (sz_headers+2);

		save_data(&data, conf, path, sz);

		response->status_code = 200;
		response->body = data;
		response->length = strlen(data);
	}

	return true;

	error:
		response->status_code = 404;
		response->length = 0;

		return false;
}

bool DELETE(uint8_t *data, HTTP_response *response){

	uint8_t *ptr = strchr(data, '\n');
	if(!ptr)
		goto error;

	uint8_t *key = strndup(data, ptr-data);

	if(!delete_pair(key))
		goto error;

	response->status_code = 200;
	response->length = 0;

	return true;

	error:
		response->status_code = 404;
		response->length = 0;

		return false;
}


bool HEAD(uint8_t *data, HTTP_response *response){

	static const char *intro = "HEAD";
	int s = strlen(intro)+1;
	response->body = malloc(s);
	strcpy(response->body, intro);

	uint8_t *ptr = data+1;

	if(*ptr == '\n')
		ptr++;
	else if(*ptr == '\r' && *ptr == '\n')
		ptr += 2;
	else
		ptr--; response->body = calloc(MAX_PACKET, 1);


	response->status_code = 200;

	strcat(response->body, ptr);
	response->length = strlen(response->body);

	return true;
}


static const uint8_t* METHOD[] = { "GET ", "POST ", "HEAD ", "PUT ", "DELETE " };

bool (*API[5])() = {GET, POST, HEAD, PUT, DELETE};


HTTP_response *parse_packet(uint8_t *packet, uint16_t size){

	packet[size] = '\0';

	HTTP_response *response;

	uint8_t n = sizeof(METHOD)/sizeof(uint8_t*);
	int i;
	for(i=0; i<n; i++){
		size_t s = strlen(METHOD[i]);
		if(size>s && !strncmp(packet, METHOD[i], s)){
			printf("Received %s method\n", METHOD[i]);
			if(i==1)
				memcpy(packet, &size, sizeof(size));

			uint8_t *tmp = packet+s;

			response = calloc(sizeof(HTTP_response), 1);
			(*API[i])(tmp, response);
			break;
		}
	}

	if(i==n)
		goto error;

	return response;

	error:
		return NULL;

}

void init(){

	init_db();

	preload_db();
}

int listen_socket(struct sockaddr_in s_addr, struct sockaddr_in c_addr){

	int sock, conn_socket;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0)
		goto error;

	if(bind(sock, (struct sockaddr *) &s_addr, sizeof(s_addr)) < 0)
		goto error;

	listen(sock, 5);

	int length = sizeof(c_addr);
	conn_socket = accept(sock, (struct sockaddr *) &c_addr, &length);
	if (conn_socket < 0)
		goto error;

	return conn_socket;

	error:
		return -1;
}

bool run_server(){

	int sock = 0;
	int conn_socket = 0;

	struct sockaddr_in s_addr, c_addr;

	bzero((char *) &s_addr, sizeof(s_addr));
	s_addr.sin_port = htons(500);
	s_addr.sin_family = AF_INET;
	s_addr.sin_addr.s_addr = INADDR_ANY;

	conn_socket = listen_socket(s_addr, c_addr);

	if (conn_socket < 0)
		goto error;

	uint8_t buffer[MAX_PACKET+1];

	ssize_t n = read(conn_socket, buffer, MAX_PACKET);

	HTTP_response *response = parse_packet(buffer, n);
	if(!response)
		goto error;

	if(!send_response(conn_socket, response))
		goto error;

	return true;

	error:
		return false;
}

void free_all(){

}

int main(int argc, char *argv[]){

	init();

	if(!run_server())
		printf("Something failed\n");
	else
		printf("Execution completed successfully\n");

	free_all();

	return EXIT_SUCCESS;
}
