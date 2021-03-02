#include <stdio.h>
#include <time.h>
#include "lib_lab5.h"

typedef struct item{
	char data;
	struct item* next;	
}item;

typedef struct list{
	item* head;
	item* tail;
}list;

void deleteList(list* List, int print){
	item* pt = List->head;
	int fl = 1;
	while(fl){
		if(!pt->next) fl = 0;
		if(print) printf("\033[1;33m%c\033[0m", pt->data);
		item* tmp = pt;
		pt = pt->next;
		free(tmp);
	}
	if(print) printf("\n");
	free(List);
}

list* getList(){
	printf("Input your string\n");
	int fl = 0;
	list* List = (list*)calloc(1,sizeof(list));
	item* pt = (item*)malloc(sizeof(item));
	item* ptnew;
	item* tmp;
	item* lastpt = NULL;
	int lastfl = 0;
	char c = getchar();
	if(c == EOF){
		free(List);
		free(pt);
		return NULL;
	}
	while(c == '\n' || c == ' ' || c == '\t') c = getchar();
	while(c != '\n'){
		pt->data = c;
		pt->next = (item*)malloc(sizeof(item));
		if(lastfl){
			lastpt = List->head;
			lastfl = 0;
		}
		if(!List->head){
			List->head = pt;
			lastfl = 1;
		}
		c = getchar();
		if(fl){
			while(c == ' ' || c == '\t') c = getchar();
			fl = 0;
		}
		if(c == '\t' || c == ' '){
			fl = 1;
			c = ' ';
		}
		tmp = pt->next;
		c == '\n' ? (pt->next = NULL) : (pt = pt->next);
		if(c != '\n' && lastpt) lastpt = lastpt->next;

	}
	free(tmp);
	if(pt->data == ' '){
		free(pt);
		lastpt->next = NULL;
	}
	return List;
}

void shifter(list* List, int shift){
	item* pt = List->head;
	item* prev = List->head;
	item* tmp1 = NULL;
	item* tmp2 = NULL;
	item* first = NULL;
	char c = ' ';
	int n = 0, k = 1, sign = 0, firstt = 1;
	if(shift < 0){
		printf("Input direction(l/r): ");
		c = getchar();
		while(c != 'l' && c != 'r'){
			printf("\033[1;31mIncorrect answer\033[0m\n");
			getchar();
			c = getchar();
		}
		if(c == 'l') sign = 1;
		printf("Input shift: ");
		scanf("%d",&n);
		getchar();
	}
	else 
		n = shift;
	while(1){
		first = pt;
		while(pt->next && pt->next->data != ' '){
			k++;
			pt = pt->next;
		}
		tmp1 = pt->next;
		pt->next = first;
		shift = (sign*n+(!sign)*(k-n%k))%k;
		for(int i = 0; i < shift; i++){
			pt = pt->next;
		}
		tmp2 = pt->next;
		pt->next = tmp1;
		if(firstt){
			List->head = tmp2;
			firstt = 0;
		}else prev->next = tmp2;
		prev = tmp1;
		if(prev) pt = prev->next;
		else break;
		k = 1;
	}
}

void bench(int n, int m, int shift){
	clock_t all_t;
	clock_t t;
	srand(time(NULL));
	for(int i = 0; i < n; i++){
		list* List = (list*)calloc(1,sizeof(list));
		item* pt = (item*)malloc(sizeof(item));
		item* tmp = NULL;
		t = clock();
		for(int j = 0; j < m; j++){
			((j+1)%11) ? pt->data = (char)(100 + rand()%10) : (pt->data = ' '); 
			pt->next = malloc(sizeof(item));
			if(!List->head)
				List->head = pt;
			tmp = pt->next;
			j+1 >= m ? (pt->next = NULL) : (pt = pt->next);
		}
		all_t += clock() - t;
		free(tmp);
		

		pt = List->head;
		int fl = 1;
		while(fl){
			if(!pt->next) fl = 0;
			printf("\033[1;33m%c\033[0m", pt->data);
			item* tmp = pt;
			pt = pt->next;
		}
		printf("\n");

		shifter(List,shift);

		pt = List->head;
		fl = 1;
		while(fl){
			if(!pt->next) fl = 0;
			printf("\033[1;33m%c\033[0m", pt->data);
			item* tmp = pt;
			pt = pt->next;
		}
		printf("\n");
		//deleteList(List,1);
	}
	printf("Average time: %0.3f\n", all_t/1000.0/n);
}