/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguyot <bguyot@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 20:26:01 by bguyot            #+#    #+#             */
/*   Updated: 2022/03/22 21:15:07 by bguyot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	death(t_philo *philo, int index);
static void	eat(t_philo *philo, int index, int *status);
static void	ft_sleep(t_philo *philo, int index, int *status);
static void think(t_philo *philo, int index, int *status);

void	*job(void *vars)
{
	t_philo	*philo;
	int		index;
	int		status;

	philo = ((t_indexed *) vars)->philo;
	index = ((t_indexed *) vars)->index;
	status = THINK;
	message(index, THINK);
	while(philo->sim)
	{
		if (now() - philo->since_eat[index] >= philo->die_time)
			death(philo, index);
		else if (status == THINK)
			think(philo, index, &status);
		else if (status == EAT)
			eat(philo, index, &status);
		else if (status == SLEEP)
			ft_sleep(philo, index, &status);
	}
	return (NULL);
}

static void	death(t_philo *philo, int index)
{
	message(index, DEATH);
	philo->sim = 0;
}

static void	eat(t_philo *philo, int index, int *status)
{
	//static	int eat_times = 0;

	if (now() - philo->since_change[index] >= philo->eat_time)
	{
		//TODO compter nombre de miam miam (maybe elsewhere)
		/*eat_times++;
		if (eat_times == philo->to_eat)
		{
			philo->done++;
			if (philo->done == philo->nb)
				philo->sim = 0;
		}*/
		message(index, SLEEP);
		*status = SLEEP;
		philo->since_change[index] = now();
		philo->forks[index]->is_held = 0;
		pthread_mutex_unlock(&philo->forks[index]->mutex);
		philo->forks[(index + 1) % philo->nb]->is_held = 0;
		pthread_mutex_unlock(&philo->forks[(index + 1) % philo->nb]->mutex);
	}
}

static void	ft_sleep(t_philo *philo, int index, int *status)
{
	if (now() - philo->since_change[index] >= philo->sleep_time)
	{
		message(index, THINK);
		*status = THINK;
		philo->since_change[index] = now();
	}
}

static void think(t_philo *philo, int index, int *status)
{
	if (philo->nb > 1)
	{
		//TODO smarter philosophers
		pthread_mutex_lock(&philo->waiter);
		if (!philo->forks[index]->is_held
			&& !philo->forks[(index + 1) % philo->nb]->is_held)
		{
			pthread_mutex_lock(&philo->forks[index]->mutex);
			philo->forks[index]->is_held = 1;
			message(index, FORK);
			pthread_mutex_lock(&philo->forks[(index + 1) % philo->nb]->mutex);
			philo->forks[(index + 1) % philo->nb]->is_held = 1;
			message(index, FORK);
			*status = EAT;
			philo->since_eat[index] = now();
			philo->since_change[index] = now();
			message(index, EAT);
		}
		pthread_mutex_unlock(&philo->waiter);
	}
}
