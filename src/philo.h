/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduribei <eduribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 15:01:25 by eduribei          #+#    #+#             */
/*   Updated: 2025/01/01 17:45:23 by eduribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <limits.h>

typedef struct timeval	timeval;

typedef struct s_params
{
	size_t			number_of_philos;
	size_t			nb_of_forks;
	size_t			time_sleeping;
	size_t			time_to_die;
	size_t			time_eating;
	size_t			number_of_meals_to_eat;
	timeval			start_time;
	bool			stop;
	bool			is_someone_dead;
	pthread_mutex_t	*stop_mutex;
	pthread_mutex_t	*print_mutex;
}	t_params;

typedef struct s_philos
{
	size_t				index;
	pthread_mutex_t		*fork1;
	pthread_mutex_t		*fork2;
	size_t				number_of_meals_had;
	timeval				t_of_last_meal;
	timeval				curr_time;
	struct s_resources	*main;
}	t_philos;

typedef struct s_resources
{
	pthread_t		*th;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*stop_mutex;
	pthread_mutex_t	*print_mutex;
	t_philos		*philo;
	t_params		*params;
}	t_resources;

//Validation
int		ft_atoi(const char *nptr);
void	ft_validate_args(int argc, char *argv[], t_resources *main);

//Inits
void	ft_init_threads(t_resources *main);
void	ft_init_mutexes(t_resources *main);
void	ft_alloc_resources(t_resources *main);

//Philosopher
void	*ft_philo(void *args);

//Actions
bool	philo_grab_fork_1(t_philos *philo, t_params *params);
bool	philo_grab_fork_2(t_philos *philo, t_params *params);
bool	philo_eating(t_philos *philo, t_params *params);
bool	philo_sleeping(t_philos *philo, t_params *params);
bool	philo_thinking(t_philos *philo, t_params *params);

//exiting
bool	ft_stop(t_philos *philo, t_params *params);
void	ft_stop_all_threads(t_resources *main);
void	ft_join_threads(t_resources *main);
void	ft_free_resources(t_resources *main);

//Error
void	ft_error(char *message, t_resources *main);

size_t	ft_t_delta_ms(timeval start, timeval end);
size_t	ft_t_delta_us(timeval start, timeval end);


# define RESET   "\033[0m"
# define RED     "\033[31m"
# define GREY	"\033[90m"
# define GREEN   "\033[32m"
# define YELLOW  "\033[33m"
# define BLUE    "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN    "\033[36m"
# define WHITE   "\033[37m"
# define BRIGHT_GREEN "\033[92m"


#endif
