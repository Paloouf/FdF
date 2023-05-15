/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:11:01 by ltressen          #+#    #+#             */
/*   Updated: 2023/05/15 14:53:46 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	no_event(void *data)
{
	(void)data;
	ft_printf("X");
	return (0);
}

int	key_events(int key, t_pbl *map)
{	
	if (key == XK_Escape)
		mlx_destroy_window(map->cam.mlx_ptr, map->cam.win_ptr);
	//ft_printf("%d", key);
	if (key == ZOOM_UP)
	{
		map->zoom += 100;
		re_init(map);
	}
	if (key == ZOOM_MINUS)
	{
		if (map->zoom > -900)
		{
			map->zoom -= 100;
			re_init(map);
		}
	}
	if (key == XK_q)
	{
		if (map->cam.angle_x > 0)
		{
			map->cam.angle_x -= 5 * (M_PI / 180);
			re_init(map);
		}
	}
	if (key == XK_e)
	{
		map->cam.angle_x += 5 * (M_PI / 180);
		re_init(map);
	}
	if (key == XK_r)
	{
		if (map->cam.angle_z > 0)
		{
			map->cam.angle_z -= 5 * (M_PI / 180);
			re_init(map);
		}
	}
	if (key == XK_f)
	{
		map->cam.angle_z += 5 * (M_PI / 180);
		re_init(map);
	}
	return (0);
}