/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:00:59 by ltressen          #+#    #+#             */
/*   Updated: 2023/05/03 15:16:38 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define HEIGHT 1080
# define WIDTH 1920
# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <math.h>

typedef struct s_point
{
	int	xp;
	int	yp;
	int	alt;
	int	color;
} t_point;

typedef struct s_cam
{
	int	angle_x;
	int	angle_y;
	void	*mlx_ptr;
	void	*win_ptr;
} t_cam;

typedef struct s_pbl
{
	int	wth;
	int	hgt;
	t_point	**pix;
	t_cam	cam;
} t_pbl;



int	deal_key(int key, void *param);
void	ft_intsplit(t_pbl *map, char *line);
void	read_file(t_pbl *map, char *name);
void	print_map(t_pbl *map);
void	init_all(t_pbl *map);

#endif