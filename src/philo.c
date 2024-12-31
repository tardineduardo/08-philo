/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduribei <eduribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 15:01:18 by eduribei          #+#    #+#             */
/*   Updated: 2024/12/30 21:51:49 by eduribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_check_stop(t_philo *philo)
{
	pthread_mutex_lock(philo->r->stopm);
	if (philo->r->dead)
	{
		pthread_mutex_unlock(philo->r->stopm);
		pthread_exit(0);
	}
	pthread_mutex_unlock(philo->r->stopm);
	return ;
}

void	*ft_philosopher(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	//printf("Hello from philosopher %li.\n", philo->index);
	while (1)
	{
		if (philo_grab_fork_1(philo))
			break ;
		if (philo_grab_fork_2(philo))
			break ;
		if (philo_eating(philo))
			break ;
		if (philo_sleeping(philo))
			break ;
		if (philo_thinking(philo))
			break ;
	}
	return ;
}

void	ft_join_threads(t_resources *r)
{
	int	i;

	i = 0;
	while (i < r->params->nphilos)
	{
		if (!r->philo[i].detached)
			pthread_join(r->th[i], NULL);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_resources		*r;

	r = malloc(sizeof(t_resources));
	if (!r)
		ft_error("malloc failed.\n", r);
	ft_validate_args(argc, argv, r);
	ft_alloc_resources(r);
	ft_init_mutexes(r);
	ft_init_threads(r);
	ft_join_threads(r);
	ft_free_resources(r);
}
