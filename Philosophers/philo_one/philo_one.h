/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 12:06:54 by artainmo          #+#    #+#             */
/*   Updated: 2020/10/26 10:38:12 by artainmo         ###   ########.fr       */
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
extern int g_max_eat;

/*
**A chained list with mutex is used to identify the different forks around the
**table and make one fork accessible to only one t_philosopher at a time
*/

typedef	struct	s_forks
{
	int				number;
	pthread_mutex_t	*lock;
	struct s_forks	*head;
	struct s_forks	*next;
}				t_forks;

typedef	struct	s_params
{
	int				number_of_t_philosophers;
	long long int	time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_t_philosopher_must_eat;
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
	t_forks			*fork;
	t_params		*p;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
}				t_philosopher;

int				dies(t_philosopher *p, char *tim);
int				think(t_philosopher *p);
int				sleeps(t_philosopher *p);
int				eat(t_philosopher *p);
int				take_fork(t_philosopher *p);

t_philosopher	*init_philo(int argc, char **argv);
t_philosopher	*new_philo(t_philosopher *old_philo, int id);
t_params		*init_params(int argc, char **argv);

int				specific_mutex(t_philosopher *p, int action);

long long int	get_time();
void			free_philo(t_philosopher *p);
void			*error(char *str);
long long int	get_miliseconds(struct timeval t);
int				status_change(t_philosopher *p, char *message);
int				dead_message(t_philosopher *p, char *tim);

int				ft_atoi(const char *str);
char			*ft_strdup(const char *src);
int				ft_strlen(const char *str);
char			*ft_itoa(int n);
char			*ft_strjoin(char const *s1, char const *s2);

#endif
