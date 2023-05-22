/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:11:01 by ltressen          #+#    #+#             */
/*   Updated: 2023/05/22 11:09:27 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_all(t_pbl *map)
{
	int	y;

	if (map->img.image)
		mlx_destroy_image(map->cam.mlx_ptr, map->img.image);
	if (map->pix)
	{
		y = 0;
		while (y < map->hgt)
		{
			free(map->pix[y]);
			y++;
		}
		free(map->pix);
	}
	if (map->cam.mlx_ptr)
	{
		mlx_destroy_window(map->cam.mlx_ptr, map->cam.win_ptr);
		mlx_destroy_display(map->cam.mlx_ptr);
		free(map->cam.mlx_ptr);
	}
}

int	key_events(int key, t_pbl *map)
{	
	if (key == XK_Escape)
	{
		free_all(map);
		exit(EXIT_SUCCESS);
	}
	if (key == ZOOM_UP)
		map->zoom += 100;
	if (key == ZOOM_MINUS && map->zoom > -900)
		map->zoom -= 100;
	if (key == XK_q)
		map->cam.angle_x -= 5 * (M_PI / 180);
	if (key == XK_e)
		map->cam.angle_x += 5 * (M_PI / 180);
	if (key == XK_r)
		map->cam.angle_z -= 5 * (M_PI / 180);
	if (key == XK_f)
		map->cam.angle_z += 5 * (M_PI / 180);
	if (key == XK_t)
		map->alt_z += 30;
	if (key == XK_g && map->alt_z > 0)
		map->alt_z -= 30;
	translate(key, map);
	re_init(map);
	return (0);
}

int	translate(int key, t_pbl *map)
{
	if (key == XK_w)
		map->decv -= 20;
	if (key == XK_s)
		map->decv += 20;
	if (key == XK_a)
		map->dech -= 20;
	if (key == XK_d)
		map->dech += 20;
	if (key == XK_x)
		reset(map);
	if (key == XK_v)
		set_dim(map);
	if (key == XK_b)
		set_tri(map);
	return (1);
}

void	set_dim(t_pbl *map)
{
	map->cam.angle_x = 0.7853982;
	map->cam.angle_z = 0.4636467;
}

void	set_tri(t_pbl *map)
{
	map->cam.angle_x = 1.047198;
	map->cam.angle_z = 0.4642576;
}
