/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:38:12 by vnafissi          #+#    #+#             */
/*   Updated: 2022/03/14 19:46:42 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

//Parsing des arguments
// 1) vérifier que 4 <= argc <= 5 ==> sinon exit
// 2) vérifier que tous les arguments >= 1 ==> sinon exit
// 3) stockage des arguments dans l'objet game
// 4) Si nb_philos = 1, le jeu s'arrête : on ne peut pas jouer avec 1 fourchette
int	ft_check_args(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	return (1);
}


//Initialisation des philos
//Création d'un tableau de philo dans la structure game,
// du rank 1 au rank number_of_philos.
// Ces philos sont représentés par des objets
int	ft_init_game_variables(t_game *game, int argc, char **argv)
{
	int	i;

	game->nb_philos = (int)ft_atol(argv[1]);
	game->time_to_die = ft_atol(argv[2]);
	game->time_to_eat = ft_atol(argv[3]);
	game->time_to_sleep = ft_atol(argv[4]);

	if (argc == 6)
		game->nb_times_philos_must_eat = (int)ft_atol(argv[5]);
	else
		game->nb_times_philos_must_eat = -1;

	//initialization philos
	game->philos = ft_calloc((unsigned int)game->nb_philos, sizeof(t_philo));
	if (!game->philos)
		return (1);
	i = 0;

	while (i < game->nb_philos)
	{
		game->philos[i].index = i + 1;
		game->philos[i].status = 2;
		game->philos[i].nb_times_eat = 0;
		game->philos[i].game = game; //chaque philo aura un pointeur qui pointera sur la mémoire de game, pour pouvoir y accéder dans ft_routine
		i++;
	}

	//initialization forks
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

void ft_start_eating(t_philo *philo)
{
	int		right_fork;
	int		left_fork;

	left_fork = philo->index - 1;
	right_fork = philo->index;
	if (philo->index == philo->game->nb_philos)
		right_fork = 0;

	//int pthread_mutex_lock(pthread_mutex_t *mutex);
	pthread_mutex_lock(&philo->game->forks[left_fork]); //in case lock fails, need to check
	pthread_mutex_lock(&philo->game->forks[right_fork]); //in case lock fails, need to check

	printf("philo %d start eating\n",philo->index);
	printf("left_fork %d\n",left_fork);
	printf("right_fork %d\n",right_fork);

	usleep(2000 * 1000);

	pthread_mutex_unlock(&philo->game->forks[left_fork]); //in case unlock fails, need to check
	pthread_mutex_unlock(&philo->game->forks[right_fork]); //in case unlock fails, need to check
}

void ft_start_sleeping(t_philo *philo)
{
	printf("philo %d start sleeping\n",philo->index);
	usleep(2000 * 1000);
}

void ft_start_thinking(t_philo *philo)
{
	printf("philo %d start thinking\n",philo->index);
	usleep(2000 * 1000);
}

void	*ft_routine(void *arg)
{
	t_philo philo;


	//Need to put in place a while loop.
	//The condition to go out of this while loop is if a philo is dead ==> put in place the other thread which tests indefinitely if a philo is dead

	philo = *(t_philo*)arg;
	if (philo.status == 2)
	{
		ft_start_eating(&philo);
	}
	else if (philo.status == 0)
	{
		ft_start_sleeping(&philo);
	}
	else if (philo.status == 1)
	{
		ft_start_thinking(&philo);
	}
	return (arg);
}

int	ft_create_threads(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->nb_philos)
	{
		//int pthread_create(pthread_t *restrict thread,const pthread_attr_t *restrict attr,void *(*start_routine)(void *),void *restrict arg);
		if (pthread_create(&game->philos[i].thread, NULL, (void*)ft_routine, (void*)&game->philos[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	ft_wait_threads(t_game *game)
{
	int	i;

	i = 0;
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
	if (!ft_check_args(argc, argv)) //à coder
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
//pour le changement d'état des philos, faire une fonction qui compte le temps (équivalent à usleep) et au bout du bon temps écoulé, change l'état du philo automatiquement

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
//GENERIQUE : philo n mange : forks n et n+1 (ou 0 si n = nb_max) sont utilisés

//séparation des cas de philos pair et impair ?

//Vérifier si un philo est mort et arrêter le jeu le cas échéant
//faire un thread à part qui tourne en permanence, dont le seul but est de checker si un philo est mort et d'appeler la fin du programme
//faire une fonction qui gère la fin de la partie : arrêt de tous les threads, free de toutes les mémoires, exit proprement (sans la fonction exit)
