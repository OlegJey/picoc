#include<stdio.h>


int foo(int b){
	b = 2;
	float d = 2.4;			
	return b;
}

void bar(){
	int a,b,c;
	a = 2;
	b = foo(2);
	c = a+b;
}
int main() {
	printf("Hello World\n"); //Code Parsed again and executed...HElloWorld Output line 7	
	int a = 3; 		
	int b = 2;
	a = a+b;
	printf("%d\n",a);
	b = foo(1);
	printf("%d\n",b);
	bar();
	return 0;
}
