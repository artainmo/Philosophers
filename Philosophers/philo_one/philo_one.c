/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 12:00:17 by artainmo          #+#    #+#             */
/*   Updated: 2020/10/26 11:10:07 by artainmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

/*
**threads share heap memory and static memory, thus memory allocated and global
**variables can be used interchangebly between threads
**threads only last the scope of their starting function
**
**
**Each time you execute code with same parameters you will have slightly
**different result which is normal and due to how fast each separate thread
**goes based on free memory at that time
**Writes not in order of time, normal because multiple threads with
**different times are waiting to get the mutex to be able to write
**
**
**We use mutex for access to the forks, but also
**for access to write (no interwined text), and when someone dies
**
**Verify rapid death ./philo_one 6 1000 2000 2000 5
**Infinity ./philo_one 3 8000 2000 2000
**verify eat count feature ./philo_one 7 8000 3000 3000 1
**verify eat count feature ./philo_one 7 8000 3000 3000 0
**verify eat count feature ./philo_one 2 8000 3000 3000 5
*/

int g_dead = 0;
int g_max_eat = 0;
/*
**To protect the write of "number of times each philosopher must eat attained
*/
int g_eating_counter = 0;
/*
**Counts how may times gets eaten
*/
int g_error = 0;
/*
**Global variables are used to stop all threads when necessay
*/

/*
**Second thread for each t_philosopher to constantly check if one is dying
**or eating_count is attained
*/

static int		dead_check2(t_philosopher *p, long long int current_time,
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
		pthread_mutex_lock(p->write_lock);
		if (g_max_eat == 0 && g_dead != 1)
			write(1, "times each philosopher must eat attained\n", 41);
		g_max_eat = 1;
		pthread_mutex_unlock(p->write_lock);
		return (1);
	}
	return (0);
}

static void		*dead_check(void *arg)
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

static void		*philo_start(void *arg)
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
	specific_mutex(p, UNLOCK);
	return (0);
}

/*
**Delay that happens between thread creation is equal to 4ms per 10philosophers
**This is not a problem as some philosopers will have to wait until they can
**start eating.
**If time to die is less than time of all philosoper appearance, this is not
**a problem as one of the philosopher will die in meantime and stop everything
*/

static int		create_t_philosophers(t_philosopher *p)
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

int				main(int argc, char **argv)
{
	t_philosopher	*p;

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
