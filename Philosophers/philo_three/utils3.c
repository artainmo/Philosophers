/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 16:27:07 by artainmo          #+#    #+#             */
/*   Updated: 2020/10/26 12:37:28 by artainmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

/*
**-1 as pid value, causes all the processes in computer to finish
**and causes bugs... 0 causes main and child processes to finish
*/

void					dead_message(t_philosopher *p, char *tim)
{
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
	free(line);
	free(name);
	free(tim);
	free_philo(p);
	kill(0, SIGKILL);
}

/*
**https://unix.stackexchange.com/questions/275184/
**when-interrupting-a-process-does-a-memory-leak-occur
**Killing all the processes frees the memory, nomatter how a process dies
**all of its associated memory will be freed besides tmp files.
**Freeing is necessary in long-running programs, but once a program/process
**is about to die freeing is not necessary
*/

void					error(char *str)
{
	write(1, str, ft_strlen(str));
	kill(0, SIGKILL);
}

void					free_philo(t_philosopher *p)
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
