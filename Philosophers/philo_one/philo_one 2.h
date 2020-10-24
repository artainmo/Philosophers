#ifndef PHILO_ONE_HPP
#define PHILO_ONE_HPP

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdio.h>

#define LOCK 1
#define UNLOCK 2

extern int g_eating_counter;
extern int g_dead;

typedef struct forks //A chained list with mutex is used to identify the different forks around the table and make one fork accessible to only one philosopher at a time
{
  int number;
  pthread_mutex_t *lock;
  struct forks *head;
  struct forks *next;
} forks;

typedef struct params
{
  int number_of_philosophers;
  long long int time_to_die;
  int time_to_eat;
  int time_to_sleep;
  int number_of_times_each_philosopher_must_eat;
} params;

typedef struct philosopher
{
  int id;
  long long int start_time; //Unsigned is not used, because in very rare cases negative numbers were generated, that created random values in unsigned form, was challenging to see problem and debug
  long long int last_meal_time;
  int is_eating; //Boolean so no-one dies while eating
  forks *fork;
  params *p;
  pthread_mutex_t *write_lock;
  pthread_mutex_t *dead_lock;
} philosopher;

  int dies(philosopher *p, char *tim);
  int think(philosopher *p);
  int sleeps(philosopher *p);
  int eat(philosopher *p);
  int take_fork(philosopher *p);

  philosopher *init_philo(int argc, char **argv);
  philosopher *new_philo(philosopher *old_philo, int id);
  params *init_params(int argc, char **argv);

  int specific_mutex(philosopher *p, int action);

  long long int get_time();
  void free_philo(philosopher *p);
  void *error(char *str);
  long long int get_miliseconds(struct timeval t);
  int status_change(philosopher *p, char *message);
  int dead_message(philosopher *p, char *tim);

  int			ft_atoi(const char *str);
  int ft_strlen(const char *str);
  char		*ft_itoa(int n);
  char		*ft_strjoin(char const *s1, char const *s2);

#endif
