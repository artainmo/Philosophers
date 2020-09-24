#include <semaphore.h>

int main()
{
	sem_unlink("/write");
	sem_unlink("/dead");
	sem_unlink("/forks");
	sem_unlink("/eat_max");
}
