/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 11:11:30 by vnafissi          #+#    #+#             */
/*   Updated: 2022/02/24 11:12:26 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/so_long.h"

int	ft_is_wall(char c)
{
	if (c == '1')
		return (1);
	return (0);
}

int	ft_char_is_ok(char c)
{
	if (c == '1' || c == '0' || c == 'C' || c == 'E' || c == 'P')
		return (1);
	return (0);
}

// Uniquement 5 caractères acceptés : 0, 1, C, E, P
// La carte doit être fermée en étant encadrée par des murs.
int	ft_map_chars_are_ok(char **map, int nb_rows, int nb_cols)
{
	int	i;
	int	j;

	i = 0;
	while (i < nb_rows)
	{
		j = 0;
		while (map[i][j])
		{
			if (i == 0 || i == nb_rows || j == 0 || j == nb_cols - 1)
			{
				if (!ft_is_wall(map[i][j]))
					return (0);
			}
			else
			{
				if (!ft_char_is_ok(map[i][j]))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
