https://powcoder.com
代写代考加微信 powcoder
Assignment Project Exam Help
Add WeChat powcoder
https://powcoder.com
代写代考加微信 powcoder
Assignment Project Exam Help
Add WeChat powcoder
/*
 * Sieve test for finding prime numbers
 *
 * A producer thread (source) creates numbers and inserts them into a pipeline,
 * a consumer thread (sink) gets prime numbers from the end of the pipeline. The
 * pipeline consists of filtering thread, added dynamically each time a new
 * prime number is found and which filters out subsequent numbers that are
 * multiples of that prime.
 */

#include <limits.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include <thread.h>
#include <sem.h>

#define MAXPRIME 1000

typedef struct channel {
	int value;
	sem_t produce;
	sem_t consume;
} channel_t;

typedef struct filter {
	channel_t* left;
	channel_t* right;
	unsigned int prime;
	pthread_t tid;
	struct filter *next;
} filter_t;


unsigned int max = MAXPRIME;

/* Producer thread: produces all numbers, from 2 to max */
void* source(void *arg)
{
	channel_t *c = (channel_t*) arg;
	size_t i;

	for (i = 2; i <= max; i++) {
		c->value = i;
		sem_up(c->consume);
		sem_down(c->produce);
	}

	/* mark completion */
	c->value = -1;
	sem_up(c->consume);

	return NULL;
}

/* Filter thread */
void* filter(void *arg)
{
	filter_t *f = (filter_t*) arg;
	int value;

	for (;;) {
		sem_down(f->left->consume);
		value = f->left->value;
		sem_up(f->left->produce);
		if ((value == -1) || (value % f->prime != 0)) {
			f->right->value = value;
			sem_up(f->right->consume);
			sem_down(f->right->produce);
		}
		if (value == -1)
			break;
	}

	return NULL;
}

/* Consumer thread */
void* sink(void *arg)
{
	channel_t *p = (channel_t*) malloc(sizeof(channel_t));
	int value;
	pthread_t tid;
	filter_t *f_head = NULL;

	p->produce = sem_create(0);
	p->consume = sem_create(0);

	pthread_create(&tid, NULL, source, p);

	for (;;) {
		filter_t *f;

		sem_down(p->consume);
		value = p->value;
		sem_up(p->produce);

		if (value == -1)
			break;

		printf("%d is prime.\n", value);

		f = (filter_t*) malloc(sizeof(filter_t));
		f->left = p;
		f->prime = value;
		f->next = NULL;

		p = (channel_t*) malloc(sizeof(channel_t));
		p->produce = sem_create(0);
		p->consume = sem_create(0);

		f->right = p;

		pthread_create(&f->tid, NULL, filter, f);

		if (f_head)
			f->next = f_head;
		f_head = f;
	}

	pthread_join(tid, NULL);
	while (f_head) {
		filter_t *old = f_head;
		pthread_join(f_head->tid, NULL);
		f_head = f_head->next;
		free(old);
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
	pthread_t tid;

	if (argc > 1)
		max = get_argv(argv[1]);

	pthread_create(&tid, NULL, sink, NULL);
	pthread_join(tid, NULL);

	return 0;
}
