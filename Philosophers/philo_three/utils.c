/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 16:27:07 by artainmo          #+#    #+#             */
/*   Updated: 2020/10/26 08:39:46 by artainmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

long long int			get_miliseconds(struct timeval t)
{
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

long long int			get_time(void)
{
	struct timeval current_time;

	gettimeofday(&current_time, 0);
	return (get_miliseconds(current_time));
}

static long long int	get_timestamp(t_philosopher *p)
{
	struct timeval current_time;

	gettimeofday(&current_time, 0);
	return (get_miliseconds(current_time) - p->start_time);
}

static void				put_message(t_philosopher *p, char *message)
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
	free(line);
	free(name);
	free(timestamp);
}

/*
**usleep -> The first process waits on time_to_die round to give all the time
**other processes could have had to eat last meal
**do_not_die = 1 -> Protection against philospher dying while waiting
*/

int						status_change(t_philosopher *p, char *message)
{
	sem_wait(p->write_lock);
	if (p->p->number_of_times_each_t_philosopher_must_eat == p->eating_counter)
	{
		sem_post(p->write_lock);
		sem_wait(p->eat_max);
		p->do_not_die = 1;
		usleep(p->p->time_to_die * 1000);
		sem_wait(p->write_lock);
		write(1, "number of times each philosopher must eat attained\n", 51);
		free_philo(p);
		kill(0, SIGKILL);
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
