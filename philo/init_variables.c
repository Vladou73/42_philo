/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_variables.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 21:35:08 by vnafissi          #+#    #+#             */
/*   Updated: 2022/03/21 17:57:16 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

void	ft_init_parsed_variables(t_game *game, int argc, char **argv)
{
	game->start_time = ft_gettimeofday_ms();
	game->nb_philos = (int)ft_atol(argv[1]);
	game->time_to_die = ft_atol(argv[2]);
	game->time_to_eat = ft_atol(argv[3]);
	game->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		game->nb_times_philos_must_eat = (int)ft_atol(argv[5]);
	else
		game->nb_times_philos_must_eat = -1;
	game->dead_philo = 0;
}

int	ft_init_philos(t_game *game)
{
	int	i;

	game->philos = ft_calloc((unsigned int)game->nb_philos, sizeof(t_philo));
	if (!game->philos)
		return (1);
	i = 0;
	while (i < game->nb_philos)
	{
		game->philos[i].index = i + 1;
		game->philos[i].nb_times_eat = 0;
		game->philos[i].last_meal = ft_gettimeofday_ms();
		game->philos[i].left_fork = game->philos[i].index - 1;
		game->philos[i].right_fork = game->philos[i].index;
		if (game->philos[i].index == game->nb_philos)
			game->philos[i].right_fork = 0;
		if (pthread_mutex_init(&game->philos[i].lock_philo, NULL) != 0)
			return (1);
		if (pthread_mutex_init(&game->lock_death, NULL) != 0)
			return (1);
		game->philos[i].game = game;
		i++;
	}
	return (0);
}

int	ft_init_forks(t_game *game)
{
	int	i;

	game->forks = ft_calloc(
			(unsigned int)game->nb_philos, sizeof(pthread_mutex_t));
	if (!game->forks)
		return (1);
	i = 0;
	while (i < game->nb_philos)
	{
		if (pthread_mutex_init(&(game->forks[i]), NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	ft_init_game_variables(t_game *game, int argc, char **argv)
{
	ft_init_parsed_variables(game, argc, argv);
	if (ft_init_philos(game))
		return (1);
	if (ft_init_forks(game))
		return (1);
	return (0);
}
