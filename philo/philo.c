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

//Voir si la gestion du cas nb_philos = 1 est bon ou pas. Ou si faut faire tourner la simu et laisser mourir le philo

int	ft_create_threads(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->nb_philos) //threads representing philos
	{
		if (pthread_create(&game->philos[i].thread, NULL, (void*)ft_routine, (void*)&(game->philos[i])) != 0)
			return (1);
		i++;
	}
	//thread to check if a philo is dead
	if (pthread_create(&game->dead_thread, NULL, (void*)ft_dead_routine, (void*)game) != 0)
		return (1);

	return (0);
}

int	ft_wait_threads(t_game *game)
{
	int	i;

	i = 0;
	//thread to check if a philo is dead
	if (pthread_join(game->dead_thread, NULL) != 0)
		return (1);
	while (i < game->nb_philos)
	{
		//int pthread_join(pthread_t thread, void **retval);
		if (pthread_join(game->philos[i].thread, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}


int	main(int argc, char **argv)
{
	t_game	game;
	
	if (ft_check_args(argc, argv)) //à coder
	{
		//ft_exit(); //à coder
		return (1);
	}
	if (ft_init_game_variables(&game, argc, argv) == 1)
	{
		//ft_exit(); //à coder
		return (1);
	}

	if (ft_create_threads(&game) == 1)
	{
		//ft_exit(); //à coder
		return (1);
	}


	if (ft_wait_threads(&game) == 1)
	{
		//ft_exit(); //à coder
		return (1);
	}
	return (0);
}

//FIN DE LA GAME : Vérifier si un philo est mort et arrêter le jeu le cas échéant
//faire un thread à part qui tourne en permanence, dont le seul but est de checker si un philo est mort et d'appeler la fin du programme
//faire une fonction qui gère la fin de la partie : arrêt de tous les threads, free de toutes les mémoires, exit proprement (sans la fonction exit)
