/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:11:01 by ltressen          #+#    #+#             */
/*   Updated: 2023/05/11 10:01:38 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	no_event(void *data)
{
	(void)data;
	return (0);
}

int	key_events(int key, t_pbl *map)
{	
	if (key == XK_Escape)
		mlx_destroy_window(map->cam.mlx_ptr, map->cam.win_ptr);
	return (0);
}