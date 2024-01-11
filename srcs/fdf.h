/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 22:24:11 by dshatilo          #+#    #+#             */
/*   Updated: 2024/01/11 17:49:38 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../lib/libft/libft.h"

# include <math.h>
# include <fcntl.h>
# include <limits.h>
#include <stdio.h>
# include "../lib/MLX42/include/MLX42/MLX42.h"

typedef struct s_map
{
	int	**field;
	int	**colors;
	int	size_x;
	int	size_y;
}	t_map;

t_map	*reader(char *filename);
int		open_close_file(char *mode, char *filename, int fd);
char	*read_file(char *filename);
t_list	*create_list(char *file_content);
void	do_nothing(void *arg);
size_t	convert_lines_to_int_arrays(t_list **all_lines);
void	convert_lines_to_strings_arrays(t_list **all_lines);
void	clear_tlist_mixed(t_list **list, t_list *switch_point,
			void (*f1)(void *), void (*f2)(void *));
void	free_2d_array(void *ptr);
size_t	check_arrays_len(t_list **all_lines);
void	strings_arrays_to_int_color_arrays(t_list **all_lines, size_t len);
int		check_color(char *arg, int *num);
int		**list_to_colors(t_list **list, t_map *map, size_t	size_y);
int		**list_to_field(t_list **list, t_map *map, size_t	size_y);
t_map	*list_to_map(t_list **list, size_t size_x);

//drawer

typedef struct s_tp
{
	int			angle;
	double		cosine;
	double		sine;
	double		zoom;
	int			shift_x;
	int			shift_y;

	mlx_t		*mlx;
	mlx_image_t	*img;
	t_map		*map;
}	t_tp;


typedef struct s_pix_pair
{
	double	x;
	double	y;
	double	x1;
	double	y1;
	int		color;
	int		color1;
}	t_pix_pair;


void	drawer(t_map *map);
void	tp_initialise(t_tp *tp);
void	draw_img(t_tp tp);
void	put_img(t_tp tp);
void	put_lines(t_tp tp, int i, int j);

#endif
