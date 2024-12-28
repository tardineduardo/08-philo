/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduribei <eduribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 15:01:18 by eduribei          #+#    #+#             */
/*   Updated: 2024/12/27 17:02:14 by eduribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	grab_fork_1(t_philo *philo)
{	
	ft_check_stop(philo);
	pthread_mutex_lock(&philo->r->forks[philo->index]);	
	ft_check_stop(philo);
	pthread_mutex_lock(&philo->r->print);
	print("philo %i grabbed a fork.\n", philo->index);
	pthread_mutex_unlock(&philo->r->print);
}

void	grab_fork_2(t_philo *philo)
{
	ft_check_stop(philo);
	pthread_mutex_lock(&philo->r->forks[philo->index + 1]);
	ft_check_stop(philo);
	pthread_mutex_lock(&philo->r->print);
	print("philo %i grabbed a fork.\n", philo->index);
	pthread_mutex_unlock(&philo->r->print);			

}

void	eat(t_philo *philo)
{

}

void	thsleep(t_philo *philo)
{


}

void	think(t_philo *philo)
{

}

void	ft_check_stop(t_philo *philo)
{
	pthread_mutex_lock(philo->r->stop);
	if (philo->r->stop)
		pthread_exit(0);
	pthread_mutex_unlock(philo->r->stop);
	return ;
}

void	*ft_philosopher(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	printf("Hello from philosopher %li.\n", philo->index);
	while (1)
	{
		philo_grab_fork_1(philo);
		philo_grab_fork_2(philo);
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
}

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
