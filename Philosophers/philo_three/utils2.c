/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 16:36:07 by artainmo          #+#    #+#             */
/*   Updated: 2020/10/26 08:51:15 by artainmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int			ft_strlen(const char *str)
{
	int i;

	i = 0;
	while (str[i] != 0)
		i++;
	return (i);
}

static void	check_plus_minus(char const *str, int *i, int *mc, int *c)
{
	if ((str[*i] == 43 || str[*i] == 45) && str[*i])
	{
		while ((str[*i] == 43 || str[*i] == 45) && str[*i])
		{
			if (str[*i] == 45)
				*mc = *mc + 1;
			*i = *i + 1;
			*c = *c + 1;
		}
	}
}

static void	check_digits(char const *str, int *i, long *res)
{
	if (str[*i] > 47 && str[*i] < 58 && str[*i])
	{
		while (str[*i] > 47 && str[*i] < 58 && str[*i])
		{
			*res = *res * 10 + (str[*i] - 48);
			*i = *i + 1;
		}
	}
}

int			ft_atoi(const char *str)
{
	int		i;
	int		mc;
	long	res;
	int		c;

	i = 0;
	res = 0;
	c = 0;
	mc = 0;
	while (str[i] == '\n' || str[i] == ' ' || str[i] == '\t' || str[i] == '\v'
			|| str[i] == '\f' || str[i] == '\r')
		i++;
	check_plus_minus(str, &i, &mc, &c);
	check_digits(str, &i, &res);
	if (!(mc % 2 == 0))
		res = res * -1;
	if (c > 1)
		return (0);
	if (res < 9223372036854775807 && res > 2147483647)
		return (0);
	else if (res > -9223372036854775807 && res < -2147483648)
		return (-1);
	else
		return (res);
}

char		*ft_strdup(const char *src)
{
	int		i;
	char	*str;

	i = 0;
	while (src[i])
		i++;
	if (!(str = malloc(sizeof(char) * (i + 1))))
		error("Malloc failed\n");
	i = 0;
	while (src[i])
	{
		str[i] = src[i];
		i++;
	}
	str[i] = 0;
	return (str);
}
