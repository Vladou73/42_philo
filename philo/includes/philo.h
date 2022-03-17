/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:38:31 by vnafissi          #+#    #+#             */
/*   Updated: 2022/03/17 13:37:19 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <pthread.h>
#include <sys/time.h>

// status 0 = eat, 1 = sleep, 2 = think
typedef struct s_philo
{
	int				index;
	int				status;
	int				nb_times_eat;
	long			last_time_ate;
	int				left_fork;
	int				right_fork;
	pthread_t		thread;
	struct s_game	*game;
}	t_philo;

typedef struct s_game
{
	int				nb_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			time_to_think;
	int				nb_times_philos_must_eat;
	struct timeval	current_time;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_t		dead_thread;
}	t_game;

//******************** PARSING ********************//
long int	ft_atol(const char *src);
int			ft_check_args(int argc, char **argv);

//******************** INIT VARIABLES ********************//
int		ft_init_game_variables(t_game *game, int argc, char **argv);
int		ft_init_forks(t_game *game);
int		ft_init_philos(t_game *game);
void	ft_init_parsed_variables(t_game *game, int argc, char **argv);

//******************** MEMORY ********************//
void	*ft_calloc(size_t n, size_t size);
void	ft_bzero(void *ptr, size_t n);

//******************** ROUTINE & ACTIONS ********************//
void	*ft_routine(void *arg);
void	*ft_dead_routine(void *arg);
void 	ft_start_thinking(t_philo *philo);
void	ft_start_sleeping(t_philo *philo);
void	ft_start_eating(t_philo *philo);

//******************** HANDLE EXIT ********************//
int		clear_program(t_game *game);
void	ft_check_exit(t_game *game);

#endif
