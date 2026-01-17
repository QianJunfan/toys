/* I tried out detached threads. */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

/* Detached Mode:
 *
 * No More Waiting: 
 *   The main thread does not need to (and cannnot) call pthread_join to wait 
 *   for it.
 *
 * Automatic Resource Reclamation:
 *   The moment the thread finishes execution, the operating system 
 *   automatically reclaims all the resources it occupied
 *   (stack memory, descriptors, etc.).
 *
 * Independent Execution:
 *   It runs in the background until the task is complete.
 *
 * */

void *work(void *arg)
{
	printf("Child: I am running independently. \n");
	
	sleep(2);

	printf("Child: I am done and exiting.\n");
}


int main(void)
{
	pthread_t tid;
	
	pthread_create(&tid, NULL, work, NULL);
	pthread_detach(tid);

	printf("Main: I detached the child thread.\n");
	
	sleep(3);

	printf("Main: I am done and exiting...\n");

	return 0;
}
