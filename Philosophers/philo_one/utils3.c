/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 12:25:31 by artainmo          #+#    #+#             */
/*   Updated: 2020/10/25 13:22:06 by artainmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int						dead_message(t_philosopher *p, char *tim)
{
	char	*timestamp;
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
