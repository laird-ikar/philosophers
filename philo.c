/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguyot <bguyot@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 18:54:06 by bguyot            #+#    #+#             */
/*   Updated: 2022/03/22 21:14:10 by bguyot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void init(t_philo *philo, int n, char *args[]);
static void	set_thread(t_philo *philo);
static void tini(t_philo *philo);

int main(int argc, char *argv[])
{
	t_philo		*philo;

	//TODO proteger malloc + argc
	philo = malloc(sizeof(t_philo));
	init(philo, argc, argv);
	set_thread(philo);
	tini(philo);
	free(philo);
}

static void init(t_philo *philo, int n, char *args[])
{
	int	i;

	philo->nb = ft_atoi(args[1]);
	philo->die_time = ft_atoi(args[2]);
	philo->eat_time = ft_atoi(args[3]);
	philo->sleep_time = ft_atoi(args[4]);
	if (n == 6)
		philo->to_eat = ft_atoi(args[5]);
	philo->sim = 1;
	pthread_mutex_init(&philo->waiter, NULL);
	philo->forks = malloc(sizeof(t_fork *) * philo->nb);
	philo->since_eat = malloc(sizeof(long long) * philo->nb);
	philo->since_change = malloc(sizeof(long long) * philo->nb);
	i = 0;
	while (i < philo->nb)
	{
		philo->forks[i] = malloc(sizeof(t_fork));
		philo->forks[i]->is_held = 0;
		philo->since_eat[i] = now();
		philo->since_change[i] = now();
		pthread_mutex_init(&philo->forks[i++]->mutex, NULL);
	}
	//TODO proteger malloc
}

static void	set_thread(t_philo *philo)
{
	t_indexed	**idx;
	pthread_t	*philosophers;
	int			i;

	idx = malloc(sizeof(t_indexed *) * philo->nb);
	philosophers = malloc(sizeof(pthread_t *) * philo->nb);
	i = 0;
	while (i < philo->nb)
	{
		idx[i] = malloc(sizeof(t_indexed));
		idx[i]->index = i;
		idx[i]->philo = philo;
		pthread_create(&philosophers[i], NULL, job, idx[i]);
		i++;
	}
	while (philo->sim)
		;
	i = 0;
	while (i < philo->nb)
	{
		free(idx[i++]);
		pthread_detach(philosophers[i]);
	}
	free(idx);
	free(philosophers);
}

static void tini(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->nb)
	{
		pthread_mutex_destroy(&philo->forks[i]->mutex);
		free(philo->forks[i]);
		i++;
	}
	free(philo->forks);
	free(philo->since_eat);
	free(philo->since_change);
}
