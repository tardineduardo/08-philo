/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduribei <eduribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 20:42:56 by eduribei          #+#    #+#             */
/*   Updated: 2025/01/01 21:37:08 by eduribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*death_monitor(void *arg)
{
	t_resources  *r;
	size_t	   t_since_last_meal;
	size_t	   timedelta;
	size_t	   i;

	r = (t_resources *)arg;
	while (1)
	{
		i = 0;
		while (i < r->params->number_of_philos)
		{
			pthread_mutex_lock(r->meal_mutex);
			gettimeofday(&r->philo[i].curr_time, NULL);
			t_since_last_meal = ft_t_delta_us(r->philo[i].t_of_last_meal, r->philo[i].curr_time);
			pthread_mutex_unlock(r->meal_mutex);
			pthread_mutex_lock(r->stop_mutex);
			if (t_since_last_meal >= r->params->time_to_die)
			{
				r->params->is_someone_dead = true;
				gettimeofday(&r->philo[i].curr_time, NULL);
				timedelta = ft_t_delta_ms(r->params->start_time, r->philo[i].curr_time);
				pthread_mutex_lock(r->print_mutex);
				printf("%li %li died\n", timedelta, r->philo[i].index + 1);
				pthread_mutex_unlock(r->print_mutex);
				pthread_mutex_unlock(r->stop_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(r->stop_mutex);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
