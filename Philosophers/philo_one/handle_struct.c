/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 11:10:28 by artainmo          #+#    #+#             */
/*   Updated: 2020/10/25 11:14:34 by artainmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

params		*init_params(int argc, char **argv)
{
	params *ret;

	if ((ret = malloc(sizeof(params))) == 0)
		return (error("Malloced failed\n"));
	ret->number_of_philosophers = ft_atoi(argv[1]);
	ret->time_to_die = ft_atoi(argv[2]);
	ret->time_to_eat = ft_atoi(argv[3]) * 1000;
	ret->time_to_sleep = ft_atoi(argv[4]) * 1000;
	if (argc == 5)
		ret->number_of_times_each_philosopher_must_eat = -1;
	else
		ret->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	return (ret);
}

forks		*init_forks(int number)
{
	int		i;
	forks	*fork;

	i = 2;
	if ((fork = malloc(sizeof(forks))) == 0)
		return (error("Malloc failed\n"));
	fork->head = fork;
	fork->number = 1;
	if ((fork->lock = malloc(sizeof(pthread_mutex_t))) == 0)
		return (error("Malloc failed"));
	while (i <= number)
	{
		if ((fork->next = malloc(sizeof(forks))) == 0)
			return (error("Malloc failed\n"));
		fork->next->head = fork->head;
		fork = fork->next;
		fork->number = i;
		if ((fork->lock = malloc(sizeof(pthread_mutex_t))) == 0)
			return (error("Malloc failed\n"));
		if (pthread_mutex_init(fork->lock, NULL) != 0)
			error("Error with mutex lock creation\n");
		i++;
	}
	fork->next = 0;
	return (fork->head);
}

philosopher	*init_philo(int argc, char **argv)
{
	philosopher *philo;

	if ((philo = malloc(sizeof(philosopher))) == 0)
		return (error("Malloc failed\n"));
	if ((philo->p = init_params(argc, argv)) == 0)
		return (error("Malloc failed\n"));
	if ((philo->fork = init_forks(philo->p->number_of_philosophers)) == 0)
		return (error("Malloc failed\n"));
	if ((philo->write_lock = malloc(sizeof(pthread_mutex_t))) == 0)
		return (error("Malloc failed\n"));
	if (pthread_mutex_init(philo->write_lock, NULL) != 0)
		error("Error with mutex lock creation\n");
	if ((philo->dead_lock = malloc(sizeof(pthread_mutex_t))) == 0)
		return (error("Malloc failed"));
	if (pthread_mutex_init(philo->dead_lock, NULL) != 0)
		error("Error with mutex lock creation\n");
	return (philo);
}

philosopher	*new_philo(philosopher *old_philo, int id)
{
	philosopher *philo;

	if ((philo = malloc(sizeof(philosopher))) == 0)
		return (error("Malloc failed\n"));
	philo->p = old_philo->p;
	philo->fork = old_philo->fork;
	philo->id = id;
	philo->write_lock = old_philo->write_lock;
	philo->dead_lock = old_philo->dead_lock;
	return (philo);
}

int			specific_mutex(philosopher *p, int action)
{
	forks	*tmp;
	forks	*it;
	int		fork1;
	int		fork2;

	it = p->fork;
	tmp = p->fork->head;
	fork1 = p->id;
	if (p->id == p->p->number_of_philosophers)
		fork2 = 1;
	else
		fork2 = p->id + 1;
	while (it->number != fork1)
		it = it->next;
	if (action == LOCK)
	{
		pthread_mutex_lock(it->lock);
		if (take_fork(p) == 1)
			return (1);
	}
	else
		pthread_mutex_unlock(it->lock);
	while (it != 0 && it->number != fork2)
		it = it->next;
	if (it == 0)
		it = tmp;
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
