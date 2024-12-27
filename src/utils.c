/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduribei <eduribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 18:39:36 by eduribei          #+#    #+#             */
/*   Updated: 2024/12/25 22:04:25 by eduribei         ###   ########.fr       */
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

void	ft_alloc_resources(t_resources *r)
{
	r->forks = calloc(r->params->nforks, sizeof(pthread_mutex_t));
	r->th = calloc(r->params->nphilos, sizeof(pthread_t));
	r->philo = calloc(r->params->nphilos, sizeof(t_philo));
	r->stop = calloc(1, sizeof(pthread_mutex_t));
	r->chrono = calloc(1, sizeof(t_chrono));
	if (!r->forks || !r->th || !r->philo || !r->chrono)
	{
		printf("malloc error.\n");
		ft_free_resources(r);
		exit(1);
	}
	return ;
}


void	ft_free_resources(t_resources *r)
{




}

void	ft_free_resources(t_resources *r)
{
	if (!r)
		return ;
	if (r->th[0])
	{
		pthread_mutex_lock(r->stop); ////////////////// Complete this!!!!!!!
		r->params->stop = true;
		pthread_mutex_unlock(r->stop);
	}
	if (r->th)
		free(r->th);
	if (r->forks)
		free(r->forks);
	if (r->philo)
		free(r->philo);
	if (r->chrono)
		free(r->chrono);
	if (r->params)
		free(r->params);
	free(r);
	return ;
}

void	ft_error(char *message, t_resources *r)
{
	printf("Error: %s", message);
	ft_free_resources(r);
	exit(1);
}