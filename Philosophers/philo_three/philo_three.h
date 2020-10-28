/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 16:26:54 by artainmo          #+#    #+#             */
/*   Updated: 2020/10/26 12:37:01 by artainmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>

# include <stdio.h>
# include <errno.h>

typedef struct	s_params
{
	int				number_of_t_philosophers;
	long long int	time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_t_philosopher_must_eat;
}				t_params;

typedef struct	s_philosopher
{
	int				id;
	sem_t			*forks;
	long long int	start_time;
	long long int	last_meal_time;
	int				is_eating;
	int				eating_counter;
	int				do_not_die;
	sem_t			*write_lock;
	int				*g_dead;
	sem_t			*dead_lock;
	sem_t			*eat_max;
	t_params		*p;
}				t_philosopher;

int				dies(t_philosopher *p, char *tim);
int				think(t_philosopher *p);
int				sleeps(t_philosopher *p);
int				eat(t_philosopher *p);

t_philosopher	*init_philo(int argc, char **argv);
t_philosopher	*new_philo(t_philosopher *old_philo, int id);
t_params		*init_params(int argc, char **argv);

long long int	get_time();
void			free_philo(t_philosopher *p);
void			error(char *str);
long long int	get_miliseconds(struct timeval t);
int				status_change(t_philosopher *p, char *message);
void			dead_message(t_philosopher *p, char *tim);

int				ft_atoi(const char *str);
int				ft_strlen(const char *str);
char			*ft_itoa(int n);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strdup(const char *src);

#endif
