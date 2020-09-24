#include "philo_two.h"

int ft_strlen(const char *str)
{
  int i;

  i = 0;
  while(str[i] != 0)
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

static char	*ft_strdup(const char *src)
{
	int		i;
	char	*str;

	i = 0;
	while (src[i])
		i++;
	if (!(str = malloc(sizeof(char) * (i + 1))))
		return (0);
	i = 0;
	while (src[i])
	{
		str[i] = src[i];
		i++;
	}
	str[i] = 0;
	return (str);
}


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
		return (0);
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
		return (0);
	ft_cat(s1, str, &i);
	while (s2[l])
	{
		str[i + l] = s2[l];
		l++;
	}
	str[i + l] = '\0';
	return (str);
}
