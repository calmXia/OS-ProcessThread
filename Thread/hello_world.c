#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* thread(void* vargp);

int main() // The beginning of the code for the main thread
{
	/*
	 * The main thread declares a single local variable tid,
	 * which will be used to store the thread ID of the peer thread.
	 * */
	pthread_t tid;
	/*
	 * The main thread creates a new peer thread by calling the 
	 * pthread_create function.
	 * When the call to pthread_create returns, the main thread 
	 * and the newly created peer thread are running concurrently, 
	 * and tid contains the ID of the new thread.
	 * */
	pthread_create(&tid, NULL, thread, NULL);
	/*
	 * The main thread waits for the peer thread to terminate with
	 * the call to pthread_join.
	 * */
	pthread_join(tid, NULL);
	/*
	 * Terminates all threads (in this case, just the main thread) currently running in the process.
	 * */
	exit(0);
}

void* thread(void* vargp) /* Peer thread routine */
{
	printf("Hello, world!\n");

	/*
	 * Terminates itself(the peer thread) by executing the return statement
	 * */
	return NULL;
}
