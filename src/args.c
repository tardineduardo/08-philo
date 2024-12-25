/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduribei <eduribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 18:57:12 by eduribei          #+#    #+#             */
/*   Updated: 2024/12/25 19:12:28 by eduribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_validate_args(int argc, char *argv[])
{

	(void)argv;
	if (argc != 4 && argc != 5)
	{
		printf("Invalid arguments.\n");
		exit(1);
	}
}
