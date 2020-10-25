/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 15:25:05 by artainmo          #+#    #+#             */
/*   Updated: 2020/10/25 15:28:10 by artainmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>

# include <stdio.h>
# include <errno.h>

extern int g_eating_counter;
extern int g_dead;

typedef struct	s_params
{
  int			number_of_philosophers;
  long long int	time_to_die;
  int			time_to_eat;
  int			time_to_sleep;
  int			number_of_times_each_philosopher_must_eat;
}				t_params;

typedef struct	s_philosopher
{
  int			id;
  sem_t			*forks;
  long long int	start_time;
  long long int	last_meal_time;
  int			is_eating;
  sem_t			*write_lock;
  sem_t			*dead_lock;
  params		*p;
}				t_philosopher;

int				dies(philosopher *p, char *tim);
int				think(philosopher *p);
int				sleeps(philosopher *p);
int				eat(philosopher *p);

philosopher		*init_philo(int argc, char **argv);
philosopher		*new_philo(philosopher *old_philo, int id);
params			*init_params(int argc, char **argv);

long long int	get_time();
void			free_philo(philosopher *p);
void			*error(char *str);
long long int	get_miliseconds(struct timeval t);
int				status_change(philosopher *p, char *message);
int				dead_message(philosopher *p, char *tim);

int				ft_atoi(const char *str);
int				ft_strlen(const char *str);
char			*ft_itoa(int n);
char			*ft_strjoin(char const *s1, char const *s2);

#endif
