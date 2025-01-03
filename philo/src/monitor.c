/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduribei <eduribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 20:42:56 by eduribei          #+#    #+#             */
/*   Updated: 2025/01/02 21:46:56 by eduribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	ft_total_meals_are_complete(t_main *main)
{
	pthread_mutex_lock(&main->meal_mutex);
	if (main->params->total_meals_ct == main->params->total_meals_goal)
	{
		pthread_mutex_lock(&main->stop_mutex);
		main->params->must_stop = true;
		pthread_mutex_unlock(&main->stop_mutex);
		pthread_mutex_unlock(&main->meal_mutex);
		return (true);
	}
	pthread_mutex_unlock(&main->meal_mutex);
	return (false);
}

static bool	ft_philosopher_has_died(size_t index, t_main *main)
{
	t_timeval	now;
	size_t		timedelta;

	ft_get_time(&now, main->params->time_mutex);
	main->ph[index].tm_starv = ft_t_delta_us(main->ph[index].tm_lastmeal, now);
	pthread_mutex_lock(&main->stop_mutex);
	if (main->ph[index].tm_starv >= main->params->tm_die)
	{
		main->params->must_stop = true;
		timedelta = ft_t_delta_ms(main->params->start_time, now);
		pthread_mutex_lock(&main->print_mutex);
		printf("%li %li died\n", timedelta, main->ph[index].index + 1);
		pthread_mutex_unlock(&main->stop_mutex);
		pthread_mutex_unlock(&main->print_mutex);
		return (true);
	}
	pthread_mutex_unlock(&main->stop_mutex);
	return (false);
}

void	*ft_stop_monitor(void *arg)
{
	t_main		*main;
	size_t		philo_index;

	main = (t_main *)arg;
	while (1)
	{
		philo_index = 0;
		while (philo_index < main->params->nb_philos)
		{
			if (ft_philosopher_has_died(philo_index, main))
				return (NULL);
			if (ft_total_meals_are_complete(main))
				return (NULL);
			philo_index++;
		}
		usleep(2000);
	}
	return (NULL);
}
