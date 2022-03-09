/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 18:03:55 by vnafissi          #+#    #+#             */
/*   Updated: 2022/02/24 19:16:48 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/so_long.h"

int	ft_no_more_collectibles(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->nb_rows)
	{
		j = 0;
		while (j < game->nb_cols)
		{
			if (game->map[i][j] == 'C')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	ft_free_null_ptr(char **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

int	clear_program(t_game *game)
{
	int	i;

	if (game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	i = 0;
	if (game->map)
	{
		while (game->map[i])
		{
			ft_free_null_ptr(&(game->map[i]));
			i++;
		}		
		free(game->map);
	}
	if (game->mlx_ptr)
		free(game->mlx_ptr);
	exit(0);
}

void	ft_check_exit(t_game *game)
{
	if (game->exit_pos[0] == game->player_pos[0]
		&& game->exit_pos[1] == game->player_pos[1]
		&& ft_no_more_collectibles(game))
		clear_program(game);
}
