/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduribei <eduribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 20:42:56 by eduribei          #+#    #+#             */
/*   Updated: 2025/01/02 12:08:10 by eduribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*stop_monitor(void *arg)
{
	t_main		*main;
	size_t		timedelta;
	size_t		i;
	t_timeval	now;

	main = (t_main *)arg;
	while (1)
	{
		i = 0;
		while (i < main->params->nb_philos)
		{
			gettimeofday(&now, NULL);
			main->ph[i].tm_starv = ft_t_delta_us(main->ph[i].tm_lastmeal, now);
			pthread_mutex_lock(&main->stop_mutex);
			if (main->ph[i].tm_starv >= main->params->tm_die)
			{
				main->params->must_stop = true;
				timedelta = ft_t_delta_ms(main->params->start_time, now);
				pthread_mutex_lock(&main->print_mutex);
				printf("%li %li died\n", timedelta, main->ph[i].index + 1);
				pthread_mutex_unlock(&main->print_mutex);
				pthread_mutex_unlock(&main->stop_mutex);
				pthread_detach(main->monitor);
				return (NULL);
			}
			pthread_mutex_unlock(&main->stop_mutex);
			pthread_mutex_lock(&main->meal_mutex);
			if (main->params->total_meals_ct == main->params->total_meals_goal)
			{
				pthread_mutex_lock(&main->print_mutex);
				printf(RED "everyone ate!\n" RESET);
				pthread_mutex_unlock(&main->print_mutex);
				pthread_mutex_lock(&main->stop_mutex);
				main->params->must_stop = true;
				pthread_mutex_unlock(&main->stop_mutex);
				pthread_mutex_unlock(&main->meal_mutex);
				pthread_detach(main->monitor);
				return (NULL);
			}
			pthread_mutex_unlock(&main->meal_mutex);
			i++;
		}
		usleep(1000);
	}
}
