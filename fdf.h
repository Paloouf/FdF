/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:00:59 by ltressen          #+#    #+#             */
/*   Updated: 2023/05/10 17:28:32 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define HEIGHT 1080
# define WIDTH 1920
# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>

typedef struct s_point
{
	int	xp;
	int	yp;
	int	zp;
	int	z;
	int	color;
} t_point;

typedef struct s_matrix
{
	double *x;
	double *y;
	double *z;
} t_matrix;

typedef struct s_cam
{
	double	angle_x;
	double	angle_y;
	double	angle_z;
	void	*mlx_ptr;
	void	*win_ptr;
} t_cam;

typedef struct s_pbl
{
	int	wth;
	int	hgt;
	t_point	**pix;
	t_cam	cam;
	t_matrix rotate;
	t_matrix angle;
} t_pbl;



int	deal_key(int key, void *param);
void	ft_intsplit(t_pbl *map, char *line);
void	read_file(t_pbl *map, char *name);
void	print_map(t_pbl *map);
void	init_all(t_pbl *map);
void	draw_map(t_pbl *map);
void    draw(t_pbl *map, t_point one, t_point two);
int	key_events(int key, t_pbl *map);
int	no_event(void *data);
t_point	projection(t_pbl *map, int x, int y);
t_point	projection_rotate(t_pbl *map, t_point pix);
t_point	projection_angle(t_pbl *map, t_point pix);

#endif