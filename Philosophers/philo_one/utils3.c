/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 12:25:31 by artainmo          #+#    #+#             */
/*   Updated: 2020/10/26 10:52:04 by artainmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int				lock_unlock(t_forks *it, t_philosopher *p, int action)
{
	if (action == LOCK)
	{
		pthread_mutex_lock(it->lock);
		if (take_fork(p) == 1)
			return (1);
	}
	else
		pthread_mutex_unlock(it->lock);
	return (0);
}

int						specific_mutex(t_philosopher *p, int action)
{
	t_forks	*tmp;
	t_forks	*it;
	int		fork1;
	int		fork2;

	it = p->fork;
	tmp = p->fork->head;
	fork1 = p->id;
	if (p->id == p->p->number_of_t_philosophers)
		fork2 = 1;
	else
		fork2 = p->id + 1;
	while (it->number != fork1)
		it = it->next;
	if (lock_unlock(it, p, action) == 1)
		return (1);
	while (it != 0 && it->number != fork2)
		it = it->next;
	if (it == 0)
		it = tmp;
	if (lock_unlock(it, p, action) == 1)
		return (1);
	return (0);
}

int						dead_message(t_philosopher *p, char *tim)
{
	char	*name;
	char	*line;
	char	*tmp;

	pthread_mutex_lock(p->write_lock);
	name = ft_itoa(p->id);
	line = ft_strjoin(tim, "\t");
	tmp = line;
	line = ft_strjoin(line, name);
	free(tmp);
	tmp = line;
	line = ft_strjoin(line, "\tdied\n");
	free(tmp);
	write(1, line, ft_strlen(line));
	free(line);
	free(name);
	free(tim);
	pthread_mutex_unlock(p->write_lock);
	return (0);
}

/*
**g_dead equal to one to stop all the processes
**and g_error to one so that the main returns 1 in the end
*/

void					*error(char *str)
{
	write(1, str, ft_strlen(str));
	g_dead = 1;
	g_error = 1;
	return (0);
}

void					free_philo(t_philosopher *p)
{
	t_forks	*tmp;

	free(p->p);
	while (p->fork != 0)
	{
		free(p->fork->lock);
		tmp = p->fork->next;
		free(p->fork);
		p->fork = tmp;
	}
	free(p->write_lock);
	free(p->dead_lock);
	free(p);
}
