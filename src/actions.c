/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduribei <eduribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 16:09:51 by eduribei          #+#    #+#             */
/*   Updated: 2024/12/30 21:52:26 by eduribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	philo_grab_fork_1(t_philo *philo)
{
	ft_check_stop(philo);
	pthread_mutex_lock(philo->fork1);
	gettimeofday(&philo->tlog, NULL);

	ft_check_stop(philo);
	pthread_mutex_lock(philo->r->printm);
	printf("%li %li has taken a fork\n", philo->tlog.tv_usec, philo->index);
	pthread_mutex_unlock(philo->r->printm);

}

bool	philo_grab_fork_2(t_philo *philo)
{
	ft_check_stop(philo);  // SE MORREU, SOLTAR OS GARFOS
	pthread_mutex_lock(philo->fork2);
	gettimeofday(&philo->tlog, NULL);

	ft_check_stop(philo);
	pthread_mutex_lock(philo->r->printm);
	printf("%li %li has taken a fork\n", philo->tlog.tv_usec, philo->index);
	pthread_mutex_unlock(philo->r->printm);


}

bool	philo_eating(t_philo *philo)
{
	ft_check_stop(philo); // SE MORREU, SOLTAR OS GARFOS
	pthread_mutex_lock(philo->r->printm); 
	printf("%li %li is eating\n", philo->tlog.tv_usec, philo->index);
	pthread_mutex_unlock(philo->r->printm);
	usleep(philo->r->params->teat);
	pthread_mutex_unlock(philo->fork2); // CHECAR ORDEM
	pthread_mutex_unlock(philo->fork1);

}

bool	philo_sleeping(t_philo *philo)
{
	ft_check_stop(philo);
	pthread_mutex_lock(philo->r->printm);
	printf("%li %li is sleeping\n", philo->tlog.tv_usec, philo->index);
	pthread_mutex_unlock(philo->r->printm);
	usleep(philo->r->params->tsleep);

}

bool	philo_thinking(t_philo *philo)
{
	ft_check_stop(philo);
	pthread_mutex_lock(philo->r->printm);
	printf("%li %li is thinking\n", philo->tlog.tv_usec, philo->index);
	pthread_mutex_unlock(philo->r->printm);
	// ESPERAR UMA MERREQUINHA 
}
