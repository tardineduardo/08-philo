/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduribei <eduribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 15:01:18 by eduribei          #+#    #+#             */
/*   Updated: 2024/12/25 21:35:40 by eduribei         ###   ########.fr       */
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



void *ft_philosopher(void *args)
{

	printf("");

}

int	main(int argc, char *argv[])
{
	t_resources	*r;

	//ft_validate_args(argc, argv);
	r = malloc(sizeof(t_resources));
	r->mutex = malloc(ft_atoi(argv[1]) * sizeof(pthread_t));
	r->th = malloc(ft_atoi(argv[1]) * sizeof(pthread_t));
	r->time = malloc(sizeof(t_time));

	gettimeofday(r->time, NULL);
	printf("sec = %li, usec = %li\n", r->time->tv_sec, r->time->tv_usec);
}
