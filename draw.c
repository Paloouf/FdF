/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 08:56:56 by ltressen          #+#    #+#             */
/*   Updated: 2023/05/19 10:30:24 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_map(t_pbl *map)
{
	int	x;
	int	y;

	x = 0;
	aller_les_bleus(map);
	while (x < map->wth - 1)
	{
		y = 0;
		while (y < map->hgt - 1)
		{
			draw(map, projection(map, x, y), projection(map, x, y + 1));
			draw(map, projection(map, x, y), projection(map, x + 1, y));
			y++;
		}
		x++;
	}
	last_lines(map, y, x);
	mlx_put_image_to_window(map->cam.mlx_ptr, map->cam.win_ptr,
		map->img.image, 0, 0);
}

void	aller_les_bleus(t_pbl *map)
{
	t_point	one;
	t_point	two;
	t_point	three;
	t_point	zero;

	one = projection(map, 0, 0);
	two = projection(map, 0, map->hgt - 1);
	three = projection(map, map->wth - 1, 0);
	zero = projection(map, map->wth - 1, map->hgt - 1);
	if (one.xp < two.xp)
	{
		map->xmin = one.xp;
		map->xmax = zero.xp;
		map->ymin = three.yp;
		map->ymax = two.yp;
	}
	else
	{
		map->xmin = two.xp;
		map->xmax = three.xp;
		map->ymin = one.yp;
		map->ymax = zero.yp;
	}
}

unsigned int	color(t_point one, t_point two, int i, int total)
{
	unsigned int	code;
	double	dz;
	static int	flag = 0;

	if (one.colorflag)
		flag = 1;
	if (flag == 1)
	{
		if (one.color)
			return (one.color);
		else
			return (16777215);
	}
	if (one.z > two.z && two.z != 0)
		dz = one.z / two.z;
	if (two.z > one.z && one.z != 0)
		dz = two.z / one.z;
	if (one.z > two.z && two.z == 0)
		dz = one.z * -1;
	if (one.z < two.z && one.z == 0)
		dz = two.z;
	if (one.z == two.z)
		code = 16777215 - (2500 * one.z);
	else
	{
		if (total != 0)
			code = 16777215 - ((2500 * one.z) + (((2500 / abs(total)) * (abs(i) * dz))));
	}
	return (code);
}

t_point	projection(t_pbl *map, int x, int y)
{
	t_point	pt;

	pt.xp = (map->pix[y][x].xp) * cos(map->cam.angle_x)
		+ map->pix[y][x].yp * (-sin(map->cam.angle_x)) + map->pix[y][x].zp * 0;
	pt.yp = (map->pix[y][x].xp) * (sin(map->cam.angle_x)
			* cos(map->cam.angle_z))
		+ map->pix[y][x].yp * (cos(map->cam.angle_x) * cos(map->cam.angle_z))
		+ map->pix[y][x].zp * (-sin(map->cam.angle_z));
	pt.zp = (map->pix[y][x].xp) * (sin(map->cam.angle_x)
			* sin(map->cam.angle_z))
		+ map->pix[y][x].yp * (cos(map->cam.angle_x) * sin(map->cam.angle_z))
		+ map->pix[y][x].zp * cos(map->cam.angle_z);
	pt.z = map->pix[y][x].z;
	if (map->pix[y][x].colorflag)
		pt.color = map->pix[y][x].color;
	pt.colorflag = map->pix[y][x].colorflag;
	return (pt);
}

void	draw(t_pbl *map, t_point one, t_point two)
{
	int		dx;
	int		dy;

	map->xd = (abs(map->xmin) + abs(WIDTH - map->xmax)) / 2;
	map->yd = (abs(map->ymin) + abs(HEIGHT - map->ymax)) / 2;
	dx = one.xp - two.xp;
	dy = one.yp - two.yp;
	if (dy == 0)
		pxl_one(map, one, two, dx);
	else if (dx == 0)
		pxl_two(map, one, two, dy);
	else if (abs(dy) >= abs(dx))
		pxl_three(map, one, two, dy);
	else if (abs(dx) > abs(dy))
		pxl_four(map, one, two, dx);
}
