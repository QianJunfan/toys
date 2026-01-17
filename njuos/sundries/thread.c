/* My first multi-threading example */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>


/* Arguments and return values must be of the void * type.
 * This is a requirement of the pthread lib.
 */
void *func(void *arg)
{
	char *message = (char *)arg;
	for (int i = 0; i < 5; i++) {
		printf("Child Thread: %s (%d)\n", message, i + 1);
	}
	return NULL;
}

int main(void)
{
	pthread_t p;
	char *msg = "Hello from thread!";

	if (pthread_create(&p, NULL, func, (void *)msg)) {
		printf("ERR: Thread creation failed!\n");
		return 1;
	}

	for (int i = 0; i < 20; i++)
		printf("Main thread is running... (%d)\n", i + 1);
	
	/* The main thread blocks here to await the completion of 'p'.
	 * Without this synchronization, the process will exit immediately
	 * upon the main thread's termination,
	 * which may result in the premature destruction of the child thread.
	 */

	pthread_join(p, NULL);
	
	printf("Done: All threads finished.\n");
		
	return 0;
}
