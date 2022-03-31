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

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	array_has_only_digits(char *arr)
{
	int	j;

	j = 0;
	if (!arr[j])
		return (0);
	while (arr[j])
	{
		if (!ft_isdigit(arr[j]))
			return (0);
		j++;
	}
	return (1);
}

int	ft_args_pos_long(int argc, char **argv)
{
	if (ft_atol(argv[1]) < 1 || ft_atol(argv[2]) < 1
		|| ft_atol(argv[3]) < 1 || ft_atol(argv[4]) < 1)
	{
		printf("an argument has a wrong value\n");
		return (1);
	}
	if (argc == 6)
	{
		if (ft_atol(argv[5]) < 0)
		{	
			printf("last arg has a wrong value\n");
			return (1);
		}
	}
	return (0);
}

int	ft_check_args(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		printf("wrong number of args\n");
		return (1);
	}
	i = 1;
	while (i < argc)
	{
		if (!array_has_only_digits(argv[i]))
		{
			printf("an argument has a wrong value\n");
			return (1);
		}
		i++;
	}
	if (ft_args_pos_long(argc, argv))
		return (1);
	return (0);
}
