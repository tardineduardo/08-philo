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

bool	ft_stop(t_philos *philo, t_params *params)
{
	printf(YELLOW "philo %li is checking a stop.\n" RESET, philo->index);
	pthread_mutex_lock(params->stop_mutex);
	if (params->is_someone_dead)
	{
	pthread_mutex_unlock(params->stop_mutex);
		printf(RED "philo %li confirmed that someone died.\n" RESET, philo->index);
		return (true);
	}
	gettimeofday(&philo->curr_time, NULL);
	printf(YELLOW "philo %li now is %li, main start was %li, diff is %li.\n" RESET, philo->index, philo->curr_time.tv_usec/1000, philo->time_of_last_meal.tv_usec/1000, philo->curr_time.tv_usec/1000 - philo->time_of_last_meal.tv_usec/1000);
	if (philo->curr_time.tv_usec - philo->time_of_last_meal.tv_usec >=  params->time_to_die)
	{
		printf(RED "philo %li confirmed it died.\n" RESET, philo->index);
		pthread_mutex_unlock(params->stop_mutex);
		return (true);
	}
	pthread_mutex_unlock(params->stop_mutex);
	printf(GREEN "philo %li got ok to go.\n" RESET, philo->index);
	return (false);
}

void	*ft_philo(void *args)
{
	t_philos		*philo;
	t_params	*params;

	philo = (t_philos *)args;
	params = philo->main->params;

	printf("Hello from philosopher %li.\n", philo->index);
	while (1)
	{
		if (!philo_grab_fork_1(philo, params))
			return (NULL);
		if (!philo_grab_fork_2(philo, params))
			return (NULL);
		if (!philo_eating(philo, params))
			return (NULL);
		if (!philo_sleeping(philo, params))
			return (NULL);
		if (!philo_thinking(philo, params))
			return (NULL);
	}
	printf(BLUE "philo %li is done.\n" RESET, philo->index);
	return (NULL);
}

void	ft_join_threads(t_resources *main)
{
	int	i;

	i = 0;
	while (i < main->params->number_of_philos)
	{
		if (!main->philo[i].is_detached)
			pthread_join(main->th[i], NULL);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_resources		*main;

	main = malloc(sizeof(t_resources));
	if (!main)
		ft_error("malloc failed.\n", main);
	ft_validate_args(argc, argv, main);
	ft_alloc_resources(main);
	ft_init_mutexes(main);
	ft_init_threads(main);
	ft_join_threads(main);
	ft_free_resources(main);
}
