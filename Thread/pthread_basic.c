#include <stdio.h>
#include <pthread.h>

/*
 * A thread is a logical flow that runs in the context of a process.
 * Like processes, threads are scheduled automatically by the kernel
 * and are known to the kernel by an integer ID.
 *
 * Each thread has its own *thread context*, including **a unique
 * integer thread ID(TID), stack, stack pointer, program counter,
 * general-purpose registers, and condition codes**.
 *
 * All threads running in the context of a single process, and thus
 * they **share the entire contents of the process virtual address space
 * , including its code, data, heap, shared libraries, and open files**.
 * */

/*
 * This program consists of a main thread that creates two **peer threads**.
 * The main thread passes a unique ID to each peer thread, which uses the ID
 * to print a personalized message along with a count of the total number of
 * times that the thread routine has been invoked.
 *
 * 1. 线程内存模型：
 * （线程的）寄存器从不共享，而虚拟内存总是共享的。
 * 各个线程有各自独立的线程栈，这些栈被保存在虚拟地址空间的栈区域中，并且通常
 * (而不总是)是被相应的线程独立地访问的。“不总是”是因为不同线程栈是不对其他
 * 线程设防的。如果一个线程以某种方式得到了一个指向其他线程栈的指针，那么它就
 * 可以读写这个栈的任何部分。
 *
 * 例如：printf("[%d]: %s (cnt=%d)\n", myid, ptr[myid], ++cnt); 就展示了这一点
 * ，其中 peer thread 直接通过全局指针变量 ptr 间接引用主线程栈的内容。
 *
 * 2. 将变量映射到内存
 * 全局变量：只有一个实例， 任何线程都可以引用；
 * 本地自动变量：线程函数内部非static变量，每个线程创建一个实例；
 * 本地静态变量：线程函数内部的static变量，其对应的多个 peer thread共用一个实例
 * */

#define N 2

void *thread(void *vargp);
char **ptr;

int main()
{
	int i;
	pthread_t tid;
	char *msgs[N] = {
		"Hello from foo",
		"Hello from bar"
	};

	ptr = msgs;
	for (i = 0; i < N; i++)
		pthread_create(&tid, NULL, thread, (void *)i);

	pthread_exit(NULL);
}
	
void *thread(void *vargp)
{
	int myid = (int)vargp;
	static int cnt = 0;
	printf("[%d]: %s (cnt=%d)\n", myid, ptr[myid], ++cnt);
	return NULL;
}
