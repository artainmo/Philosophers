#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <errno.h>

int main()
{
	int *variable;
	variable = malloc(sizeof(int));
	*variable = 0;
	pid_t pid;
	sem_t *id;
	
	//sem_unlink("/id");
	//return (0);
	sem_wait(id);
	id = sem_open("/id", O_CREAT, 644, 1);
	pid = fork();
	if (!pid)
	{
		sem_wait(id);
		sem_unlink("/id");
		sem_close(id);
		*variable += 1;
		exit(0);
	}
	else
	{
		usleep(1000);
		printf("go\n");	
		while(1)
		{
			if (sem_wait(id) == -1)
			{
				printf("yes\n");
				break ;
			}
		}
	}
	printf("END\n");
	sem_unlink("/id");
	printf("%d\n", *variable);
	return (0);
}
