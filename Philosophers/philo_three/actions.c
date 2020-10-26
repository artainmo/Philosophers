/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 16:22:27 by artainmo          #+#    #+#             */
/*   Updated: 2020/10/25 18:28:08 by artainmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int			dies(t_philosopher *p, char *tim)
{
	if (p->do_not_die == 1)
	{
		free(tim);
		return (1);
	}
	sem_wait(p->dead_lock);
	dead_message(p, tim);
	sem_post(p->dead_lock);
	return (1);
}

int			think(t_philosopher *p)
{
	if (status_change(p, "\tis thinking\n") == 1)
		return (1);
	return (0);
}

int			sleeps(t_philosopher *p)
{
	if (status_change(p, "\tis sleeping\n") == 1)
		return (1);
	usleep(p->p->time_to_sleep);
	return (0);
}

static int	take_fork(t_philosopher *p)
{
	sem_wait(p->forks);
	if (status_change(p, "\thas taken a fork\n") == 1)
		return (1);
	return (0);
}

int			eat(t_philosopher *p)
{
	take_fork(p);
	take_fork(p);
	if (status_change(p, "\tis eating\n") == 1)
		return (1);
	p->eating_counter++;
	p->is_eating = 1;
	usleep(p->p->time_to_eat);
	p->last_meal_time = get_time();
	p->is_eating = 0;
	sem_post(p->forks);
	sem_post(p->forks);
	return (0);
}
