/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 15:32:00 by artainmo          #+#    #+#             */
/*   Updated: 2020/10/25 16:15:07 by artainmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static int	ft_counter(int n)
{
	int counter;

	counter = 0;
	if (n < 0)
	{
		counter++;
		n = n * -1;
	}
	while (n >= 10)
	{
		counter++;
		n = n / 10;
	}
	counter++;
	return (counter);
}

static void	ft_neg(int *n, char *str)
{
	*n = *n * -1;
	str[0] = '-';
}

char		*ft_itoa(int n)
{
	char	*str;
	int		counter;

	counter = ft_counter(n) - 1;
	if (!(str = malloc(sizeof(char) * (ft_counter(n) + 1))))
		return (error("Malloc failed\n"));
	if (n == -2147483648)
	{
		if (!(str = ft_strdup("-2147483648")))
			return (0);
		return (str);
	}
	else if (n < 0)
		ft_neg(&n, str);
	str[counter + 1] = '\0';
	while (n >= 10)
	{
		str[counter] = n % 10 + 48;
		n = n / 10;
		counter--;
	}
	str[counter] = n % 10 + 48;
	return (str);
}

static void	ft_cat(char const *s1, char *str, int *i)
{
	while (s1[*i])
	{
		str[*i] = s1[*i];
		*i = *i + 1;
	}
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		l;

	i = 0;
	l = 0;
	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	if (!(str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (error("Malloc failed\n"));
	ft_cat(s1, str, &i);
	while (s2[l])
	{
		str[i + l] = s2[l];
		l++;
	}
	str[i + l] = '\0';
	return (str);
}
