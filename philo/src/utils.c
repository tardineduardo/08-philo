/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduribei <eduribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 18:39:36 by eduribei          #+#    #+#             */
/*   Updated: 2025/01/02 12:30:03 by eduribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	int	nb;
	int	sign;

	nb = 0;
	sign = 1;
	while (*nptr == ' ' || (*nptr >= '\t' && *nptr <= '\r'))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		nb = nb * 10 + (*nptr - '0');
		nptr++;
	}
	return (nb * sign);
}

// FREE RESOURCES WHEN ONLY WHEN THREADS RETURN.
void	ft_free_resources(t_main *main)
{
	if (!main)
		return ;
	if (main->th)
		free(main->th);
	if (main->forks)
	{
		//ft pthread_mutex_destroy(...)
		free(main->forks);
	}
	if (main->ph)
		free(main->ph);
	if (main->params)
		free(main->params);
	free(main);
	return ;
}

void	ft_error(char *message, t_main *r)
{
	printf("Error: %s", message);
	ft_free_resources(r);
	exit(1);
}

int	ft_update_meal_count(t_philos *philo, t_params *params)
{
	pthread_mutex_lock(params->meal_mutex);
	philo->nb_meals_had += 1;
	params->total_meals_ct += 1;
	pthread_mutex_unlock(params->meal_mutex);
	if (philo->nb_meals_had == params->nb_meals_to_eat)
	{
		pthread_mutex_lock(params->print_mutex);
		printf(BLUE "--- %li had all %li meals! \n" RESET, philo->index + 1, params->nb_meals_to_eat);
		pthread_mutex_unlock(params->print_mutex);
		return (5);
	}
	return (0);
}
