/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduribei <eduribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 16:11:14 by eduribei          #+#    #+#             */
/*   Updated: 2025/01/02 21:59:50 by eduribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_assign_forks(t_philos *philo)
{
	size_t	i;
	size_t	n;

	i = philo->index;
	n = philo->main->params->nb_philos;
	
	if (i == 0)
	{
		philo->fork1 = &philo->main->forks[i];
		philo->fork2 = NULL;
	}
	else if (i == n - 1)
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

void	ft_init_threads(t_main *m)
{
	size_t	i;

	i = 0;
	while (i < m->params->nb_philos)
	{
		m->ph[i].index = i;
		m->ph[i].nb_meals_had = 0;
		m->ph[i].main = m;
		m->ph[i].is_detached = false;
		m->ph[i].tm_lastmeal = m->params->start_time;
		ft_assign_forks(&m->ph[i]);
		if (pthread_create(&m->th[i], NULL, &ft_philo, (void *)&m->ph[i]) != 0)
			ft_error("Failed to create philosopher thread.\n", m);
		i++;
	}
	if (pthread_create(&m->monitor, NULL, &stop_monitor, m) != 0)
		ft_error("Failed to create monitor thread.\n", m);
	return ;
}

void	ft_init_mutexes(t_main *main)
{
	size_t	a;

	a = 0;
	while (a < main->params->nb_philos + 1)
		pthread_mutex_init(&main->forks[a++], NULL);
	pthread_mutex_init(&main->stop_mutex, NULL);
	pthread_mutex_init(&main->print_mutex, NULL);
	pthread_mutex_init(&main->meal_mutex, NULL);
	pthread_mutex_init(&main->time_mutex, NULL);
	pthread_mutex_init(&main->detached_mutex, NULL);
	main->params->stop_mutex = &main->stop_mutex;
	main->params->print_mutex = &main->print_mutex;
	main->params->meal_mutex = &main->meal_mutex;
	main->params->time_mutex = &main->time_mutex;
	main->params->detached_mutex = &main->detached_mutex;
	return ;
}
