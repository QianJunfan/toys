#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *func(void *arg)
{
        int id = *(int*)arg;

        int val = 42;
        printf("Thread %d Addr: %p\n", id, (void *)&val);


        /* To prevent the thread from terminating prematurely
         * and its stack space being reclaimed or reused
         */
        sleep(2);

        return NULL;
}


int main(void)
{
        pthread_t a, b;
        int id_a = 1;
        int id_b = 2;

        pthread_create(&a, NULL, func, &id_a);
        pthread_create(&b, NULL, func, &id_b);

        pthread_join(a, NULL);
        pthread_join(b, NULL);

        return 0;
}
