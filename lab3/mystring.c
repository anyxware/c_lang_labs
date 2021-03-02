#include "mystring.h"

int mystrlen(char* word){
	int z = 0;
	while(word[z] != '\0')
		z++;
	return z;
}

int mymemcpy(char* ptr, char* buf, int buflen){
	for(int i = 0; i < buflen; i++)
		ptr[i] = buf[i];
	return 0;
}
