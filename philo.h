/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguyot <bguyot@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 19:20:41 by bguyot            #+#    #+#             */
/*   Updated: 2022/03/22 21:05:17 by bguyot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h> //DEBUG

# ifndef T_FORK
#  define T_FORK

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int				is_held;
}	t_fork;
# endif

# ifndef T_PHILO
#  define T_PHILO

typedef struct s_philo
{
	int				nb;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				to_eat;
	int				sim;
	int				done;
	long long		*since_eat;
	long long		*since_change;
	pthread_mutex_t	waiter;
	t_fork			**forks;
}	t_philo;
# endif

#ifndef T_INDEXED
#define T_INDEXED

typedef struct s_indexed
{
	int		index;
	t_philo	*philo;
}	t_indexed;
#endif

enum
{
	THINK = 0,
	EAT	= 1,
	DEATH = 2,
	FORK = 3,
	SLEEP = 4
};

int			ft_atoi(const char *str);
void		*job(void *idx);
long long	now(void);
void		message(int index, int status);

#endif
