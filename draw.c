/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 08:56:56 by ltressen          #+#    #+#             */
/*   Updated: 2023/05/10 18:24:13 by ltressen         ###   ########.fr       */
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
			draw(map, projection(map, x, y), projection(map, x, y + 1));
			draw(map, projection(map, x, y), projection(map, x+1, y));
			y++;		
                }
		x++;
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

t_point	projection(t_pbl *map, int x, int y)
{
	t_point pt;

	pt.xp = (map->pix[y][x].xp - WIDTH/2) * cos(map->cam.angle_x) + map->pix[y][x].yp * (-sin(map->cam.angle_x)) + map->pix[y][x].zp * 0;//resultat de matrice de proj iso; 
	pt.yp = (map->pix[y][x].xp - WIDTH/2)* (sin(map->cam.angle_x)*cos(map->cam.angle_z)) + map->pix[y][x].yp * (cos(map->cam.angle_x) * cos(map->cam.angle_z)) + map->pix[y][x].zp * (-sin(map->cam.angle_z));//resultat de matrice de proj iso;
	pt.zp = (map->pix[y][x].xp - WIDTH/2)* (sin(map->cam.angle_x) * sin(map->cam.angle_z)) + map->pix[y][x].yp * (cos(map->cam.angle_x) * sin(map->cam.angle_z)) + map->pix[y][x].zp * cos(map->cam.angle_z);
	//pt.color = get_color(pt.zp);
	return(pt);
}

void    draw(t_pbl *map, t_point one, t_point two)
{
        int     dx;
        int     dy;
       // double  x;
      //  double  y;
        int     i;
        double  a;

        i = 0;
        dx = one.xp - two.xp;
        dy = one.yp - two.yp;
	//x = one.xp * cos(map->cam.angle_x) + one.yp * cos(map->cam.angle_x + 2.0944) + one.zp * cos(map->cam.angle_x - 2.0944);
       // y = one.xp * sin(map->cam.angle_x) + one.yp * sin(map->cam.angle_x + 2.0944) + one.zp * sin(map->cam.angle_x - 2.0944);
	if (abs(dx) >= abs(dy))
                a = (double) dy / (double) dx;
        else
                a = (double) dx / (double) dy;
        if (dy == 0)
        {
                while (one.xp + i != two.xp)
                {
                        mlx_pixel_put(map->cam.mlx_ptr, map->cam.win_ptr, one.xp + i, one.yp, 0xFFFFFF);
                        i += 1 - (2 * (dx > 0));
                }
        }
        else if (dx == 0)
        {
                while (one.yp + i != two.yp)
                {
                        mlx_pixel_put(map->cam.mlx_ptr, map->cam.win_ptr, one.xp, one.yp + i, 0xFFFFFF);
                        i += 1 - (2 * (dy > 0));
                }
        }
        else if (abs(dy) >= abs(dx))
        {
//        ft_printf("dy > dx | dx : %d, dy : %d\n,xp 1 = %d, xp 2 = %d, yp 1 = %d, yp 2 = %d \n",dx, dy, one.xp, two.xp, one.yp, two.yp);
                while (one.yp + i != two.yp)
                {
                	mlx_pixel_put(map->cam.mlx_ptr, map->cam.win_ptr, one.xp + ((double) i * a), one.yp + i, 0xFFFFFF);
                	i += 1 - (2 * (dy > 0));
                }       
        }
        else if (abs(dx) > abs(dy))
        {
//        ft_printf("dx > dy | dx : %d, dy :%d\n xp 1 = %d, xp 2 = %d, yp 1 = %d, yp 2 = %d \n",dx, dy, one.xp, two.xp, one.yp, two.yp);
                while (one.xp + i != two.xp)
                {
                    mlx_pixel_put(map->cam.mlx_ptr, map->cam.win_ptr, one.xp + i, one.yp + ((double) i * a), 0xFFFFFF);
                    i += 1 - (2 * (dx > 0));
                }
        }
}                    
