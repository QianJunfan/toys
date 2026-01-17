/* Demonstrates how to utilize two threads for parallel computing. */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

struct task {
	int start;
	int end;
	long long result;
};

void *cal(void *arg)
{
	struct task *n = (struct task *)arg;
	n->result = 0;

	for (int i = n->start; i <= n->end; i++)
	       n->result += i;

	printf("[Worker] Finished calculating %d to %d\n", n->start, n->end);

	pthread_exit((void *)n);	
}

int main(void)
{
	pthread_t t1, t2;
	
	struct task task1 = {1, 5000, 0};
	struct task task2 = {5001, 10000, 0};

	void *status;

	pthread_create(&t1, NULL, cal, &task1);
	pthread_create(&t2, NULL, cal, &task2);

	pthread_join(t1, &status);
	struct task *res1 = (struct task *)status;

	pthread_join(t2, &status);
	struct task *res2 = (struct task *)status;

	long long sum = res1->result + res2->result;

	printf("[Main] Final total sum is %lld\n", sum);

	return 0;
}
