/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 15:24:11 by artainmo          #+#    #+#             */
/*   Updated: 2020/10/26 11:20:42 by artainmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

/*
**All of the forks will be simulated with a semaphore with value number of
**forks, each time a t_philosopher takes a fork the semaphore loses a value,
**when semaphore is equal to 0, 0 forks are on the table and t_philosophers
**have to wait The mutexes used to control the write lock and dead lock are
**replaced by binary semaphore or simply a semaphore with intial value 1
**
**If creation of semaphore fails (permission denied) it is because the
**semaphore has not been destroyed and the computer keeps it in memory even
**after the program has finished, so the solution is to always unlink and close
**your semaphores.
**Caution when testing infinite loop and quiting it with control-c, you do not
**unlink the semaphore, thus above error will occur, use underlying main
**to resolve.
** #include <semaphore.h>
**
** int main()
** {
** 	sem_unlink("/write");
** 	sem_unlink("/dead");
** 	sem_unlink("/forks");
** }
**
** ./philo_two 6 1000 2000 2000 5
** ./philo_two 3 8000 2000 2000
** ./philo_two 2 8000 3000 3000 5
** ./philo_two 7 8000 3000 3000 1
** ./philo_two 7 8000 3000 3000 0
*/

int g_dead = 0;
int g_max_eat = 0;
int g_eating_counter = 0;
int g_error = 0;

static int	dead_check2(t_philosopher *p, long long int current_time,
		long long int since_last_meal)
{
	current_time = get_time();
	since_last_meal = current_time - p->last_meal_time;
	if (p->p->time_to_die <= since_last_meal && !p->is_eating)
	{
		dies(p, ft_itoa(current_time - p->start_time));
		return (1);
	}
	if (p->p->number_of_times_each_t_philosopher_must_eat != -1
			&& p->p->number_of_times_each_t_philosopher_must_eat
						* p->p->number_of_t_philosophers <= g_eating_counter)
	{
		sem_wait(p->write_lock);
		if (g_max_eat == 0 && g_dead != 1)
			write(1, "times each philosopher must eat attained\n", 41);
		g_max_eat = 1;
		sem_post(p->write_lock);
		return (1);
	}
	return (0);
}

static void	*dead_check(void *arg)
{
	t_philosopher	*p;
	long long int	current_time;
	long long int	since_last_meal;

	p = (t_philosopher *)arg;
	p->is_eating = 0;
	while (1)
	{
		if (dead_check2(p, current_time, since_last_meal) == 1)
			break ;
	}
	return (0);
}

static void	*philo_start(void *arg)
{
	t_philosopher	*p;
	pthread_t		id;

	p = (t_philosopher *)arg;
	if (pthread_create(&id, NULL, dead_check, p))
		return (error("Creation of thread failed\n"));
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
	pthread_t		id;
	int				i;

	i = 1;
	p->start_time = get_time();
	p->last_meal_time = get_time();
	while (i <= p->p->number_of_t_philosophers)
	{
		new = new_philo(p, i);
		if (pthread_create(&id, NULL, philo_start, new) != 0)
		{
			error("Creation of thread failed\n");
			return (0);
		}
		usleep(50);
		i++;
	}
	pthread_join(id, NULL);
	free_philo(p);
	if (g_error == 1)
		return (0);
	return (1);
}

int			main(int argc, char **argv)
{
	t_philosopher *p;

	if (argc != 5 && argc != 6)
	{
		error("Error in program arguments\n");
		return (1);
	}
	if ((p = init_philo(argc, argv)) == 0)
		return (1);
	if (p->p->number_of_t_philosophers < 2)
	{
		error("Not enough philosophers\n");
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
