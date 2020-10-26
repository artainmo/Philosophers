/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 15:28:24 by artainmo          #+#    #+#             */
/*   Updated: 2020/10/25 16:10:26 by artainmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

long long int			get_miliseconds(struct timeval t)
{
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

long long int			get_time(void)
{
	struct timeval	current_time;

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
	free(line);
	free(name);
	free(timestamp);
}

int						status_change(t_philosopher *p, char *message)
{
	int total_eat;

	total_eat = p->p->number_of_times_each_t_philosopher_must_eat *
				p->p->number_of_t_philosophers;
	sem_wait(p->write_lock);
	if (g_dead == 1 ||
			(p->p->number_of_times_each_t_philosopher_must_eat != -1
						&& total_eat <= g_eating_counter))
	{
		sem_post(p->write_lock);
		return (1);
	}
	put_message(p, message);
	sem_post(p->write_lock);
	return (0);
}
