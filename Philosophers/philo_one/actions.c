/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 11:08:31 by artainmo          #+#    #+#             */
/*   Updated: 2020/10/25 11:10:18 by artainmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	dies(t_philosopher *p, char *tim)
{
	pthread_mutex_lock(p->dead_lock);
	if (g_dead == 1 || g_max_eat == 1)
	{
		pthread_mutex_unlock(p->dead_lock);
		free(tim);
		return (1);
	}
	g_dead = 1;
	dead_message(p, tim);
	pthread_mutex_unlock(p->dead_lock);
	return (1);
}

int	think(t_philosopher *p)
{
	if (status_change(p, "\tis thinking\n") == 1)
		return (1);
	return (0);
}

int	sleeps(t_philosopher *p)
{
	if (status_change(p, "\tis sleeping\n") == 1)
		return (1);
	usleep(p->p->time_to_sleep);
	return (0);
}

int	eat(t_philosopher *p)
{
	if (specific_mutex(p, LOCK) == 1)
		return (1);
	if (status_change(p, "\tis eating\n") == 1)
		return (1);
	g_eating_counter++;
	p->is_eating = 1;
	usleep(p->p->time_to_eat);
	p->last_meal_time = get_time();
	p->is_eating = 0;
	if (specific_mutex(p, UNLOCK) == 1)
		return (1);
	return (0);
}

int	take_fork(t_philosopher *p)
{
	if (status_change(p, "\thas taken a fork\n") == 1)
		return (1);
	return (0);
}
