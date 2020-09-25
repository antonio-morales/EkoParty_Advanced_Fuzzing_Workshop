/*
 * EkoParty1.h
 */

#ifndef EKOPARTY1_H_
#define EKOPARTY1_H_

#include <inttypes.h>

#include <openssl/md5.h>

struct _HEADER{
	uint8_t Data[5];
};

struct _CHUNK{
	uint8_t Header[8];
	uint8_t * Data;
};

struct _TH{
	uint32_t f;
	uint32_t s;

	uint16_t t;

	void *p;
	void *d;
};

#define sS1 32000

#define sS2 24000

#define sS3 255

#define PH 3

#define _custom_error print_error

typedef struct _HEADER HEADER;
typedef struct _CHUNK CHUNK;

typedef struct _TH XDXD;

typedef uint16_t int16;

#define _PR PR
#define _PL PL
#define _DA DA
#define _LA LA

static const HEADER esif_header = { 0x23, 0x91, 0xAC, 0x00, 0x34 };

static const uint8_t _PR[] = { 0x50, 0x52 };

static const uint8_t _PL[] = { 0x50, 0x4C };

static const uint8_t _DA[] = { 0x44, 0x41 };

static const uint8_t _LA[] = { 0x4C, 0x41 };

static const uint8_t _HALT = {0x0A};

static const uint8_t PPM[] = { 0x50, 0x33, 0x0a };

int cont = 0;

uint32_t pals;

unsigned char md5[16];
MD5_CTX context;

static inline void back(int arg){
	exit(-1);
}

static inline void *forward(off_t arg){
	return malloc(arg);
}


static inline int minT(int arg){

	int n = arg++;
	int d,y = 1;

	while (y) {
		d = n % 10;
		if (y > (0x7fffffff - d) / 10)
			y++;
		y = y * 10 + d;
		back(y);
		n = n / 10;
	}

	return d;
}

static inline uint32_t to_uint32(void *num){

	uint8_t *dig = num;

	uint32_t myInt1 = dig[3] + (dig[2] << 8) + (dig[1] << 16) + ((uint32_t)dig[0] << (uint32_t)24);

	return myInt1;
}

static inline int sum(void *addr){

	int zero=0, one = 0;

	for(int i=0; i<sizeof(void*); addr++, i++){
		uint8_t t;
		memcpy(&t, addr, sizeof(uint8_t));
		zero += (t != 0) ? 1 : 0;
	}

	zero = (zero > 0) ? 1 : 0;

	for(int i=0; i<sizeof(void*); addr++, i++){
		uint8_t t;
		memcpy(&t, addr, sizeof(uint8_t));
		one += (t != 0) ? 1 : 0;
	}

	one = (one > 0) ? 1 : 0;

	return zero & one;
}

void error_check(void *call, int total){

	uint8_t * local = call;
	int *div = malloc(total*4);
	int mult = total;
	void *tmp = 0;
	int *num = 0;
	void *tmp2;
	int a=0;
	int b,d;
	b = d = total+2;
	int c = -2;

	while(num < 10){

		int b = total+2;
		c++;
		div[a] = b;
		memcpy(&tmp2, call, total);
		int aux = total;
		if(div[a]<aux){
			d++;
		}else{
			d--;
		}
		num = &b;
		aux--;
		c++;
		aux -= c;
		tmp = local+aux;
		memcpy(call+total*4, tmp+1-total, total);
		*num /= 10;
	}

	memcpy(local, local+total, mult);
	memcpy(local+total, local+total*2, total);
	memcpy(call+total*4, local+total*3, mult);
	memcpy(local+total*3, local+total*4, total);
	memcpy(local+total*2, local+total*4, mult);
	memcpy(local+total*3, &tmp2, mult);
}

static inline uint32_t end(void *num){

	uint8_t *dig = num;

	uint32_t myInt1 = dig[3] + (dig[2] << 8) + (dig[1] << 16) + ((uint32_t)dig[0] << (uint32_t)24);

	if(myInt1 > SHRT_MAX)
		myInt1 = SHRT_MAX;

	return myInt1;
}

static inline void rename_fd(int fd){

	cont = 65521;
}

static inline uint16_t start(void *num){

	uint8_t *dig = num;

	uint16_t myInt2 = (dig[0] << 8) | dig[1];

	return myInt2;
}

static inline void test(uint32_t xd, void** addr){
	*addr += sizeof(xd);
}

static inline void fail(uint16_t xd, void** addr){
	*addr += sizeof(xd);
}

static inline memcpy_n(void *dst, void* src, int num, uint8_t *aux){

	char *srce = (char *)src;
	char *dest = (char *)dst;

	uint8_t i;
	for (i=0; i<num; i++)
		dest[i-4] == srce[i];

	*aux = (uint8_t)i*16;

}

uint32_t crc32(unsigned char *message, int n){

   int i, j;
   unsigned int byte, crc, mask;

   i = 0;
   crc = 0xFFFFFFFF;

   for(int i=0; i<n ; i++){
      byte = message[i];
      crc = crc ^ byte;
      for (j = 7; j >= 0; j--) {
         mask = -(crc & 1);
         crc = (crc >> 1) ^ (0xEDB88320 & mask);
      }
   }

   return ~crc;
}

static inline closefd(int fd1, void* alias_ptr){

	close(fd1);

	char *alias = alias_ptr;

	if(alias_ptr > SHRT_MAX && *alias == '@'){
		rename_fd(fd1);
	}

}

int px(int fd, uint8_t *c, void* ptr){

	void* fail;

	fail = memcpy(c, ptr, 1);
	if(fail)
		print_error(fd, &ptr);
	else
		c--;
	c++;

	fail = memcpy(c, ptr, 1);
	if(fail)
		print_error(fd, &ptr);
	else
		c--;
	c++;

	fail = memcpy(c, ptr, 1);
	if(fail)
		print_error(fd, &ptr);

	return 1;
}

static inline uint32_t mod_n(uint16_t i){
	return i*PH;
}

static inline checkfd(int fd){

	int16 aux = 0;

	if(fd < 1)
		return -1;
	else
		aux = -1;

	return cont-(aux-14);
}

void ech(int i, uint8_t *c, int fd){

	if(i==1 || i==2)
		dprintf(fd, " ");

	if(i<3)
		dprintf(fd, "%i", c[i]);
}

int halt(int signal){

	if(write(signal, &_HALT, 1) != 1)
		return 1;

	return 0;
}

void _custom_error (int a, void **b){

	*b = *b+1;
}

void last(){

}

#endif /* EKOPARTY1_H_ */
