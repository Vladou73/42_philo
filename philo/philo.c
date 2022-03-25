/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:38:12 by vnafissi          #+#    #+#             */
/*   Updated: 2022/03/21 17:50:13 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

int	ft_create_threads(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->nb_philos)
	{
		if (pthread_create(&game->philos[i].thread, NULL, (void*)ft_routine, (void*)&(game->philos[i])) != 0)
			return (1);
		i++;
	}
	if (pthread_create(&game->dead_thread, NULL, (void*)ft_dead_routine, (void*)game) != 0)
		return (1);

	return (0);
}

int	ft_wait_threads(t_game *game)
{
	int	i;

	i = 0;
	if (pthread_join(game->dead_thread, NULL) != 0)
		return (1);
	while (i < game->nb_philos)
	{
		if (pthread_join(game->philos[i].thread, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;
	
	if (ft_check_args(argc, argv))
		return (1);
	if (ft_init_game_variables(&game, argc, argv) == 1)
	{
		ft_exit(&game);
		return (1);
	}
	if (ft_create_threads(&game) == 1)
	{
		ft_exit(&game);
		return (1);
	}
	if (ft_wait_threads(&game) == 1)
	{
		ft_exit(&game);
		return (1);
	}
	return (0);
}