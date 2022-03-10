/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:38:12 by vnafissi          #+#    #+#             */
/*   Updated: 2022/03/10 16:36:47 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

int	ft_check_args(int argc, char **argv)
{
	int	len;

	if (argc != 2)
		return (0);
	len = (int)ft_strlen(argv[1]);
	if (len < 4)
		return (0);
	if (argv[1][len - 1] != 'r' || argv[1][len - 2] != 'e'
		|| argv[1][len - 3] != 'b' || argv[1][len - 4] != '.')
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	game;

}

//Parsing des arguments
// 1) vérifier que 4 <= argc <= 5 ==> sinon exit
// 2) vérifier que tous les arguments >= 1 ==> sinon exit
// 3) stockage des arguments dans l'objet game
// 4) Si nb_philos = 1, le jeu s'arrête : on ne peut pas jouer avec 1 fourchette

//Initialisation des philos
//Création d'un tableau de philo dans la structure game,
// du rank 1 au rank number_of_philos.
// Ces philos sont représentés par des objets
//Chaque philo doit également etre représenté par un thread : double boucle pour initialiser le thread et attendre qu'il s'arrête

//Passage des philos d'un état à l'autre
//pour le changement d'état des philos, faire une fonction qui compte le temps (équivalent à usleep) et au bout du bon temps écoulé, change l'état du philo automatiquement

//Initialisation des forks
// il faut un tableau de forks dans la structure game
// les forks doivent être des mutex

// blocage des forks lorsqu'un philo l'utilise
// il faut pouvoir lier le tableau de forks et de philos qui les utilise
// philos : [0, 1, 2, 3, 4]
// forks: [0, 1, 2, 3, 4]
//philo 0 mange : forks 0 et 1 sont utilisés
//philo 1 mange : forks 1 et 2 sont utilisés
//philo 2 mange : forks 2 et 3 sont utilisés
//philo 3 mange : forks 3 et 4 sont utilisés
//philo 4 mange : forks 4 et 5 sont utilisés
//GENERIQUE : philo n mange : forks n et n+1 (ou 0 si n = nb_max) sont utilisés

//séparation des cas de philos pair et impair ?

//Vérifier si un philo est mort et arrêter le jeu le cas échéant
//faire un thread à part qui tourne en permanence, dont le seul but est de checker si un philo est mort et d'appeler la fin du programme
//faire une fonction qui gère la fin de la partie : arrêt de tous les threads, free de toutes les mémoires, exit proprement (sans la fonction exit)
