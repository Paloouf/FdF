/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 08:56:56 by ltressen          #+#    #+#             */
/*   Updated: 2023/05/12 19:49:03 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_map(t_pbl *map)
{
	int	x;
	int	y;


	x = 0;
	ft_printf("xD\n");
	aller_les_bleus(map);
	while(x < map->wth - 1)
	{
		y = 0;
		while(y < map->hgt - 1)
		{
			draw(map, projection(map, x, y), projection(map, x, y + 1));
			draw(map, projection(map, x, y), projection(map, x+1, y));
			y++;		
                }
		x++;
	}
	ft_printf("WTF\n");

}

void aller_les_bleus(t_pbl *map)
{
	t_point one;
	t_point two;
	t_point three;
	t_point zero;

	ft_printf("YOLO\n");
	one = projection(map, 0, 0);
	ft_printf("YOLO2\n");
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
/*
t_point	projection_rotate(t_pbl *map, t_point pix)
{
	//matrice de rotation
	pix.xp = pix.xp * (cos(map->cam.angle_x)) + pix.yp * (-sin(map->cam.angle_x)) + pix.zp * 0;
	pix.yp = pix.xp * (sin(map->cam.angle_x)) + pix.yp * (cos(map->cam.angle_x)) + pix.zp * 0;
	pix.zp = pix.xp * 0 + pix.yp * 0 + pix.zp * 1;
	return(pix);
}

t_point	projection_angle(t_pbl *map, t_point pix)
{
	//matrice de rotation d'angle
	pix.xp= pix.xp * 1 + pix.yp * 0 + pix.zp * 0;
	pix.yp= pix.xp * 0 + pix.yp * (cos(map->cam.angle_z)) + pix.zp * (-sin(map->cam.angle_z));
	pix.zp= pix.xp * 0 + pix.yp * (sin(map->cam.angle_z)) + pix.zp * (cos(map->cam.angle_z));
	return(pix);
}*/
unsigned int    color(int zone, int ztwo, int i, int total)
{
        unsigned int    code;
        int     dz;

        (void)ztwo;
        (void)i;
       // ft_printf("%d\n", total);
        dz = zone - ztwo;
        if (zone == ztwo)
                code = 16777215 - (2500 * zone);
        else
        {       
                if (total != 0)         
                        code = 16777215 - ((2500 * zone) + ((2500 / total) * (i * (1 - ((dz < 0 ) * 2)))));
        }
        return (code);
}


t_point	projection(t_pbl *map, int x, int y)
{
	t_point pt;

	//ft_printf("%d\n", map->pix[y][x].z);
	pt.xp = (map->pix[y][x].xp) * cos(map->cam.angle_x) + map->pix[y][x].yp * (-sin(map->cam.angle_x)) + map->pix[y][x].zp * 0;
	pt.yp = (map->pix[y][x].xp)* (sin(map->cam.angle_x)*cos(map->cam.angle_z)) + map->pix[y][x].yp * (cos(map->cam.angle_x) * cos(map->cam.angle_z)) + map->pix[y][x].zp * (-sin(map->cam.angle_z));//resultat de matrice de proj iso;
	pt.zp = (map->pix[y][x].xp)* (sin(map->cam.angle_x) * sin(map->cam.angle_z)) + map->pix[y][x].yp * (cos(map->cam.angle_x) * sin(map->cam.angle_z)) + map->pix[y][x].zp * cos(map->cam.angle_z);
	pt.z= map->pix[y][x].z;
	return(pt);
}

void    draw(t_pbl *map, t_point one, t_point two)
{
        int     dx;
        int     dy;
        int     i;
        double  a;

	map->xD = (map->xmin + (WIDTH - map->xmax));
	map->yD = (map->ymin + (HEIGHT - map->ymax))/2;
        i = 0;
        dx = one.xp - two.xp;
        dy = one.yp - two.yp;
	if (abs(dx) >= abs(dy))
                a = (double) dy / (double) dx;
        else
                a = (double) dx / (double) dy;
	if (dy == 0)
        {
                while (one.xp + i != two.xp)
                {
                        mlx_pixel_put(map->cam.mlx_ptr, map->cam.win_ptr, (one.xp + i) + map->xD, one.yp + map->yD, color(one.z, two.z, i, one.xp - two.xp));
                        i += 1 - (2 * (dx > 0));
                }
        }
        else if (dx == 0)
        {
                while (one.yp + i != two.yp)
                {
                        mlx_pixel_put(map->cam.mlx_ptr, map->cam.win_ptr, one.xp + map->xD, one.yp + i + map->yD, color(one.z, two.z, i, one.yp - two.yp));
                        i += 1 - (2 * (dy > 0));
                }
        }
        else if (abs(dy) >= abs(dx))
        {
                while (one.yp + i != two.yp)
                {
                        mlx_pixel_put(map->cam.mlx_ptr, map->cam.win_ptr, (one.xp + ((double) i * a)) + map->xD, one.yp + i + map->yD, color(one.z, two.z, i, one.yp - two.yp));
                        i += 1 - (2 * (dy > 0));
                }
        }
        else if (abs(dx) > abs(dy))
        {
                while (one.xp + i != two.xp)
                {
                    mlx_pixel_put(map->cam.mlx_ptr, map->cam.win_ptr, (one.xp + i) + map->xD, one.yp + ((double) i * a) + map->yD, color(one.z, two.z, i, one.xp - two.yp));
                    i += 1 - (2 * (dx > 0));
                }
        }
}                    
