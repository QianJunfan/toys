/* A demonstration of two threads competing to modify a global variavle
 * simultaneously, using a Mutex to ensure an accurate result.
 */

#include <stdio.h>
#include <pthread.h>

int counter = 0;
int _counter = 0;

pthread_mutex_t lock;

void *task(void *arg)
{
	for (int i = 0; i < 100000; i++) {
		pthread_mutex_lock(&lock);

		counter++;

		pthread_mutex_unlock(&lock);
	}
	return NULL;
}


void *_task(void *arg)
{
	for (int i = 0; i < 100000; i++)
		_counter++;
	return NULL;
}



int main(void)
{
	pthread_t t1, t2, _t1, _t2;

	pthread_mutex_init(&lock, NULL);

	pthread_create(&t1, NULL, task, NULL);
	pthread_create(&t2, NULL, task, NULL);
	pthread_create(&_t1, NULL, _task, NULL);
	pthread_create(&_t2, NULL, _task, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(_t1, NULL);
	pthread_join(_t2, NULL);

	printf("Final Counter (mutex) : %d\n", counter);
	printf("Final Counter (no mutex): %d\n", _counter);

	printf("Expected val: 200000\n");

	pthread_mutex_destroy(&lock);

	return 0;
}
