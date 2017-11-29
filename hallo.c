#include<stdio.h>
int foo(int b){
	b = 2;
	return b;
}
int main() {
	printf("Hello World\n"); //Code Parsed again and executed...HElloWorldOutput line 7	
	int a = 3; 		
	int b = 2;
	a = a+b;
	printf("%d\n",a);
	b = foo(1);
	printf("%d\n",b);
	return 0;
}
