https://powcoder.com
代写代考加微信 powcoder
Assignment Project Exam Help
Add WeChat powcoder
https://powcoder.com
代写代考加微信 powcoder
Assignment Project Exam Help
Add WeChat powcoder
#ifndef _SEMAPHORE_H
#define _SEMAPHORE_H

#include <stdint.h>

/*
 * sem_t - Semaphore type
 *
 * A semaphore is a way to control access to a common resource by multiple
 * threads. Such resource has an internal count, meaning that it can only be
 * shared a certain number of times. When a thread successfully takes the
 * resource, the count is decreased. When the resource is not available,
 * following threads are blocked until the resource becomes available again.
 */
typedef struct semaphore *sem_t;

/*
 * sem_create - Create semaphore
 * @count: Semaphore count
 *
 * Allocate and initialize a semaphore of internal count @count.
 *
 * Return: Pointer to initialized semaphore. NULL in case of failure when
 * allocating the new semaphore.
 */
sem_t sem_create(size_t count);

/*
 * sem_destroy - Deallocate a semaphore
 * @sem: Semaphore to deallocate
 *
 * Deallocate semaphore @sem.
 *
 * Return: -1 if @sem is NULL, or 0 is @sem was successfully destroyed.
 */
int sem_destroy(sem_t sem);

/*
 * sem_down - Take a semaphore
 * @sem: Semaphore to take
 *
 * Take a resource from semaphore @sem.
 *
 * Taking an unavailable semaphore will cause the caller thread to be blocked
 * until the semaphore becomes available.
 *
 * Return: -1 if @sem is NULL. 0 if semaphore was successfully taken.
 */
int sem_down(sem_t sem);

/*
 * sem_up - Release a semaphore
 * @sem: Semaphore to release
 *
 * Release a resource to semaphore @sem.
 *
 * Releasing a resource if the semaphore was currently empty causes the first
 * thread in the waiting list to be unblocked.
 *
 * Return: -1 if @sem is NULL. 0 if semaphore was successfully released.
 */
int sem_up(sem_t sem);

#endif /* _SEMAPHORE_H */
