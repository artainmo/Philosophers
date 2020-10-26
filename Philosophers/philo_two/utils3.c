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

int						dead_message(t_philosopher *p, char *tim)
{
	char	*name;
	char	*line;
	char	*tmp;

	sem_wait(p->write_lock);
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
	sem_post(p->write_lock);
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
	sem_unlink("/write");
	sem_unlink("/dead");
	sem_unlink("/forks");
	sem_close(p->write_lock);
	sem_close(p->dead_lock);
	sem_close(p->forks);
	free(p->p);
	free(p);
}
