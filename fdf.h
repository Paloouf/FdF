/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:00:59 by ltressen          #+#    #+#             */
/*   Updated: 2023/05/17 14:20:09 by ltressen         ###   ########.fr       */
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

# define ZOOM_MINUS 65453
# define ZOOM_UP 65451

typedef struct s_point
{
	int	xp;
	int	yp;
	int	zp;
	int	z;
	int	color;
} t_point;

typedef struct s_cam
{
	double	angle_x;
	double	angle_y;
	double	angle_z;
	void	*mlx_ptr;
	void	*win_ptr;
} t_cam;

typedef struct s_img
{
	void	*image;
	char	*data_addr;
	int	bpp;
	int	line_len;
	int	endian;
} t_img;

typedef struct s_pbl
{
	int	wth;
	int	hgt;
	int	zmax;
	int	zmin;
	int	xmin;
	int	xmax;
	int	ymin;
	int	ymax;
	int	xD;
	int	yD;
	int	zoom;
	int	alt_z;
	int	decv;
	int	dech;
	t_point	**pix;
	t_point origin;
	t_cam	cam;
	t_img	img;
} t_pbl;

void	ft_intsplit(t_pbl *map, char *line);
void	read_file(t_pbl *map, char *name);
void	init_all(t_pbl *map);
void	draw_map(t_pbl *map);
void    draw(t_pbl *map, t_point one, t_point two);
int	key_events(int key, t_pbl *map);
t_point	projection(t_pbl *map, int x, int y);
void	aller_les_bleus(t_pbl *map);
void	re_init(t_pbl *map);
void	pxl_to_img(t_pbl *map, int x, int y, unsigned int color);
void	erase_img(t_pbl *map);
void	free_all(t_pbl *map);
void	reset(t_pbl *map);

#endif