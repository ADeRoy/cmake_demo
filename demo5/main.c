#include<stdio.h>
#include<config.h>

#ifdef USE_MYCALC
#include"head.h"
#endif
int main()
{
	int a = 20;
	int b = 12;
	printf("a = %d,b = %d\n",a,b);
#ifdef USE_MYCALC
	printf("use my calc\n");
	printf("a + b = %d\n",add(a,b));
	printf("a - b = %d\n",subtract(a,b));
	printf("a * b = %d\n",multiply(a,b));
	printf("a / b = %lf\n",divide(a,b));
#else
	printf("not use my clac\n");
	printf("a + b = %d\n",a + b);
	printf("a - b = %d\n",a - b);
	printf("a * b = %d\n",a * b);
	printf("a / b = %d\n",a / b);
#endif
	return 0;
}
