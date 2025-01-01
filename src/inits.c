/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduribei <eduribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 16:11:14 by eduribei          #+#    #+#             */
/*   Updated: 2024/12/28 17:44:02 by eduribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_assign_forks(t_philos *philo)
{
	size_t	i;
	size_t	n;

	i = philo->index;
	n = philo->main->params->number_of_philos;

	if (i == 0)
	{
		philo->fork1 = &philo->main->forks[0];
		philo->fork2 = &philo->main->forks[1];
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
	return ;
}

void	ft_init_threads(t_resources *main)
{
	int	i;

	i = 0;
	while (i < main->params->number_of_philos)
	{
		main->philo[i].index = i;
		main->philo[i].number_of_meals_had = 0;
		main->philo[i].is_detached = false;
		main->philo[i].main = main;
		ft_assign_forks(&main->philo[i]);
		gettimeofday(&main->philo->time_of_last_meal, NULL);
		pthread_create(&main->th[i], NULL, &ft_philo, (void *)&main->philo[i]);
		i++;
	}
	return ;
}

void	ft_init_mutexes(t_resources *r)
{
	int	a;

	a = 0;
	while (a < r->params->number_of_philos + 1)
		pthread_mutex_init(&r->forks[a++], NULL);
	pthread_mutex_init(r->stop_mutex, NULL);
	pthread_mutex_init(r->print_mutex, NULL);
	r->params->stop_mutex = r->stop_mutex;
	r->params->print_mutex = r->print_mutex;
	return ;
}
