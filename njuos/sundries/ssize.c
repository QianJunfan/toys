#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


void *func(void * arg)
{
        printf("Thread is running\n");

        return NULL;
}

int main(void)
{
        pthread_t t;
        pthread_attr_t attr;
        size_t size;

        pthread_attr_getstacksize(&attr, &size);

        printf("Default Stack Size: %ld Bytes\n", size);

        size = 16 * 1024 * 1024;

        pthread_attr_setstacksize(&attr, size);

        if (pthread_create(&t, &attr, func, NULL) != 0) {
                perror("Failed: pthread()");
                return 1;
        }

        pthread_attr_destroy(&attr);
        pthread_join(t, NULL);

        return 0;
}
