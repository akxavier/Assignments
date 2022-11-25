#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define N 5
#define THINKING 2
#define HUNGRY 1
#define EATING 0
#define LEFT (phnum + 4) % N
#define RIGHT (phnum + 1) % N

int state[N];
int phil[N] = { 0, 1, 2, 3, 4 };
int forks[N] = {0, 0, 0, 0, 0};
int hold[N] = {0, 0, 0, 0, 0};

sem_t mutex;
sem_t S[N];

void Take_fork(int i)
{

	state[i] = HUNGRY;

	printf("Philosopher %d is Hungry\n", i);

	int left = i;
	int right = (i + 1) % N;

	while(forks[left] != 0)
		;
	forks[left] = 1;
	hold[i]++;

	printf("Philosopher %d picks up Fork %d\n", i, left);

	sleep(2);

	while(forks[right] != 0)
		;
	forks[right] = 1;
	hold[i]++;

	printf("Philosopher %d picks up Fork %d\n", i, right);

	state[i] = EATING;

	printf("Philosopher %d starts Eating\n", i);

	sleep(1);
}

void Put_fork(int i)
{
	state[i] = THINKING;

	int left = i;
	int right = (i + 1) % N;

	forks[left] = forks[right] = 0;
	hold[i] = 0;

	printf("Philosopher %d puts down Fork %d and Fork %d\n", i, left, right);
	printf("Philosopher %d starts Thinking\n", i);

}

void* Philosopher(void* num)
{

	while (1) {

		int* i = num;

		sleep(1);

		Take_fork(*i);

		sleep(0);

		Put_fork(*i);
	}
}

void* Deadlock_detect(void* arg) {
	int flag, i;

	while(1) {
		flag = 1;

		for(i = 0; i < N; i++) {
			if(forks[i] == 0) {
				flag = 0;
				break;
			}
		}

		if(flag == 0)
			continue;

		for(i = 0; i < N; i++) {
			if(hold[i] == 0) {
				flag = 0;
				break;
			}
		}

		if(flag == 0)
			continue;

		printf("DEADLOCK DETECTED!\nInitiating Recovery...\n");
		//exit(0);

		forks[1] = 0;
		hold[1] = 0;
		printf("Philosopher 1 puts down Fork 1\n");
	}
}



void Deadlock()
{

	int i;
	pthread_t thread_id[N];
	pthread_t detect;

	pthread_create(&detect, NULL, Deadlock_detect, NULL);

	for (i = 0; i < N; i++) {

		pthread_create(&thread_id[i], NULL, Philosopher, &phil[i]);

		printf("Philosopher %d is thinking\n", i + 1);
	}

	pthread_join(detect, NULL);

	for (i = 0; i < N; i++)
		pthread_join(thread_id[i], NULL);
}

void test(int phnum)
{
	if (state[phnum] == HUNGRY
		&& state[LEFT] != EATING
		&& state[RIGHT] != EATING) {

		state[phnum] = EATING;

		sleep(2);

		printf("Philosopher %d takes fork %d and %d\n",
					phnum + 1, LEFT + 1, phnum + 1);

		printf("Philosopher %d is Eating\n", phnum + 1);

		sem_post(&S[phnum]);
	}
}

void take_fork(int phnum)
{

	sem_wait(&mutex);

	state[phnum] = HUNGRY;

	printf("Philosopher %d is Hungry\n", phnum + 1);

	test(phnum);

	sem_post(&mutex);

	sem_wait(&S[phnum]);

	sleep(1);
}

void put_fork(int phnum)
{

	sem_wait(&mutex);

	state[phnum] = THINKING;

	printf("Philosopher %d putting fork %d and %d down\n",
		phnum + 1, LEFT + 1, phnum + 1);
	printf("Philosopher %d is thinking\n", phnum + 1);

	test(LEFT);
	test(RIGHT);

	sem_post(&mutex);
}

void* philosopher(void* num)
{

	while (1) {

		int* i = num;

		sleep(1);

		take_fork(*i);

		sleep(0);

		put_fork(*i);
	}
}

void Deadlock_Free()
{

	int i;
	pthread_t thread_id[N];

	sem_init(&mutex, 0, 1);

	for (i = 0; i < N; i++)

		sem_init(&S[i], 0, 0);

	for (i = 0; i < N; i++) {

		pthread_create(&thread_id[i], NULL,
					philosopher, &phil[i]);

		printf("Philosopher %d is thinking\n", i + 1);
	}

	for (i = 0; i < N; i++)

		pthread_join(thread_id[i], NULL);
}

int main() {
	int n;
	printf("----------------------------DINING PHILOSOPHERS PROBLEM--------------------------\n");
	printf("1. Deadlock-prone situation with Recovery\n");
	printf("2. Deadlock-free situation\n");
	printf("Enter 1 or 2: ");
	
	scanf("%d", &n);
	
	switch(n) {
	case 1:	Deadlock();
				break;
	case 2: Deadlock_Free();
				break;
	default:	exit(0);
	}
	
}

