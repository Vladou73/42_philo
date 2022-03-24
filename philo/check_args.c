/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 12:13:05 by vnafissi          #+#    #+#             */
/*   Updated: 2022/03/17 12:30:08 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

//Parsing des arguments
// 1) vérifier que 5 <= argc <= 6 ==> sinon exit
// 2) vérifier que tous les arguments >= 1 ==> sinon exit
// 3) stockage des arguments dans l'objet game
// 4) Si nb_philos = 1, le jeu s'arrête : on ne peut pas jouer avec 1 fourchette
int	ft_check_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("wrong number of args");
		return (1);
	}
	if (atol(argv[1]) < 2 || atol(argv[2]) < 1 || atol(argv[3]) < 1 || atol(argv[4]) < 1)
	{
		printf("an argument has a wrong value");
		return (1);
	}
	if (argc == 6)
	{
		if (atol(argv[5]) < 1)
		{	
			printf("last arg has a wrong value");
			return (1);
		}
	}
	return (0);
}
