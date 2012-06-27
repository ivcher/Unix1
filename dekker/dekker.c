#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

static void* threadDo(void * arg);
static void unlock(int id);
static void lock(int id);


static int volatile turn = 0;
static int volatile flag[2] = {0};
#define MAX_ITERATION 10
int counter = 0;

int main()
{
	pthread_t thread[2];
	int id[2] = {1,2};
	int i = 0;	
	while(i < 2) 
	{
		if(pthread_create(&thread[i], NULL, threadDo,(void*) &id[i]))
		{
			perror("thread not created\n");
			exit(0);
		}
		i++;
	}
	pthread_join(thread[0],NULL);		
	pthread_join(thread[1],NULL);		
	
	return 0;	
}

static void *threadDo(void * arg)
{
	int id = *((int *)arg), i;
	for(i = 0; i < MAX_ITERATION; i++)
	{
		lock(id);
		++counter;
		printf("Thread %d counter = %d\n", id, counter);
		unlock(id);
	} 
}
static void lock (int id)
{
	int other = id ^ 1;
	flag[id] = 1;
	while(flag[other])
	{
		if( turn != id )
		{
			flag[id] = 0;
			while (turn != id);
			flag[id] = 1;
		}
	}
}

static void unlock(int id)
{
	turn = id ^ 1;
	flag[id] = 0;
}
