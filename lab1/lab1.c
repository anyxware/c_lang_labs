//find number by remainders of division on 3, 5, 7.
#include <stdio.h>
int main(){
        printf("input n,m,k\n");
        int n; int m; int k;
        int x1;int x2;int x3;
        scanf("%d",&n);scanf("%d",&m);scanf("%d",&k);
        if(n < 3 && m < 5 && k < 7){
	for(int i = 0;i < 1000;i++){
		if((i - n) % 3 == 0 && (i - m) % 5 == 0 && (i - k) % 7 == 0){
			printf("%d",i);
			printf("\n");
}	
}

}
	}


