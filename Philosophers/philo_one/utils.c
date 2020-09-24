#include "philo_one.h"

long long int get_miliseconds(struct timeval t) //seconds to milisecinds and microseconds to miliseconds
{
  return (((long long int)t.tv_sec * (long long int)1000) + ((long long int)t.tv_usec / (long long int)1000));
}

long long int get_time()
{
  struct timeval current_time;

  gettimeofday(&current_time, 0); //First parameter is structure that contains seconds since epoch and microseconds of last second
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
  pthread_mutex_lock(p->write_lock);
  if (g_dead == 1 ||
        (p->p->number_of_times_each_philosopher_must_eat != -1
                && p->p->number_of_times_each_philosopher_must_eat * p->p->number_of_philosophers <= g_eating_counter))
  {
    pthread_mutex_unlock(p->write_lock);
    return (1);
  }
  put_message(p, message);
  pthread_mutex_unlock(p->write_lock);
  return (0);
}

int dead_message(philosopher *p, char *tim)
{
  char *timestamp;
  char *name;
  char *line;
  char *tmp;

  pthread_mutex_lock(p->write_lock);
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
  pthread_mutex_unlock(p->write_lock);
  return (0);
}

void *error(char *str)
{
  write(1, str, ft_strlen(str));
  return (0);
}

void free_philo(philosopher *p)
{
  forks *tmp;

  free(p->p);
  while (p->fork != 0)
  {
    free(p->fork->lock);
    tmp = p->fork->next;
    free(p->fork);
    p->fork = tmp;
  }
  free(p->write_lock);
  free(p->dead_lock);
  free(p);
}
