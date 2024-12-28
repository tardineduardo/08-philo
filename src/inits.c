/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduribei <eduribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 16:11:14 by eduribei          #+#    #+#             */
/*   Updated: 2024/12/28 16:11:27 by eduribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_threads(t_resources *r)
{
	int	i;

	i = 0;
	while (i < r->params->nphilos)
	{
		r->philo[i].index = i;
		r->philo[i].detached = false;
		r->philo->r = r;
		pthread_create(&r->th[i], NULL, &ft_philosopher, (void *)&r->philo[i]);
		i++;
	}
	return ;
}

void	ft_init_mutexes(t_resources *r)
{
	int a;

	a = 0;
	while (a < r->params->nphilos)
		pthread_mutex_init(&r->forks[a++], NULL);
	pthread_mutex_init(&r->stop, NULL);

}