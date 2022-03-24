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
		printf("thread %d launched\n", i);
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

	printf("nb_philos=%d\n\n", game.nb_philos);

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

//Chaque philo doit également etre représenté par un thread : double boucle pour initialiser le thread et attendre qu'il s'arrête

//Passage des philos d'un état à l'autre
//pour le changement d'état des philos, faire une fonction qui compte le temps (équivalent à ft_usleep) et au bout du bon temps écoulé, change l'état du philo automatiquement

//Initialisation des forks
// il faut un tableau de forks dans la structure game
// les forks doivent être des mutex

// blocage des forks lorsqu'un philo l'utilise
// il faut pouvoir lier le tableau de forks et de philos qui les utilise
// philos : [1, 2, 3, 4, 5]
// forks: [0, 1, 2, 3, 4]
//philo 1 mange : forks 0 et 1 sont utilisés
//philo 2 mange : forks 1 et 2 sont utilisés
//philo 3 mange : forks 2 et 3 sont utilisés
//philo 4 mange : forks 3 et 4 sont utilisés
//philo 5 mange : forks 4 et 0 sont utilisés
//à 5 :
//--- les philos 1 et 3 peuvent manger en même temps
//--- les philos 2 et 4 peuvent manger en même temps
//--- les philos 3 et 5 peuvent manger en même temps

//GENERIQUE : philo n mange : forks n et n+1 (ou 0 si n = nb_max) sont utilisés

// philos : [1, 2, 3]
// forks: [0, 1, 2]
//philo 1 mange : forks 0 et 1 sont utilisés
//philo 2 mange : forks 1 et 2 sont utilisés
//philo 3 mange : forks 2 et 0 sont utilisés
//à 1, 2 ou 3 les philos doivent manger l'un après l'autre : ils se bloquent tous mutuellement


// philos : [1, 2, 3, 4]
// forks: [0, 1, 2, 3]
//philo 1 mange : forks 0 et 1 sont utilisés
//philo 2 mange : forks 1 et 2 sont utilisés
//philo 3 mange : forks 2 et 3 sont utilisés
//philo 4 mange : forks 3 et 0 sont utilisés
//à 4 :
//--- les philos 1 et 3 peuvent manger en même temps
//--- les philos 2 et 4 peuvent manger en même temps

// philos : [1, 2, 3, 4, 5, 6]
// forks: [0, 1, 2, 3, 4, 5]
//philo 1 mange : forks 0 et 1 sont utilisés
//philo 2 mange : forks 1 et 2 sont utilisés
//philo 3 mange : forks 2 et 3 sont utilisés
//philo 4 mange : forks 3 et 4 sont utilisés
//philo 5 mange : forks 4 et 5 sont utilisés
//philo 6 mange : forks 5 et 0 sont utilisés
//à 6 :
//--- les philos 1 - 3 - 5 peuvent manger en même temps
//--- les philos 2 - 4 - 6 peuvent manger en même temps

// philos : [1, 2, 3, 4, 5, 6, 7]
// forks: [0, 1, 2, 3, 4, 5, 6]
//philo 1 mange : forks 0 et 1 sont utilisés
//philo 2 mange : forks 1 et 2 sont utilisés
//philo 3 mange : forks 2 et 3 sont utilisés
//philo 4 mange : forks 3 et 4 sont utilisés
//philo 5 mange : forks 4 et 5 sont utilisés
//philo 6 mange : forks 5 et 6 sont utilisés
//philo 7 mange : forks 6 et 0 sont utilisés
//à 7 :
//--- les philos 1 - 3 - 5 ou 1 - 3 - 6 peuvent manger en même temps
//--- les philos 2 - 4 - 6 ou 2 - 4 - 7 peuvent manger en même temps
//--- les philos 3 - 5 - 7 peuvent manger en même temps


//séparation des cas de philos pair et impair ?
//GENERIQUE : philo n mange : forks n et n+1 (ou 0 si n = nb_max) sont utilisés
//Si nb_philos%2==0, au max nb_philos/2 peuvent manger en même temps (tous les philos pair mangent d'un coup, tous les philos impairs mangent d'un coup)
//	Dans ce cas-là on peut set le time_to_think quasiment à 0 puisque les philos alternent entre manger / dormir.
//Si nb_philos%2==1, au max (nb_philos - 1)/2 peuvent manger en même temps. Il faut faire 3 rounds pour se nourir :le time to think doit prendre compte de cela


//COMMENT SET TIME_TO_THINK

// philos  [1, 2, 3, 4]
// forks [0, 1, 2, 3]
// time_to_eat = 2000
// time_to_sleep = 1000
// time_to_think = ?
//philos 1 et 3 commencent à manger : ils mettent time_to_eat avant de passer au statut sleep
//après time_to_eat, les philos 2 et 4 peuvent commencer à manger ==> time_to_think >= time_to_eat
//les philos 1 et 3 passent time_to_sleep en train de dormir. parallèlement les philos 2 et 4 mangent pendant time_to_eat.
//CAS 1 : Si  time_to_eat < time_to_sleep : les philos 2 et 4 finissent de manger et passent à time_to_sleep. Les forks sont dispo pour que les philos 1 et 3 passent directement de sleeping à eating
	//Si on set time_to_think = time_to_sleep - time_to_eat ça semble pas mal
//CAS 2 : Si time_to_eat > time_to_sleep : il faut que time_to_think = time_to_eat - time_to_sleep



//Autre manière de faire pour éviter les deadlocks?
//ne pas set de time_to_think spécifique.
//Une fois que le philo n a fini de dormir:
//	-> on check les statuts de n-1 et n+1. Si les deux ont fini de manger, go ils mangent
//	-> quand le philo n a fini de manger, on check les statuts de n-1 et n+1. Si leur statut est thinking, on les passe en manger







//FIN DE LA GAME : Vérifier si un philo est mort et arrêter le jeu le cas échéant
//faire un thread à part qui tourne en permanence, dont le seul but est de checker si un philo est mort et d'appeler la fin du programme
//faire une fonction qui gère la fin de la partie : arrêt de tous les threads, free de toutes les mémoires, exit proprement (sans la fonction exit)
