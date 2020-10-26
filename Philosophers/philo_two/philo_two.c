/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 15:24:11 by artainmo          #+#    #+#             */
/*   Updated: 2020/10/25 15:55:28 by artainmo         ###   ########.fr       */
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
**your semaphores or restart computer.
**Caution when testing infinite loop and quiting it with control-c, you do not
**unlink the semaphore, thus above error will occur, use underlying main
**to resolve problem without changing computers
** #include <semaphore.h>
**
** int main()
** {
** 	sem_unlink("/write");
** 	sem_unlink("/dead");
** 	sem_unlink("/forks");
** }
**
**If time does not advance, but goes very slightly backwards this is possible
**because every thread has its own starting time that comes slghtly after the
**prior thread.
**
**Rare not understood, probably linked to semaphore lib, bug of directly
**quiting the program with a philospher dead at time_before_dead
**Caused by fault in calculation of
**"since_last_meal = current_time - p->last_meal_time;" while they all are
**equal to long long int -> show with commented printf that error makes no
**sense and only occurs in rare random cases
**Looks similar to not understood bug -> bug occurs whereas after a philospher
**dies, number of philospher becomes 0 and thread enters the eat_count write,
**for unknown reason
**Those bugs do not exist with use of mutex and
**are thus probably associated with semaphore lib
**
** ./philo_two 6 1000 2000 2000 5
** ./philo_two 3 8000 2000 2000
** ./philo_two 2 8000 3000 3000 5
** ./philo_two 7 8000 3000 3000 1
** ./philo_two 7 8000 3000 3000 0
*/

int g_dead = 0;
int g_eat_count = 0;
int g_eating_counter = 0;
int g_error = 0;

static void	*dead_check(void *arg)
{
	t_philosopher		*p;
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
			// printf("~%llu\n", current_time);
			// printf("~~%llu\n", p->last_meal_time);
			// printf("~~%llu\n", since_last_meal);
			dies(p, ft_itoa(current_time - p->start_time));
			break ;
		}
		if (p->p->number_of_times_each_t_philosopher_must_eat != -1
				&& p->p->number_of_times_each_t_philosopher_must_eat * p->p->number_of_t_philosophers <= g_eating_counter)
		{
			sem_wait(p->write_lock);
			if (g_eat_count == 0 && g_dead != 1) //To block the write of eat_count, because bug occurs whereas after a philospher dies, number of philospher becomes 0 and thread enters the eat_count write, for unknown reason
				write(1, "number of times each philosopher must eat attained\n", 51);
			g_eat_count = 1;
			sem_post(p->write_lock);
			break ;
		}
	}
	return (0);
}

static void	*philo_start(void *arg)
{
	t_philosopher	*p;
	pthread_t	id;

	p = (t_philosopher *)arg;
	p->start_time = get_time();
	p->last_meal_time = get_time();
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
	pthread_t	id;
	int			i;

	i = 1;
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
		error("Not enough t_philosophers\n");
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
