#include "philo_one.h"

//threads share heap memory and static memory, thus memory allocated and global variables can be used interchangebly between threads
//threads only last the scope of their starting function

//Each time you execute code with same parameters you will have slightly different result which is normal and due to how fast each separate thread goes based on free memory at that time
//Writes not in order of time, normal because multiple threads with different times are waiting to get the mutex to be able to write

//We use mutex for access to the forks, but also for access to write (no interwined text), and when someone dies

//Verify rapid death ./philo_one 6 1000 2000 2000 5
//Infinity ./philo_one 3 8000 2000 2000
//verify eat count feature ./philo_one 7 8000 3000 3000 1
//verify eat count feature ./philo_one 7 8000 3000 3000 0
//verify eat count feature ./philo_one 2 8000 3000 3000 5

int g_dead = 0; //Initialize the global variables
int eat_count = 0;
int g_eating_counter = 0; //Counts how may times gets eaten
//Global variables are used to stop all threads when necessay


static void *dead_check(void *arg) //Second thread for each philosopher to constantly check if one is dying or eating_count is attained
{
  philosopher *p;
  long long int current_time; //Unsigned is not used, because in very rare cases negative numbers were generated, that created random values in unsigned form, was challenging to see problem and debug
  long long int since_last_meal;

  p = (philosopher *)arg;
  p->is_eating = 0;
  while (1)
  {
    current_time = get_time();
    since_last_meal = current_time - p->last_meal_time;
    if (p->p->time_to_die <= since_last_meal && !p->is_eating)
    {
      dies(p, ft_itoa(current_time - p->start_time));
      break ;
    }
    if (p->p->number_of_times_each_philosopher_must_eat != -1
            && p->p->number_of_times_each_philosopher_must_eat * p->p->number_of_philosophers <= g_eating_counter)
    {
      pthread_mutex_lock(p->write_lock);
      if (eat_count == 0)
        write(1, "number of times each philosopher must eat attained\n", 52);
      eat_count = 1;
      pthread_mutex_unlock(p->write_lock);
      break ;
    }
  }
  return (0);
}

static void *philo_start(void *arg)
{
  philosopher *p;
  pthread_t id;

  p = (philosopher *)arg;
  p->start_time = get_time();
  p->last_meal_time = get_time();
  if (pthread_create(&id , NULL, dead_check, p))
  {
    error("Creation of thread failed\n");
    return (0);
  }
  while (1)
  {
    if (eat(p) == 1)
      break ;
    if (sleeps(p) == 1)
      break ;
    if (think(p) == 1)
        break ;
  }
  specific_mutex(p, UNLOCK);
  return (0);
}

static int create_philosophers(philosopher *p)
{
  philosopher *new;
  pthread_t id;
  int i;

  i = 1;
  while (i <= p->p->number_of_philosophers)
  {
    new = new_philo(p, i);
    if (pthread_create(&id, NULL, philo_start, new) != 0)
    {
      error("Creation of thread failed\n");
      return (0);
    }
    usleep(50); //If you make them spawn too quickly they can be stuck with one fork, unable to get the second fork and never eat and die
    i++;
  }
  pthread_join(id, NULL); //Before freeing the main philosopher class, the other classes partly point on, wait the threads to terminate
  free_philo(p);
  return (1);
}


int main(int argc, char **argv)
{
  philosopher *p;

  if (argc != 5 && argc != 6)
  {
    error("Error in program arguments\n");
    return (1);
  }
  if ((p = init_philo(argc, argv)) == 0)
    return (1);
  if (p->p->number_of_philosophers < 2)
  {
    error("Not enough philosophers\n");
    return (1);
  }
  if (create_philosophers(p) == 0)
    return (1);
}
