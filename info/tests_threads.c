#include <pthread.h>
#include <stdio.h>

int g = 0;

void *start(void *start)
{
	printf("%d\n", g);
	g++;
	return (0);
}

int main()
{
	pthread_t id;
	int i = 0;

	while (i++ < 3)
	{
		pthread_create(&id, NULL, start, NULL);
		pthread_join(id, NULL); //If you do not use this, the global variable will not have the time to increment, before the next thread is created...
	}
	return (0);
}
