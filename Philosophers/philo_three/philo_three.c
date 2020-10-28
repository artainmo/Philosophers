/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 16:25:08 by artainmo          #+#    #+#             */
/*   Updated: 2020/10/26 11:25:49 by artainmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

/*
**named semaphores, sem_open creates named semaphores contrary to sem_init,
**are able to communicate between processes while unnamed semaphores can only
**communicate between threads
**
**
**If creation of semaphore fails (permission denied) it is because the
**semaphore has not been destroyed and the computer keeps it in memory even
**after the program has finished, so the solution is to always unlink and close
**your semaphores or restart computer
**Caution when testing infinite loop and quiting it with control-c, you do not
**unlink the semaphore, thus above error will occur,
**use underlying main to resolve problem without changing computers
**
** #include <semaphore.h>
**
** int main()
** {
** 	sem_unlink("/write");
** 	sem_unlink("/dead");
** 	sem_unlink("/forks");
** }
**
** ./philo_three 6 1000 2000 2000 5
** ./philo_three 3 8000 2000 2000
** ./philo_three 2 8000 3000 3000 5
** ./philo_three 7 8000 3000 3000 1
** ./philo_three 7 8000 3000 3000 0
**
**To stop the program when necessary kill(0) is used, by making the processes
**die the operating system will free back the memory once program ends
**so no memory leaks when killing processes
*/

static void	*dead_check(void *arg)
{
	t_philosopher	*p;
	long long int	current_time;
	long long int	since_last_meal;

	p = (t_philosopher *)arg;
	p->is_eating = 0;
	while (1)
	{
		current_time = get_time();
		since_last_meal = current_time - p->last_meal_time;
		if (p->p->time_to_die <= since_last_meal && !p->is_eating)
		{
			dies(p, ft_itoa(current_time - p->start_time));
			break ;
		}
	}
	return (0);
}

static void	*philo_start(void *arg)
{
	t_philosopher	*p;
	pthread_t		id;

	p = (t_philosopher *)arg;
	if (pthread_create(&id, NULL, dead_check, p))
		error("Creation of thread failed\n");
	while (1)
	{
		if (eat(p) == 1)
			break ;
		if (sleeps(p) == 1)
			break ;
		if (think(p) == 1)
			break ;
	}
	sem_post(p->forks);
	return (0);
}

static int	create_t_philosophers(t_philosopher *p)
{
	t_philosopher	*new;
	pid_t			pid;
	int				i;

	i = 1;
	p->start_time = get_time();
	p->last_meal_time = get_time();
	while (i <= p->p->number_of_t_philosophers)
	{
		new = new_philo(p, i);
		if ((pid = fork()) == -1)
			error("Forking process failed\n");
		if (!pid)
		{
			philo_start(new);
			exit(0);
		}
		usleep(50);
		i++;
	}
	waitpid(pid, 0, 0);
	free_philo(p);
	return (1);
}

int			main(int argc, char **argv)
{
	t_philosopher *p;

	if (argc != 5 && argc != 6)
	{
		write(1, "Error in program arguments\n", 27);
		return (1);
	}
	if ((p = init_philo(argc, argv)) == 0)
		return (1);
	if (p->p->number_of_t_philosophers < 2)
	{
		write(1, "Not enough philosophers\n", 24);
		free_philo(p);
		return (1);
	}
	if (p->p->number_of_times_each_t_philosopher_must_eat == 0)
	{
		write(1, "number of times each philosopher must eat attained\n", 51);
		free_philo(p);
		return (1);
	}
	if (create_t_philosophers(p) == 0)
		return (1);
}
