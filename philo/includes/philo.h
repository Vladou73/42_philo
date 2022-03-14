/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:38:31 by vnafissi          #+#    #+#             */
/*   Updated: 2022/03/14 17:18:54 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <pthread.h>


// status 0 = eat, 1 = sleep, 2 = think
typedef struct s_philo
{
	int			index;
	int			status;
	int			nb_times_eat;
	pthread_t	thread;
}	t_philo;

typedef struct s_game
{
	int				nb_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				nb_times_philos_must_eat;
	t_philo			*philos;
	pthread_mutex_t	*forks;
}	t_game;

# define RED_CROSS	17

//******************** MEMORY ********************//
void	*ft_calloc(size_t n, size_t size);
void	ft_bzero(void *ptr, size_t n);





//******************** PARSING ********************//
long int	ft_atol(const char *src);

int		ft_map_is_ok(char **map, int nb_rows, int nb_cols);
char	*ft_read_map(char *str_map, char *filename);
int		ft_count_elements(char **map, int nb_rows);
int		ft_map_is_rectangle(char **map, int nb_cols);
int		ft_map_is_ok(char **map, int nb_rows, int nb_cols);
int		ft_is_wall(char c);
int		ft_char_is_ok(char c);
int		ft_map_chars_are_ok(char **map, int nb_rows, int nb_cols);
int		ft_check_args(int argc, char **argv);

//******************** HANDLE MOVES ********************//
void	handle_key_up(t_game *game);
void	handle_key_down(t_game *game);
void	handle_key_left(t_game *game);
void	handle_key_right(t_game *game);

//******************** HANDLE EXIT ********************//
int		ft_no_more_collectibles(t_game *game);
int		clear_program(t_game *game);
void	ft_check_exit(t_game *game);

//******************** USE MINILIBIX ********************//
void	use_minilibx(t_game *game);
void	init_mlx(t_game *game);

//******************** MAIN FUNCTIONS ********************//
void	update_window(t_game *game);
void	*ft_chose_img(t_game *game, char c);
void	ft_update_put_moves(t_game *game);

#endif
