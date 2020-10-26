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

/*
**-1 as pid value, causes all the processes in computer to finish
**and causes bugs... 0 causes main and child processes to finish
*/

int						dead_message(philosopher *p, char *tim)
{
	char	*timestamp;
	char	*name;
	char	*line;
	char	*tmp;

	sem_wait(p->write_lock);
	*p->g_dead = 1;
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
	free_philo(p);
	kill(0, SIGKILL);
	return (0);
}

void					*error(char *str)
{
	write(1, str, ft_strlen(str));
	return (0);
}

void					free_philo(philosopher *p)
{
	sem_unlink("/write");
	sem_unlink("/dead");
	sem_unlink("/forks");
	sem_unlink("/eat_max");
	sem_close(p->write_lock);
	sem_close(p->dead_lock);
	sem_close(p->forks);
	free(p->p);
	free(p);
}
