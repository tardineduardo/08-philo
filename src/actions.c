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

void	grab_fork_1(t_philo *philo)
{
	ft_check_stop(philo);
	pthread_mutex_lock(philo->fork1);
	gettimeofday(&philo->tlog, NULL);

	ft_check_stop(philo);
	pthread_mutex_lock(&philo->r->print);
	print("%li Philo%i grabbed a fork.\n", philo->tlog.tv_usec, philo->index);
	pthread_mutex_unlock(&philo->r->print);

	pthread_mutex_unlock(philo->fork1);
}

void	grab_fork_2(t_philo *philo)
{
	ft_check_stop(philo);
	pthread_mutex_lock(philo->fork2);
	gettimeofday(&philo->tlog, NULL);

	ft_check_stop(philo);
	pthread_mutex_lock(&philo->r->print);
	print("%li Philo%i grabbed a fork.\n", philo->tlog.tv_usec, philo->index);
	pthread_mutex_unlock(&philo->r->print);

	pthread_mutex_unlock(philo->fork1);
	pthread_mutex_unlock(philo->fork2);
}

void	eating(t_philo *philo)
{
	ft_check_stop(philo);
	pthread_mutex_lock(&philo->r->print);
	print("%li Philo%i is eating.\n", philo->tlog.tv_usec, philo->index);
	pthread_mutex_unlock(&philo->r->print);
	usleep(philo->r->params->teat);
}

void	sleeping(t_philo *philo)
{
	ft_check_stop(philo);
	pthread_mutex_lock(&philo->r->print);
	print("%li Philo%i is sleeping.\n", philo->tlog.tv_usec, philo->index);
	pthread_mutex_unlock(&philo->r->print);
	usleep(philo->r->params->tsleep);

}

void	thinking(t_philo *philo)
{
	ft_check_stop(philo);
	pthread_mutex_lock(&philo->r->print);
	print("%li Philo%i is thinking.\n", philo->tlog.tv_usec, philo->index);
	pthread_mutex_unlock(&philo->r->print);
}
