#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int q = 0;
int j = 0;

void *end = NULL;

void *start(void *arg)
{
	int *p = (int *)arg;
	while (*p <= 1000000) 
		(*p)++;
		
	end = arg;
	return NULL;
}

int main(void)
{

	pthread_t t1, t2;

	printf("game start!\n");
	printf("jiang: %p\n", &j);
	printf("qian: %p\n", &q);
	pthread_create(&t1, NULL, start, (void *)&q);
	pthread_create(&t2, NULL, start, (void *)&j);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);	
	printf("The loser is %s\n", end == &q ? "qian" : "yulan");
	return 0;
}
