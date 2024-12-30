/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduribei <eduribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 16:09:51 by eduribei          #+#    #+#             */
/*   Updated: 2024/12/28 16:12:48 by eduribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_grab_fork_1(t_philo *philo)
{
	ft_check_stop(philo);
	pthread_mutex_lock(philo->fork1);
	gettimeofday(&philo->tlog, NULL);

	ft_check_stop(philo);
	pthread_mutex_lock(philo->r->printm);
	printf("%li Philo%li grabbed a fork.\n", philo->tlog.tv_usec, philo->index);
	pthread_mutex_unlock(philo->r->printm);

	pthread_mutex_unlock(philo->fork1);
}

void	philo_grab_fork_2(t_philo *philo)
{
	ft_check_stop(philo);
	pthread_mutex_lock(philo->fork2);
	gettimeofday(&philo->tlog, NULL);

	ft_check_stop(philo);
	pthread_mutex_lock(philo->r->printm);
	printf("%li Philo%li grabbed a fork.\n", philo->tlog.tv_usec, philo->index);
	pthread_mutex_unlock(philo->r->printm);

	pthread_mutex_unlock(philo->fork1);
	pthread_mutex_unlock(philo->fork2);
}

void	philo_eating(t_philo *philo)
{
	ft_check_stop(philo);
	pthread_mutex_lock(philo->r->printm);
	printf("%li Philo%li is eating.\n", philo->tlog.tv_usec, philo->index);
	pthread_mutex_unlock(philo->r->printm);
	usleep(philo->r->params->teat);
}

void	philo_sleeping(t_philo *philo)
{
	ft_check_stop(philo);
	pthread_mutex_lock(philo->r->printm);
	printf("%li Philo%li is sleeping.\n", philo->tlog.tv_usec, philo->index);
	pthread_mutex_unlock(philo->r->printm);
	usleep(philo->r->params->tsleep);

}

void	philo_thinking(t_philo *philo)
{
	ft_check_stop(philo);
	pthread_mutex_lock(philo->r->printm);
	printf("%li Philo%li is thinking.\n", philo->tlog.tv_usec, philo->index);
	pthread_mutex_unlock(philo->r->printm);
}
