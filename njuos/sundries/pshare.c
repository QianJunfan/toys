#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int data = 0;


void *writer(void *arg)
{
        printf("Thread A: Modifying 'data' value to 100\n");
        data = 100;
        return NULL;
}

void *reader(void *arg)
{
        sleep(1);
        printf("Thread B: Read value of 'data' is %d\n", data);
        return NULL;
}

int main(void)
{
        pthread_t t1, t2;

        printf("Init: data = %d\n", data);

        pthread_create(&t1, NULL, writer, NULL);
        pthread_create(&t2, NULL, reader, NULL);

        pthread_join(t1, NULL);
        pthread_join(t2, NULL);

        printf("Main: Finally, data = %d\n", data);


        return 0;
}
