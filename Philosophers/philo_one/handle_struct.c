/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 11:10:28 by artainmo          #+#    #+#             */
/*   Updated: 2020/10/26 10:50:07 by artainmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

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

t_forks			*init_forks(int number)
{
	int		i;
	t_forks	*fork;

	i = 2;
	if ((fork = malloc(sizeof(t_forks))) == 0)
		return (error("Malloc failed\n"));
	fork->head = fork;
	fork->number = 1;
	if ((fork->lock = malloc(sizeof(pthread_mutex_t))) == 0)
		return (error("Malloc failed"));
	while (i <= number)
	{
		if ((fork->next = malloc(sizeof(t_forks))) == 0)
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

t_philosopher	*init_philo(int argc, char **argv)
{
	t_philosopher *philo;

	if ((philo = malloc(sizeof(t_philosopher))) == 0)
		return (error("Malloc failed\n"));
	if ((philo->p = init_params(argc, argv)) == 0)
		return (error("Malloc failed\n"));
	if ((philo->fork = init_forks(philo->p->number_of_t_philosophers)) == 0)
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

t_philosopher	*new_philo(t_philosopher *old_philo, int i)
{
	t_philosopher *philo;

	if ((philo = malloc(sizeof(t_philosopher))) == 0)
		return (error("Malloc failed\n"));
	philo->p = old_philo->p;
	philo->fork = old_philo->fork;
	philo->id = i;
	philo->write_lock = old_philo->write_lock;
	philo->dead_lock = old_philo->dead_lock;
	philo->start_time = old_philo->start_time;
	philo->last_meal_time = old_philo->last_meal_time;
	return (philo);
}
