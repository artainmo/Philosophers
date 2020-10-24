#include "philo_three.h"

long long int get_miliseconds(struct timeval t)
{
  return (((long long int)t.tv_sec * (long long int)1000) + ((long long int)t.tv_usec / (long long int)1000));
}

long long int get_time()
{
  struct timeval current_time;

  gettimeofday(&current_time, 0);
  return (get_miliseconds(current_time));
}

static long long int get_timestamp(philosopher *p)
{
  struct timeval current_time;

  gettimeofday(&current_time, 0);
  return (get_miliseconds(current_time) - p->start_time);
}

static void put_message(philosopher *p, char *message)
{
  char *timestamp;
  char *name;
  char *line;
  char *tmp;

  name = ft_itoa(p->id);
  timestamp = ft_itoa((int)get_timestamp(p));
  line = ft_strjoin(timestamp, "\t");
  tmp = line;
  line = ft_strjoin(line, name);
  free(tmp);
  tmp = line;
  line = ft_strjoin(line, message);
  free(tmp);
  write(1, line, ft_strlen(line));
  free(name);
  free(timestamp);
}

int status_change(philosopher *p, char *message)
{
  sem_wait(p->write_lock);
  if (p->p->number_of_times_each_philosopher_must_eat == p->eating_counter)
  {
    sem_post(p->write_lock);
    sem_wait(p->eat_max); //This will block all processes that ate max, behalf the first one
    usleep(p->p->time_to_die * 1000); //The first process waits on time_to_die round to give all the time other processes could have had to eat last meal
    sem_wait(p->write_lock);
    write(1, "number of times each philosopher must eat attained\n", 52);
    free_philo(p);
    kill(0, SIGKILL); //And finally the process kills of all processes
    //-1 as pid value, causes all the processes in computer to finish and causes bugs... 0 causes main and child processes to finish
  }
  if (*p->g_dead == 1)
  {
    sem_post(p->write_lock);
    return (1);
  }
  put_message(p, message);
  sem_post(p->write_lock);
  return (0);
}

int dead_message(philosopher *p, char *tim)
{
  char *timestamp;
  char *name;
  char *line;
  char *tmp;

  sem_wait(p->write_lock);
  *p->g_dead = 1;
  name = ft_itoa(p->id);
  line = ft_strjoin(tim, "\t");
  tmp = line;
  line = ft_strjoin(line, name);
  free(tmp);
  tmp = line;
  line = ft_strjoin(line, "\tdied\n");
  free(tmp);
  write(1, line, ft_strlen(line));
  free(name);
  free(tim);
  free_philo(p);
  kill(0, SIGKILL);
  //-1 as pid value, causes all the processes in computer to finish and causes bugs... 0 causes main and child processes to finish
  return (0);
}

void *error(char *str)
{
  write(1, str, ft_strlen(str));
  return (0);
}

void free_philo(philosopher *p)
{
  sem_unlink("/write"); //If not unlinked even after program ends semaphore stays in memory causing problems (permission denied), when re-calling program, so always unlink it
  sem_unlink("/dead");
  sem_unlink("/forks");
  sem_unlink("/eat_max");
  sem_close(p->write_lock);
  sem_close(p->dead_lock);
  sem_close(p->forks);
  free(p->p);
  free(p);
}
