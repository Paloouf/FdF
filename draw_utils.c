/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:52:11 by ltressen          #+#    #+#             */
/*   Updated: 2023/05/18 16:47:58 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	last_lines(t_pbl *map, int y, int x)
{
	while (y > 0)
	{
		draw(map, projection(map, map->wth - 1, y - 1),
			projection(map, map->wth - 1, y));
		y--;
	}
	while (x > 0)
	{
		draw(map, projection(map, x - 1, map->hgt - 1),
			projection(map, x, map->hgt - 1));
		x--;
	}
}

void	pxl_one(t_pbl *map, t_point one, t_point two, int dx)
{
	int	i;

	i = 0;
	while (one.xp + i != two.xp)
	{
		if (((one.xp + i) + map->xd + map->dech > 0 && (one.xp + i)
				+ map->xd + map->dech < WIDTH)
			&& (one.yp + map->yd + map->decv > 0
				&& one.yp + map->yd + map->decv < HEIGHT))
			pxl_to_img(map, (one.xp + i) + map->xd + map->dech,
				one.yp + map->yd + map->decv,
				color(one, two, i, one.xp - two.xp));
		i += 1 - (2 * (dx > 0));
	}
}

void	pxl_two(t_pbl *map, t_point one, t_point two, int dy)
{
	int	i;

	i = 0;
	while (one.yp + i != two.yp)
	{
		if ((one.xp + map->xd + map->dech > 0 && one.xp
				+ map->xd + map->dech < WIDTH)
			&& (one.yp + i + map->decv + map->yd > 0
				&& one.yp + map->decv + i + map->yd < HEIGHT))
			pxl_to_img(map, one.xp + map->xd + map->dech,
				one.yp + i + map->decv + map->yd,
				color(one, two, i, one.yp - two.yp));
		i += 1 - (2 * (dy > 0));
	}
}

void	pxl_three(t_pbl *map, t_point one, t_point two, int dy)
{
	int		i;
	int		dx;
	double	a;

	i = 0;
	dx = one.xp - two.xp;
	dy = one.yp - two.yp;
	if (abs(dx) >= abs(dy))
		a = (double) dy / (double) dx;
	else
		a = (double) dx / (double) dy;
	while (one.yp + i != two.yp)
	{
		if (((one.xp + ((double) i * a)) + map->xd + map->dech > 0
				&& (one.xp + ((double) i * a)) + map->dech
				+ map->xd < WIDTH)
			&& (one.yp + map->decv + i + map->yd > 0
				&& one.yp + i + map->decv + map->yd < HEIGHT))
			pxl_to_img(map, (one.xp + ((double) i * a)) + map->xd
				+ map->dech, one.yp + i + map->decv + map->yd,
				color(one, two, i, one.yp - two.yp));
		i += 1 - (2 * (dy > 0));
	}
}

void	pxl_four(t_pbl *map, t_point one, t_point two, int dx)
{
	int		i;
	int		dy;
	double	a;

	i = 0;
	dx = one.xp - two.xp;
	dy = one.yp - two.yp;
	if (abs(dx) >= abs(dy))
		a = (double) dy / (double) dx;
	else
		a = (double) dx / (double) dy;
	while (one.xp + i != two.xp)
	{
		if (((one.xp + i) + map->xd + map->dech > 0
				&& (one.xp + i) + map->xd + map->dech < WIDTH)
			&& (one.yp + ((double) i * a) + map->decv + map->yd > 0
				&& one.yp + ((double) i * a) + map->yd
				+ map->decv < HEIGHT))
			pxl_to_img(map, (one.xp + i) + map->xd + map->dech,
				one.yp + ((double) i * a) + map->yd + map->decv,
				color(one, two, i, one.xp - two.xp));
		i += 1 - (2 * (dx > 0));
	}
}
