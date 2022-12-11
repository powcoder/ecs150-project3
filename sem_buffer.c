https://powcoder.com
代写代考加微信 powcoder
Assignment Project Exam Help
Add WeChat powcoder
https://powcoder.com
代写代考加微信 powcoder
Assignment Project Exam Help
Add WeChat powcoder
/*
 * Producer/consumer test
 *
 * A producer produces x values in a shared buffer, while a consume consumes y
 * of these values. x and y are always less than the size of the buffer but can
 * be different. The synchronization is managed through two semaphores.
 */

#include <limits.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include <thread.h>
#include <sem.h>

#define BUFFER_SIZE	16
#define MAXCOUNT	1000

struct test4 {
	sem_t empty;
	sem_t full;
	size_t size, head, tail, maxcount;
	unsigned int buffer[BUFFER_SIZE];
};

#define clamp(x, y) (((x) <= (y)) ? (x) : (y))

void* consumer(void* arg)
{
	struct test4 *t = (struct test4*)arg;
	size_t out = 0;

	while (out < t->maxcount - 1) {
		size_t i, n = random() % BUFFER_SIZE + 1;

		n = clamp(n, t->maxcount - out - 1);
		printf("Consumer wants to get %zu items out of buffer...\n", n);
		for (i = 0; i < n; i++) {
			sem_down(t->empty);
			out = t->buffer[t->tail];
			printf("Consumer is taking %zu out of buffer\n", out);
			t->tail = (t->tail + 1) % BUFFER_SIZE;
			t->size--;
			sem_up(t->full);
		}
	}

	return NULL;
}

void* producer(void* arg)
{
	struct test4 *t = (struct test4*)arg;
	size_t count = 0;

	while (count < t->maxcount) {
		size_t i, n = random() % BUFFER_SIZE + 1;
		n = clamp(n, t->maxcount - count + 1);

		printf("Producer wants to put %zu items into buffer...\n", n);
		for (i = 0; i < n; i++) {
			sem_down(t->full);
			printf("Producer is putting %zu into buffer\n", count);
			t->buffer[t->head] = count++;
			t->head = (t->head + 1) % BUFFER_SIZE;
			t->size++;
			sem_up(t->empty);
		}
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
	struct test4 t;
	unsigned int maxcount = MAXCOUNT;
	unsigned int randseed = 1;
	pthread_t tid[2];

	if (argc > 1)
		maxcount = get_argv(argv[1]);
	if (argc > 2)
		randseed = get_argv(argv[2]);
	srandom(randseed);

	t.size = t.head = t.tail = 0;
	t.maxcount = maxcount;

	t.empty = sem_create(0);
	t.full = sem_create(BUFFER_SIZE);

	pthread_create(&tid[0], NULL, producer, &t);
	pthread_create(&tid[1], NULL, consumer, &t);

	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);

	return 0;
}
