#ifndef MYSTRING_H
#include <stdlib.h>
#define MYSTRING_H
typedef struct item item;
typedef struct list list;
list* getList();
void deleteList(list* List, int print);
void shifter(list* List, int shift);
void bench(int n, int m, int shift);
#endif
