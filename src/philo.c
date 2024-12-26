/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduribei <eduribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 15:01:18 by eduribei          #+#    #+#             */
/*   Updated: 2024/12/25 22:37:42 by eduribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(void)
{

}

void	sleep(void)
{

}

void	think(void)
{

}



void	ft_philosopher(void *args)
{
	t_philo	*data;

	data = (t_philo *)args;
	printf("Hello from philosopher %i.\n", data->r->philo->index);

}

int	main(int argc, char *argv[])
{
	int			i;
	t_resources	*r;

	//ft_validate_args(argc, argv);
	r = malloc(sizeof(t_resources));
	
	//create separate funtion to init all this.
	r->mutex = malloc(ft_atoi(argv[1]) * sizeof(pthread_mutex_t));
	r->th = malloc(ft_atoi(argv[1]) * sizeof(pthread_t));
	r->philo = malloc(ft_atoi(argv[1]) * sizeof(t_philo));
	r->timers = malloc(ft_atoi(argv[1]) * sizeof(t_timers));
	r->chrono = malloc(sizeof(t_chrono));

	i = 0;
	while (i < argv[1])
	{
		r->philo->index = i + 0;
		r->philo->r = r;
		pthread_create(r->th[i], NULL, ft_philosopher, (void *)&r->philo[i]);
		i++;
	}
	i = 0;
	while (i < argv[1])
	{
		pthread_join(r->th[i], NULL);
		i++;
	}
	gettimeofday(r->chrono, NULL);
	printf("sec = %li, usec = %li\n", r->chrono->tv_sec, r->chrono->tv_usec);
}
