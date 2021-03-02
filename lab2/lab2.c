//count converging series
#include <stdio.h>

double s(double a,double b,double c){
	double s = c/(a*b);
	return s;
}
int my_series(double a,double b,double c,int n,double x,double si){
	double q;
	for(int i = 1;i < n+1; ++i){
                a*=i;           //i!
                b*=n+i;         //(n+i)!
                c*=x*x/4;       //(x/2)^(2i+n)
                q = si;
		si += s(a,b,c); //sum
		if(si == q) break;
                printf("%.15lf\n",si);
        }

}

int main(){
	int n;double x;
	while(1){
	printf("n: "); scanf("%d",&n);
	printf("x: "); scanf("%lf",&x);
	double a = 1, b = n, c = 1;
	for(int i = 0; i < n; ++i) c *= x/2; //(x/2)^n
	double si = 1/n*c; //i = 0
	my_series(a,b,c,n,x,si);
	}
}

