https://powcoder.com
代写代考加微信 powcoder
Assignment Project Exam Help
Add WeChat powcoder
https://powcoder.com
代写代考加微信 powcoder
Assignment Project Exam Help
Add WeChat powcoder
/*
 * Semaphore test
 *
 * Test the synchronization of two threads sharing two semaphores. They should
 * print all the numbers from 0 to 20 - 1 (by default), in order, one number per
 * thread at a time.
 */

#include <limits.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include <thread.h>
#include <sem.h>

#define MAXCOUNT 20

struct test3 {
	sem_t sem1;
	sem_t sem2;
	size_t x;
	size_t maxcount;
};

void* thread2(void* arg)
{
	struct test3 *t = (struct test3*)arg;

	while (t->x < t->maxcount) {
		printf("thread 2, x = %zu\n", t->x++);
		sem_up(t->sem1);
		sem_down(t->sem2);
	}

	return NULL;
}

void* thread1(void* arg)
{
	struct test3 *t = (struct test3*)arg;

	while (t->x < t->maxcount) {
		sem_down(t->sem1);
		printf("thread 1, x = %zu\n", t->x++);
		sem_up(t->sem2);
	}

	return NULL;
}

unsigned int get_argv(char *argv)
{
	long int ret = strtol(argv, NULL, 0);
	if (ret == LONG_MIN || ret == LONG_MAX) {
		perror("strtol");
		exit(1);
	}
	return ret;
}

int main(int argc, char **argv)
{
	struct test3 t;
	size_t maxcount = MAXCOUNT;
	pthread_t tid[2];

	if (argc > 1)
		maxcount = get_argv(argv[1]);

	t.maxcount = maxcount;
	t.x = 0;
	t.sem1 = sem_create(0);
	t.sem2 = sem_create(0);

	pthread_create(&tid[0], NULL, thread1, &t);
	pthread_create(&tid[1], NULL, thread2, &t);

	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);

	return 0;
}
