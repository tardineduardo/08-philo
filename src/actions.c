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

bool	philo_grab_fork_1(t_philos *philo, t_params *params)
{
	if (ft_stop(philo, params))
		return (false);
	pthread_mutex_lock(philo->fork1);
	gettimeofday(&philo->curr_time, NULL);
	if (ft_stop(philo, params))
	{
		pthread_mutex_unlock(philo->fork1);
		return (false);
	}
	pthread_mutex_lock(params->print_mutex);
	printf("%li %li has taken a fork\n", philo->curr_time.tv_usec / 1000, philo->index);
	pthread_mutex_unlock(params->print_mutex);
	return (true);
}

bool	philo_grab_fork_2(t_philos *philo, t_params *params)
{
	if (ft_stop(philo, params))
	{
		pthread_mutex_unlock(philo->fork1);
		return (false);
	}
	pthread_mutex_lock(philo->fork2);
	gettimeofday(&philo->curr_time, NULL);
	if (ft_stop(philo, params))
	{
		pthread_mutex_unlock(philo->fork1);
		pthread_mutex_unlock(philo->fork2);
		return (false);
	}
	pthread_mutex_lock(params->print_mutex);
	printf("%li %li has taken a fork\n", philo->curr_time.tv_usec / 1000, philo->index);
	pthread_mutex_unlock(params->print_mutex);
	return (true);
}

bool	philo_eating(t_philos *philo, t_params *params)
{
	if (ft_stop(philo, params))
	{
		pthread_mutex_unlock(philo->fork2);
		pthread_mutex_unlock(philo->fork1);
		return (false);
	}

	gettimeofday(&philo->time_of_last_meal, NULL);
	pthread_mutex_lock(params->print_mutex); 
	printf("%li %li is eating\n", philo->curr_time.tv_usec / 1000, philo->index);
	pthread_mutex_unlock(params->print_mutex);
	//MAYBE CHECK STOP HERE AS WELL

	gettimeofday(&philo->time_of_last_meal, NULL);
	usleep(params->time_eating);
	pthread_mutex_unlock(philo->fork1);
	pthread_mutex_unlock(philo->fork2);
	philo->number_of_meals_had += 1;
	printf("philo %li just had %li of %li meals\n", philo->index, philo->number_of_meals_had, params->number_of_meals_to_eat);
	if (philo->number_of_meals_had == params->number_of_meals_to_eat)
		return (false);
	return (true);
}

bool	philo_sleeping(t_philos *philo, t_params *params)
{
	if (ft_stop(philo, params))
		return (false);
	gettimeofday(&philo->time_of_last_meal, NULL);
	pthread_mutex_lock(params->print_mutex);
	printf("%li %li is sleeping\n", philo->curr_time.tv_usec / 1000, philo->index);
	pthread_mutex_unlock(params->print_mutex);
	//HE CANT SLEEP IF HE IS GOING TO DIE
	usleep(params->time_sleeping);
	return (true);
}

bool	philo_thinking(t_philos *philo, t_params *params)
{
	if (ft_stop(philo, params))
		return (false);
	gettimeofday(&philo->curr_time, NULL);
	pthread_mutex_lock(params->print_mutex);
	printf("%li %li is thinking\n", philo->curr_time.tv_usec / 1000, philo->index);
	pthread_mutex_unlock(params->print_mutex);
	// "ESPERAR UMA MERREQUINHA" (by danbarbo)
	// Aqui, thinking poderia ser algum processo, que eu pudesse
	// interromper a qualquer momento, mas eu não sei como dar KILL
	// em uma thread.
	return (true);
}
