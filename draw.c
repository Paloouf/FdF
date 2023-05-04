/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 08:56:56 by ltressen          #+#    #+#             */
/*   Updated: 2023/05/04 14:46:32 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_map(t_pbl *map)
{
	int	x;
	int	y;

	x = 0;
	while(x < map->wth - 1)
	{
		y = 0;
		while(y < map->hgt - 1)
		{
			draw(map, map->pix[y][x], map->pix[y + 1][x]);
			draw(map, map->pix[y][x], map->pix[y][x + 1]);
			y++;
                }
		x++;
	}
}

void    draw(t_pbl *map, t_point one, t_point two)
{
        int     dx;
        int     dy;
        int     i;

        i = 0;
        dx = one.xp - two.xp;
        dy = one.yp - two.yp;
        if (dy == 0)
        {
                while (one.xp + i != two.xp)
                {
                        mlx_pixel_put(map->cam.mlx_ptr, map->cam.win_ptr, one.xp + i, one.yp, 0xFFFFFF);
                        i += 1 - (2 * (dx > 0));
                }
        }
        if (dx == 0)
        {
                while (one.yp + i != two.yp)
                {
                        mlx_pixel_put(map->cam.mlx_ptr, map->cam.win_ptr, one.xp, one.yp + i, 0xFFFFFF);
                        i += 1 - (2 * (dx > 0));
                }
        }

}