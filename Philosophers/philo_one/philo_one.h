/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 12:06:54 by artainmo          #+#    #+#             */
/*   Updated: 2020/10/25 13:34:23 by artainmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>

# define LOCK 1
# define UNLOCK 2

extern int g_eating_counter;
extern int g_dead;
extern int g_error;

/*
**A chained list with mutex is used to identify the different forks around the
**table and make one fork accessible to only one philosopher at a time
*/

typedef	struct	s_forks
{
	int				number;
	pthread_mutex_t	*lock;
	struct forks	*head;
	struct forks	next;
}				t_forks;

typedef	struct	s_params
{
	int				number_of_philosophers;
	long long int	time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
}				t_params;

/*
**is_eating boolean, so no one dies while eating
*/
typedef struct	s_philosopher
{
	int				id;
	long long int	start_time;
	long long int	last_meal_time;
	int				is_eating;
	forks			*fork;
	params			*p;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
}				t_philosopher;

int				dies(philosopher *p, char *tim);
int				think(philosopher *p);
int				sleeps(philosopher *p);
int				eat(philosopher *p);
int				take_fork(philosopher *p);

philosopher		*init_philo(int argc, char **argv);
philosopher		*new_philo(philosopher *old_philo, int id);
params			*init_params(int argc, char **argv);

int				specific_mutex(philosopher *p, int action);

long long int	get_time();
void			free_philo(philosopher *p);
void			*error(char *str);
long long int	get_miliseconds(struct timeval t);
int				status_change(philosopher *p, char *message);
int				dead_message(philosopher *p, char *tim);

int				ft_atoi(const char *str);
char			*ft_strdup(const char *src);
int				ft_strlen(const char *str);
char			*ft_itoa(int n);
char			*ft_strjoin(char const *s1, char const *s2);

#endif
