/* In multithreading, relying solely on 'locks' is not enough.
 *
 * If a consumer thread finds the basket empty. It cannnot just keep staring at
 * it in an infinite loop (which wastes too much CPU time);
 * instead, it should go to sleep.
 * When the producer adds something, it then wakes the consumer up.
 *
 * To implement this type of 'communication', we need to use a condition 
 * variable.
 */
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int inventory;
pthread_mutex_t lock;
pthread_cond_t has_food;

void *producer(void *arg)
{
	for (int i = 0; i < 5; i++) {
		pthread_mutex_lock(&lock);
		
		inventory++;

		printf("[Producer] Item added. Current inventory: %d\n", 
				inventory);

		pthread_cond_signal(&has_food);
		pthread_mutex_unlock(&lock);
		
		sleep(1);
	}

	return NULL;
}


void *consumer(void *arg)
{
	for (int i = 0; i < 5; i++) {
		pthread_mutex_lock(&lock);

		while (inventory == 0) {
			printf("[Consumer] Inventory empty. "
				"Waiting for stock...\n");

			pthread_cond_wait(&has_food, &lock);
		}
		
		inventory--;
		printf("[Consumer] Item taken. "
			"Current inventory: %d\n", inventory);

		pthread_mutex_unlock(&lock);

		sleep(2);
	}

	return NULL;
}

int main(void)
{
	pthread_t p_tid, c_tid;

	pthread_mutex_init(&lock, NULL);
	pthread_cond_init(&has_food, NULL);

	pthread_create(&p_tid, NULL, producer, NULL);
	pthread_create(&c_tid, NULL, consumer, NULL);

	pthread_join(p_tid, NULL);
	pthread_join(c_tid, NULL);

	pthread_mutex_destroy(&lock);
	pthread_cond_destroy(&has_food);

	printf("[Main] Simulation finished.\n");
	
	return 0;
}
