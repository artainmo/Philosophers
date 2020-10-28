/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 15:22:58 by artainmo          #+#    #+#             */
/*   Updated: 2020/10/25 15:46:38 by artainmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

t_params		*init_params(int argc, char **argv)
{
	t_params *ret;

	if ((ret = malloc(sizeof(t_params))) == 0)
		return (error("Malloced failed\n"));
	ret->number_of_t_philosophers = ft_atoi(argv[1]);
	ret->time_to_die = ft_atoi(argv[2]);
	ret->time_to_eat = ft_atoi(argv[3]) * 1000;
	ret->time_to_sleep = ft_atoi(argv[4]) * 1000;
	if (argc == 5)
		ret->number_of_times_each_t_philosopher_must_eat = -1;
	else
		ret->number_of_times_each_t_philosopher_must_eat = ft_atoi(argv[5]);
	return (ret);
}

/*
**First indicate a name starting with / to be able to recognize the already
**existing semaphore, second argument is a flag to create the sem if it does
**not already exist, third argument is the permission with 644 being read
**and write access, lastly indicate the number of forks or the semaphore values
*/

t_philosopher	*init_philo(int argc, char **argv)
{
	t_philosopher *philo;

	if ((philo = malloc(sizeof(t_philosopher))) == 0)
		return (error("Malloc failed\n"));
	if ((philo->p = init_params(argc, argv)) == 0)
		return (error("Malloc failed\n"));
	if ((philo->forks = sem_open("/forks", O_CREAT, 644, ft_atoi(argv[1])))
			== SEM_FAILED)
		return (error("Semaphore opening failed\n"));
	if ((philo->write_lock = sem_open("/write", O_CREAT, 644, 1)) == SEM_FAILED)
		return (error("Semaphore opening failed\n"));
	if ((philo->dead_lock = sem_open("/dead", O_CREAT, 644, 1)) == SEM_FAILED)
		return (error("Semaphore opening failed\n"));
	return (philo);
}

t_philosopher	*new_philo(t_philosopher *old_philo, int id)
{
	t_philosopher *philo;

	if ((philo = malloc(sizeof(t_philosopher))) == 0)
		return (error("Malloc failed\n"));
	philo->p = old_philo->p;
	philo->forks = old_philo->forks;
	philo->id = id;
	philo->write_lock = old_philo->write_lock;
	philo->dead_lock = old_philo->dead_lock;
	philo->dead_lock = old_philo->dead_lock;
	philo->start_time = old_philo->start_time;
	philo->last_meal_time = old_philo->last_meal_time;
	return (philo);
}
