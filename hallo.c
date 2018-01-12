#include <stdio.h>

void test1()
{
	char *t = "Test";
}

void test2()
{
	char *t = "Test2";
	test1();
}

int foo(int b)
{
	b = 2;
	float d = 2.4;
	test2();
	return b;
}

void bar()
{
	int a, b, c;
	a = 2;
	b = foo(2);
	c = a + b;
}
int main()
{
	printf("Hello World\n"); //Code Parsed again and executed...HElloWorld Output line 7
	int a = 3;
	int b = 2;
	a = a + b;
	printf("%d\n", a);
	b = foo(1);
	printf("%d\n", b);
	bar();

	return 0;
}
