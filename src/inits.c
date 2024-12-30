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


void	ft_assign_forks(t_philo *philo)
{
	size_t	i;
	size_t	n;


	i = philo->index;
	n = philo->r->params->nphilos;

	if (i == 0)
	{
		philo->fork1 = &philo->r->forks[0];
		philo->fork2 = &philo->r->forks[1];
	}
	else if (i == n - 1)
	{
		philo->fork1 = &philo->r->forks[0];
		philo->fork2 = &philo->r->forks[i];
	}
	else
	{
		philo->fork1 = &philo->r->forks[i];
		philo->fork2 = &philo->r->forks[i + 1];
	}
}


void	ft_init_threads(t_resources *r)
{
	int	i;

	i = 0;
	while (i < r->params->nphilos)
	{
		r->philo[i].index = i;
		r->philo[i].total_meals = 0;
		r->philo[i].detached = false;
		r->philo[i].r = r;
		ft_assign_forks(&r->philo[i]);
		pthread_create(&r->th[i], NULL, &ft_philosopher, (void *)&r->philo[i]);
		i++;
	}
	return ;
}

void	ft_init_mutexes(t_resources *r)
{
	int	a;

	a = 0;
	while (a < r->params->nphilos + 1)
		pthread_mutex_init(&r->forks[a++], NULL);
	pthread_mutex_init(r->stopm, NULL);
	pthread_mutex_init(r->printm, NULL);

}
