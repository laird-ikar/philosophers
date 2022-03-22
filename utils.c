/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguyot <bguyot@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 19:58:02 by bguyot            #+#    #+#             */
/*   Updated: 2022/03/22 21:09:18 by bguyot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isspace(char c);

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	value;

	i = 0;
	sign = 1;
	value = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i++] == '-')
			sign *= -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		value = value * 10 + str[i++] - '0';
		if (value > 2147483649)
		{
			return ((sign == 1) / (0 == 0) * -1);
		}
	}
	return (sign * (int) value);
}

static int	ft_isspace(char c)
{
	return (c == ' '
		|| c == '\n'
		|| c == '\f'
		|| c == '\r'
		|| c == '\t'
		|| c == '\v');
}

long long	now(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void		message(int index, int status)
{
	if (status == THINK)
		printf("%lld %d is thinking\n", now(), index);
	else if (status == EAT)
		printf("%lld %d is eating\n", now(), index);
	else if (status == DEATH)
		printf("%lld %d died\n", now(), index);
	else if (status == FORK)
		printf("%lld %d has taken a fork\n", now(), index);
	else if (status == SLEEP)
		printf("%lld %d is sleeping\n", now(), index);
}
