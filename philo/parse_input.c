/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 11:02:21 by vnafissi          #+#    #+#             */
/*   Updated: 2022/03/09 17:23:39 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/so_long.h"

char	*ft_read_map(char *str_map, char *filename)
{
	int	len_file;
	int	fd;

	fd = open(filename, O_RDONLY);
	len_file = (int)read(fd, str_map, 100000);
	if (len_file == -1)
	{
		ft_putstr_fd("Error\n", 1);
		exit(1);
	}
	str_map[len_file] = 0;
	close(fd);
	return (str_map);
}

// C pour un item à ramasser (c pour collectible),
// E pour une sortie,
// P pour la position de départ du personnage.
int	ft_count_elements(char **map, int nb_rows)
{
	int	exit;
	int	item;
	int	start;
	int	i;

	exit = 0;
	item = 0;
	start = 0;
	while (nb_rows)
	{
		i = 0;
		while (map[nb_rows - 1][i])
		{
			if (map[nb_rows - 1][i] == 'C')
				item++;
			if (map[nb_rows - 1][i] == 'E')
				exit++;
			if (map[nb_rows - 1][i++] == 'P')
				start++;
		}
		nb_rows--;
	}
	if (exit != 1 || item < 1 || start != 1)
		return (0);
	return (1);
}

// La carte doit être de forme rectangulaire.
int	ft_map_is_rectangle(char **map, int nb_cols)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if ((int)ft_strlen(map[i]) != nb_cols)
			return (0);
		i++;
	}
	return (1);
}

int	ft_map_is_ok(char **map, int nb_rows, int nb_cols)
{
	if (!ft_map_chars_are_ok(map, nb_rows, nb_cols))
		return (0);
	if (!ft_map_is_rectangle(map, nb_cols))
		return (0);
	if (!ft_count_elements(map, nb_rows))
		return (0);
	return (1);
}
