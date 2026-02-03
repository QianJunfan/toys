#include <stdio.h>

void prt_hello(void)
{
	printf("hello\n");
}

int main(void)
{
	printf("head: %p\n", prt_hello);
	return 0;
}



