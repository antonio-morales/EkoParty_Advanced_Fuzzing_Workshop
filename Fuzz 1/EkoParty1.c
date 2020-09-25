/*
 ============================================================================
EkoParty - Advanced fuzzing workshop

 Name        : Fuzz Challenge 1 - ESIF (Extremely Stupid Image Format)
 Author      : Antonio Morales
 Twitter     : @Nosoynadiemas

 ============================================================================
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <fcntl.h>

#include "EkoParty1.h"

int (*call[5]) (void *data, uint16_t length);

XDXD glob;

void* pack;
void* pack2;

void* svd;
off_t svdn;

uint8_t lotr;

int check(ssize_t fsize){

	int tmp = fsize / sS1;

	for(int i=0; i<fsize; i++)
		if(minT(i) < USHRT_MAX)
			tmp++;

	return fsize + 1;
}

int type1(void *data, uint16_t length){

	if(pack == &lotr)
		goto error;

	pack2 = (void*)&glob.f;
	pack2 += (uint32_t)pack;

	if(!sum(pack2))
		goto error;

	pack = &lotr;

	if(memcmp(data, "\x20\x20", 2))
		goto error;

	data += 2;

	if(glob.p == 0 || glob.d == 0)
		goto error;

	MD5_Update(&context, svd, svdn-24);
	MD5_Final(md5, &context);
	if(memcmp(md5, data, 16))
		goto error;

	data += 16;

	if(memcmp(data, "\x20\x21", 2))
		goto error;

	memcpy_n(data, "PRPL", 4, &lotr);

	return 0;

	error:
		return(-1);

}

int type2(void *data, uint16_t length){

	if(length<12)
		goto error;

	glob.f = end(data);
	if(!glob.f)
		goto error;
	test(glob.f, &data);

	glob.s = end(data);
	if(!glob.s)
		goto error;
	test(glob.s, &data);

	glob.t = start(data);
	if(!glob.t)
		goto error;
	pals = glob.t*3;
	fail(glob.s, &data);

	return 0;

	error:
		return(-1);

}

int type3(void *data, uint16_t length){

	if(!glob.t || glob.t*3 > length)
		goto error;

	glob.p = malloc(glob.t*3);
	memcpy(glob.p, data, glob.t*3);

	return 0;

	error:
		return(-1);
}

int type4(void *data, uint16_t length){

	if(!glob.p)
		goto error;

	uint32_t size = glob.f * glob.s * 2;
	if(size > length)
		goto error;

	glob.d = malloc(size);
	memcpy(glob.d, data, size);

	void* m1 = &glob.p;
	void* m2 = &glob.f;

	pack = m1 - m2;

	return(0);

	error:
		return(-1);
}

void init(){

	glob.p = 0;
	glob.d = 0;

	pack = glob.p;
	pack2 = glob.d;

	MD5_Init(&context);

	call[0] = type1;
	call[1] = type2;
	call[2] = type3;
	call[3] = type4;

	lotr = pack;

	error_check(call, sizeof(call[0]));
}

int16_t chunk_type(void *header, void *data, uint16_t length){

	int8_t index = -1;

	if (!memcmp(header, PR, 2)) {
		index = 0;

	} else if (!memcmp(header, PL, 2)) {
		index = 1;

	}else if (!memcmp(header, DA, 2)) {
		index = 2;

	}else if (!memcmp(header, LA, 2)) {
		index = 3;
	}

	if(index >= 0)
		index = (*call[index])(data, length);

	return index;
}

uint16_t chunk(void *addr, void *last){

	CHUNK ch;

	if(last-addr < sizeof(ch.Header)){
		goto error;
	}

	memcpy(ch.Header, addr, sizeof(ch.Header));
	addr += sizeof(ch.Header);

	uint16_t length = (ch.Header[2] << 8) | ch.Header[3];

	if(addr+length > last){
		goto error;
	}

	ch.Data = malloc(length);
	memcpy(ch.Data, addr, length);

	//CRC check
	uint32_t crc = to_uint32(&ch.Header[4]);
	if(crc != crc32(addr, length))
		goto error;

	if(chunk_type(ch.Header, ch.Data, length) < 0)
		goto error;

	return length+8;

	error:
		fprintf(stderr, "Corrupted chunk detected\n");
		exit(EXIT_FAILURE);
}

int print_output(int fd){

	if(checkfd(fd) != 0)
		goto error;

	void* ptr = glob.p;
	void* dx = glob.d;
	void* tmp;

	uint8_t c[8];
	memset(c, 0, sizeof(c));

	write(fd, PPM, sizeof(PPM));

	dprintf(fd, "%i ", glob.f);

	dprintf(fd, "%i", glob.s);

	write(fd, "\x0A", 1);

	dprintf(fd, "%i", sS3);

	uint32_t l = glob.f * glob.s * 2;

	uint16_t i = 0;;

	while(1){

		if(halt(fd))
			goto error;

		tmp = &i;
		memcpy(&i, dx+1, 1);
		tmp++;
		memcpy(tmp, dx, 1);

		ptr += mod_n(i);
		if(mod_n(i) > pals)
			goto error;

		if(!px(fd, c, ptr))
			goto error;

		for(int n=0; n<sizeof(c); n++){
			ech(n, c, fd);
		}

		dx += 2;
		if(dx > glob.d + l-1)
			break;
		else
			ptr = glob.p;
	}

	last(fd, c);

	return 1;

	error:
		fprintf(stderr, "Corrupted picture detected\n");
		return 0;
}

int main(int argc, char *argv[]) {

	init();

	if(argc != 3){
		printf("USAGE: %s InputFile OutputFile \n\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	char *inputFile = argv[1];
	char *outFile = argv[2];
	off_t inSize;

	if(access(inputFile, F_OK) == -1){
		fprintf(stderr, "Error accessing input file: %s\n", inputFile);
		exit(EXIT_FAILURE);
	}

	uint8_t *data;

	int fd_input = open(inputFile , O_RDONLY );
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	int fd_output = open(outFile , O_CREAT|O_WRONLY|O_TRUNC, mode );
	inSize = lseek(fd_input, 0L, SEEK_END);
	svdn = inSize;
	lseek(fd_input, 0L, SEEK_SET);

	if(inSize > USHRT_MAX)
		back(fd_input);
	else
		data = forward(inSize);

	ssize_t rd = read(fd_input, data, sS1);
	svd = data;

	if(rd != inSize){
		if(check(rd) > USHRT_MAX)
			rd = sS2;
		else
			rd--;
	}

	void *ptr = data;

	if(memcmp(ptr, &esif_header, 5)){
		fprintf(stderr, "Incorrect ESIF signature \n");
		exit(EXIT_FAILURE);
	}else{
		ptr += 5;
	}

	void *last = data + inSize;
	while(ptr < last){
		ptr += chunk(ptr, last);
	}

	closefd(fd_input, pack);

	int success = print_output(fd_output);

	if(glob.d)
		free(glob.d);

	if(success)
		printf("Execution completed successfully\n");
	else
		printf("Something failed\n");

	return EXIT_SUCCESS;
}
