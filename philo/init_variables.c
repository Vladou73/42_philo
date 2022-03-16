/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_variables.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 21:35:08 by vnafissi          #+#    #+#             */
/*   Updated: 2022/03/16 21:53:01 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"


void	ft_init_parsed_variables(t_game *game, int argc, char **argv)
{
	game->nb_philos = (int)ft_atol(argv[1]);
	game->time_to_die = ft_atol(argv[2]);
	game->time_to_eat = ft_atol(argv[3]);
	game->time_to_sleep = ft_atol(argv[4]);
	if (game->time_to_eat > game->time_to_sleep)
		game->time_to_think = game->time_to_eat - game->time_to_sleep + 500;
	else
		game->time_to_think = game->time_to_sleep - game->time_to_eat + 500;

	if (argc == 6)
		game->nb_times_philos_must_eat = (int)ft_atol(argv[5]);
	else
		game->nb_times_philos_must_eat = -1;
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
		if (game->philos[i].index % 2 == 1) //les philos au nombre impair commencent à manger
			game->philos[i].status = 2;
		else
		{
			if (game->time_to_eat > game->time_to_sleep)
				game->philos[i].status = 0;
			else
				game->philos[i].status = 1;
		}
		game->philos[i].nb_times_eat = 0;
		game->philos[i].left_fork = game->philos[i].index - 1;
		game->philos[i].right_fork = game->philos[i].index;

		if (game->philos[i].index == game->nb_philos)
			game->philos[i].right_fork = 0;
		game->philos[i].game = game; //chaque philo aura un pointeur qui pointera sur la mémoire de game, pour pouvoir y accéder dans ft_routine
		i++;
	}
	return (0);
}

int	ft_init_forks(t_game *game)
{
	int	i;

	game->forks = ft_calloc((unsigned int)game->nb_philos, sizeof(pthread_mutex_t));
	if (!game->forks)
		return (1);
	i = 0;
	while (i < game->nb_philos)
	{
		//int pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr);
		if (pthread_mutex_init(&(game->forks[i]), NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

//Initialisation des philos
//Création d'un tableau de philo dans la structure game,
// du rank 1 au rank number_of_philos.
// Ces philos sont représentés par des objets
int	ft_init_game_variables(t_game *game, int argc, char **argv)
{
	ft_init_parsed_variables(game, argc, argv);
	if (ft_init_philos(game))
		return (1);
	if (ft_init_forks(game))
		return (1);
	return (0);
}
