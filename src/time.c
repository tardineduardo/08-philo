/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduribei <eduribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 20:48:56 by eduribei          #+#    #+#             */
/*   Updated: 2025/01/01 20:49:14 by eduribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_t_delta_ms(timeval start, timeval end)
{
	ssize_t	seconds;
	ssize_t	microseconds;

	seconds = end.tv_sec - start.tv_sec;
	microseconds = end.tv_usec - start.tv_usec;
	if (microseconds < 0)
	{
		seconds -= 1;
		microseconds += 1000000;
	}
	return (seconds * 1000 + microseconds / 1000);
}

size_t	ft_t_delta_us(timeval start, timeval end)
{
	ssize_t	seconds;
	ssize_t	microseconds;

	seconds = end.tv_sec - start.tv_sec;
	microseconds = end.tv_usec - start.tv_usec;
	if (microseconds < 0)
	{
		seconds -= 1;
		microseconds += 1000000;
	}
	return (seconds * 1000000 + microseconds);
}
