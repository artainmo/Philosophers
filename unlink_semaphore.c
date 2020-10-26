/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unlink_semaphore.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 10:19:39 by artainmo          #+#    #+#             */
/*   Updated: 2020/10/26 10:22:01 by artainmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <semaphore.h>

/*
**If creation of semaphore fails (permission denied) it is because the
**semaphore has not been destroyed and the computer keeps it in memory even
**after the program has finished, so the solution is to always unlink and
**close your semaphores or restart computer
**Caution when testing infinite loop and quiting it with control-c,
**you do not unlink the semaphore, thus above error will occur
*/

int	main(void)
{
	sem_unlink("/write");
	sem_unlink("/dead");
	sem_unlink("/forks");
	sem_unlink("/eat_max");
}
