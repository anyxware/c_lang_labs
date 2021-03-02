#include "lib_lab5.h"

int main(int argc, char const *argv[]){
	list* List = NULL;
	do{
		List = getList();
		if(List){
			shifter(List,-1);
			deleteList(List,1);
		}
	}while(List);
	return 0;
}