#include <pthread.h>
#include <semaphore.h>

int main()
{
	sem_t sem; //semaphore variable

  sem_init(&sem, 0, 4); //semaphore variable gets initialized, with 0 to indicate threads and not processes and the semaphore value, used on linux on macos we use sem_open
  &sem = sem_open("/name", NULL, NULL, 4); //First parameter is the name of the sem with a backslash, second parameter is to set flags like if already created do not create, third parameter is for other flags that we can set to null also, last parameter is the value given to the semaphore.  
  sem_wait(&sem); //Locks the semaphore, thus one of its values
  sem_post(&sem); //Unlocks one of the semaphore's values
  sem_destroy(&sem);
  sem_close(&sem); //Used on macos while destroy is used on linux
}
