#include "philo_three.h"

int dies(philosopher *p, char *tim)
{
  sem_wait(p->dead_lock);
  dead_message(p, tim);
  sem_post(p->dead_lock);
  return (1);
}

int think(philosopher *p)
{
  if (status_change(p, "\tis thinking\n") == 1)
    return (1);
  return (0);
}

int sleeps(philosopher *p)
{
  if (status_change(p, "\tis sleeping\n") == 1)
    return (1);
  usleep(p->p->time_to_sleep);
  return (0);
}


static int take_fork(philosopher *p)
{
  sem_wait(p->forks); //Locks one of the semaphore's values, if all semaphore values are locked the thread waits until one gets unlocked
  if (status_change(p, "\thas taken a fork\n") == 1)
    return (1);
  return (0);
}

static void leave_fork(philosopher *p)
{
  sem_post(p->forks); //Unlocks one of the semaphore's values
}

int eat(philosopher *p)
{
  take_fork(p);
  take_fork(p);
  if (status_change(p, "\tis eating\n") == 1)
    return (1);
  p->eating_counter++;
  p->is_eating = 1;
  usleep(p->p->time_to_eat);
  p->last_meal_time = get_time();
  p->is_eating = 0;
  leave_fork(p);
  leave_fork(p);
  return (0);
}
