/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 15:28:24 by artainmo          #+#    #+#             */
/*   Updated: 2020/10/25 15:30:42 by artainmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

long long int			get_miliseconds(struct timeval t)
{
	return (((long long int)t.tv_sec * (long long int)1000) + ((long long int)t.tv_usec / (long long int)1000));
}

long long int			get_time(void)
{
	struct	timeval current_time;

	gettimeofday(&current_time, 0);
	return (get_miliseconds(current_time));
}

static long long int	get_timestamp(philosopher *p)
{
	struct	timeval current_time;

	gettimeofday(&current_time, 0);
	return (get_miliseconds(current_time) - p->start_time);
}

static void				put_message(philosopher *p, char *message)
{
	char	*timestamp;
	char	*name;
	char	*line;
	char	*tmp;

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

int						status_change(philosopher *p, char *message)
{
	sem_wait(p->write_lock);
	if (g_dead == 1 ||
			(p->p->number_of_times_each_philosopher_must_eat != -1
			 && p->p->number_of_times_each_philosopher_must_eat * p->p->number_of_philosophers <= g_eating_counter))
	{
		sem_post(p->write_lock);
		return (1);
	}
	put_message(p, message);
	sem_post(p->write_lock);
	return (0);
}

int						dead_message(philosopher *p, char *tim)
{
	char	*timestamp;
	char	*name;
	char	*line;
	char	*tmp;

	sem_wait(p->write_lock);;
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
	sem_post(p->write_lock);
	return (0);
}

void					*error(char *str)
{
	write(1, str, ft_strlen(str));
	return (0);
}

void					free_philo(philosopher *p)
{
	sem_unlink("/write"); //If not unlinked even after program ends semaphore stays in memory causing problems (permission denied), when re-calling program, so always unlink it
	sem_unlink("/dead");
	sem_unlink("/forks");
	sem_close(p->write_lock);
	sem_close(p->dead_lock);
	sem_close(p->forks);
	free(p->p);
	free(p);
}
