/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 16:24:15 by artainmo          #+#    #+#             */
/*   Updated: 2020/10/25 16:24:51 by artainmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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

philosopher	*init_philo(int argc, char **argv)
{
  philosopher *philo;

  if ((philo = malloc(sizeof(philosopher))) == 0)
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
  if ((philo->eat_max = sem_open("/eat_max", O_CREAT, 644, 1)) == SEM_FAILED)
    return (error("Semaphore opening failed\n"));
  return (philo);
}

philosopher	*new_philo(philosopher *old_philo, int id)
{
  philosopher *philo;

  if ((philo = malloc(sizeof(philosopher))) == 0)
    return (error("Malloc failed\n"));
  philo->eating_counter = 0;
  philo->p = old_philo->p;
  philo->forks = old_philo->forks;
  philo->id = id;
  philo->write_lock = old_philo->write_lock;
  philo->dead_lock = old_philo->dead_lock;
  if ((philo->g_dead = malloc(sizeof(int))) == 0)
    return (error("Malloc failed\n"));
  *philo->g_dead = 0;
  if ((philo->g_eat_count = malloc(sizeof(int))) == 0)
    return (error("Malloc failed\n"));
  *philo->g_eat_count = 0;
  return (philo);
}
