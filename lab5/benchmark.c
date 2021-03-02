#include <stdio.h>
#include "lib_lab5.h"

int main(int argc, char const *argv[]){
	int n,m,shift,fl = 1;
	char answ;
	do{
		printf("\033[1;33mInput number of lines: \033[0m");
		scanf("%d", &n);
		printf("\033[1;33mInput line length: \033[0m");
		scanf("%d", &m);
		printf("\033[1;33mInput shift(0 <= shift < word_len): \033[0m");
		scanf("%d", &shift);
		bench(n,m,shift);
		printf("\033[1;31mDo it again?(y/n): \033[0m");
		do scanf("%c",&answ); while(answ == '\n');
		if(answ == 'n') fl = 0;
	}while(fl);
	return 0;
}