https://powcoder.com
代写代考加微信 powcoder
Assignment Project Exam Help
Add WeChat powcoder
https://powcoder.com
代写代考加微信 powcoder
Assignment Project Exam Help
Add WeChat powcoder
#ifndef _THREAD_H
#define _THREAD_H

#include <pthread.h>

/*
 * thread_block - Block thread
 *
 * By calling this function the current thread becomes blocked. It can only be
 * unblocked by another thread calling `thread_unblock()`.
 *
 * Return: -1 in case of failure, 0 otherwise
 */
int thread_block(void);

/*
 * thread_unblock - Unblock thread
 * @tid: Thread ID
 *
 * Unblock thread @tid and make it ready for scheduling.
 *
 * Return: -1 if @tid does not correspond to a currently blocked thread. 0 if
 * thread @tid was successfully unblocked.
 */
int thread_unblock(pthread_t tid);

/*
 * enter_critical_section - Enter critical section
 *
 * Call this function when entering a critical section in order to ensure mutual
 * exclusion with other threads.
 */
void enter_critical_section(void);

/*
 * exit_critical_section - Exit critical section
 *
 * Call this function when leaving a critical section in order to allow another
 * thread who was waiting to enter the same critical section to enter.
 */
void exit_critical_section(void);

#endif /* _THREAD_H */
