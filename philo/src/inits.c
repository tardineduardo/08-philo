/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduribei <eduribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 16:11:14 by eduribei          #+#    #+#             */
/*   Updated: 2025/01/02 12:21:57 by eduribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_assign_forks(t_philos *philo)
{
	size_t	i;
	size_t	n;

	i = philo->index;
	n = philo->main->params->nb_philos;
	if (i == n - 1)
	{
		philo->fork1 = &philo->main->forks[0];
		philo->fork2 = &philo->main->forks[i];
	}
	else
	{
		philo->fork1 = &philo->main->forks[i];
		philo->fork2 = &philo->main->forks[i + 1];
	}
}

void	ft_init_threads(t_main *main)
{
	size_t	s;
	size_t	i;

	i = 0;
	while (i < main->params->nb_philos)
	{
		main->ph[i].index = i;
		main->ph[i].nb_meals_had = 0;
		main->ph[i].main = main;
		main->ph[i].tm_lastmeal = main->params->start_time;
		ft_assign_forks(&main->ph[i]);
		s = pthread_create(&main->th[i], NULL, &ft_philo, (void *)&main->ph[i]);
		if (s != 0)
			ft_error("Failed to create philosopher thread.\n", main);
		i++;
	}
	s = pthread_create(&main->monitor, NULL, &stop_monitor, main);
	if (s != 0)
		ft_error("Failed to create monitor thread.\n", main);
	return ;
}

void	ft_init_mutexes(t_main *r)
{
	size_t	a;

	a = 0;
	while (a < r->params->nb_philos + 1)
		pthread_mutex_init(&r->forks[a++], NULL);
	pthread_mutex_init(&r->stop_mutex, NULL);
	pthread_mutex_init(&r->print_mutex, NULL);
	pthread_mutex_init(&r->meal_mutex, NULL);
	r->params->stop_mutex = &r->stop_mutex;
	r->params->print_mutex = &r->print_mutex;
	r->params->meal_mutex = &r->meal_mutex;
	return ;
}
