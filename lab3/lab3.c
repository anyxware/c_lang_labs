//Search for different words with identical letters
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//#define strlen mystrlen
//#define memcpy mymemcpy
//#include "mystring.c"

int absolut_analog(char* word1,char* word2){
	int fl = 1;
	if(strlen(word1) == strlen(word2)){
		for(int l = 0;l < strlen(word1);l++){
			if(word1[l] != word2[l]){
				fl = 0;
				break;
			}
		}
	}else fl = 0;
	return fl;
}

int analog(char* word1,char* word2){
	int absfl = 1;
	int fl = 1;
	int d[26] = {0};
	for(int l = 0; l < strlen(word1); l++){
		d[(int)word1[l] - 97] += 1;
		d[(int)word2[l] - 97] -= 1;
		if(word1[l] != word2[l]) absfl = 0;
	}
	for(int l = 0; l < 26; l++) {
	    if(d[l]){
	      fl = 0;
	      break;
	    }
  	}
  	return fl + absfl;
  	/*
	if(fl && absfl) return 2;
  	else if(fl && !absfl) return 1;
  	else return 0;*/
}

char* get_str(){
	char buf[80] = {0};
	char* res = NULL;
	int len = 0;
	int n = 0;
	do{
		n = scanf("%80[^\n]",buf);
		if(n < 0){
			if(!res) return NULL;	
		} else if(n > 0){
			int chunk_len = strlen(buf);
			int str_len = len + chunk_len;
			res = realloc(res,str_len + 1);
			memcpy(res + len, buf, chunk_len);
			len = str_len;
		} else{
			scanf("%*c");
		}
	}while(n > 0);

	if(len > 0) res[len] = '\0';
	else res = calloc(1,sizeof(char));
	return res;
}

int changing(char* s, char** p, int m){
	int k = 1;
	for(int i = 1; i <= m; i++){
		if((s[i-1] == ' ' || s[i-1] == '\t')){
			s[i-1] = '\0';
			p[k++] = &s[i];
		}
	}
	return k;
}

int choosing(char** p,int* numbers, int k){
	for(int i = 0; i < k; i++){
		if(numbers[i]) 
			continue;
		char* word1;
		char* word2;
		word1 = p[i];
		int cucumber = 1;
		for(int j = i + 1; j < k; j++){
			if(numbers[j])
				continue;
			word2 = p[j];
			for(int y = j + 1;y < k;y++){
				if(absolut_analog(word2,p[y]))
					numbers[y] = 1;
			}
			if(strlen(word1) == strlen(word2)){
				int flag = analog(word1,word2);
				switch(flag){
					case 1: 
						if(cucumber){
							printf("%s ", word1);
							cucumber = 0;
						}
						printf("%s ", word2);
					case 2: numbers[j] = 1;
				}
			}
		}
		if(!cucumber) 
			printf("\n");
	}
	return 0;
}

int main(){
	printf("Input strings(only ASCII symbols)\n");
	char* s = NULL;
	do{
		s = get_str();
		clock_t t = clock();
		int numbers[20] = {0}, k = 1, m = 0, cucumber = 0, flag = 0;
		char* p[20] = {NULL};
		p[0] = s;
		if(s){
			m = strlen(s);
			k = changing(s,p,m);
			choosing(p,numbers,k);
			free(s);
		}
		printf("%.3f\n", (clock() - t)/1000.0);
	}while(s);
	return 0;
}
