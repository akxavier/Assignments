#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex;
int counter;

void* increment(void* arg)
{
	sem_wait(&mutex);
	
	printf("Entering T1...\n");

	for(int i = 0; i < 10000000; i++) 
		counter++;
	
	printf("Exiting T1...\n");

	sem_post(&mutex);
}

void* decrement(void* arg)
{
        sem_wait(&mutex);
	
	printf("Entering T2...\n");

        for(int i = 0; i < 10000000; i++) 
                counter--;
		
        printf("Exiting T2...\n");

	sem_post(&mutex);
}


int main()
{
	sem_init(&mutex, 0, 1);

	pthread_t t1,t2;
	pthread_create(&t1, NULL, increment, NULL);
	pthread_create(&t2, NULL, decrement, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	sem_destroy(&mutex);

	printf("Value of counter is %d\n", counter);
	return 0;
}

