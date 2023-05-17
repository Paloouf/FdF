/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 08:56:56 by ltressen          #+#    #+#             */
/*   Updated: 2023/05/17 16:48:18 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_map(t_pbl *map)
{
	int	x;
	int	y;

	x = 0;
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
	draw(map, projection(map, x, y), projection(map, 0, y));
	draw(map, projection(map, x, y), projection(map, x, 0));
	mlx_put_image_to_window(map->cam.mlx_ptr, map->cam.win_ptr, map->img.image, 0, 0);
}

void aller_les_bleus(t_pbl *map)
{
	t_point one;
	t_point two;
	t_point three;
	t_point zero;

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

unsigned int    color(int zone, int ztwo, int i, int total)
{
    unsigned int    code;
    double    dz;

    if (zone > ztwo && ztwo != 0)
        dz = zone / ztwo;
    if (ztwo > zone && zone != 0)
        dz = ztwo / zone;
    if (zone > ztwo && ztwo == 0)
        dz = zone * -1;
    if (zone < ztwo && zone == 0)
        dz = ztwo;
    if (zone == ztwo)
        code = 16777215 - (2500 * zone);
    else
    {
        if (total != 0)
            code = 16777215 - ((2500 * zone) + (((2500 / abs(total)) * (abs(i) * dz))));
    }
    return (code);
}


t_point	projection(t_pbl *map, int x, int y)
{
	t_point pt;

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

   	map->xD = (abs(map->xmin) + abs(WIDTH - map->xmax))/2;
   	map->yD = (abs(map->ymin) + abs(HEIGHT - map->ymax))/2;
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
            if (((one.xp + i) + map->xD + map->dech > 0 && (one.xp + i) + map->xD + map->dech < WIDTH) && (one.yp + map->yD + map->decv > 0 && one.yp + map->yD + map->decv < HEIGHT))
                            pxl_to_img(map, (one.xp + i) + map->xD + map->dech, one.yp + map->yD + map->decv , color(one.z, two.z, i, one.xp - two.xp));
                        i += 1 - (2 * (dx > 0));
                }
        }
        else if (dx == 0)
        {
                while (one.yp + i != two.yp)
                {
            if ((one.xp + map->xD + map->dech > 0 && one.xp + map->xD + map->dech < WIDTH) && (one.yp + i + map->decv + map->yD > 0 && one.yp + map->decv + i + map->yD < HEIGHT))
                            pxl_to_img(map, one.xp + map->xD + map->dech, one.yp + i + map->decv + map->yD, color(one.z, two.z, i, one.yp - two.yp));
                        i += 1 - (2 * (dy > 0));
                }
        }
        else if (abs(dy) >= abs(dx))
        {
                while (one.yp + i != two.yp)
                {
            if (((one.xp + ((double) i * a)) + map->xD + map->dech > 0 && (one.xp + ((double) i * a)) + map->dech + map->xD < WIDTH) && (one.yp + map->decv + i + map->yD > 0 && one.yp + i + map->decv + map->yD < HEIGHT))
                            pxl_to_img(map, (one.xp + ((double) i * a)) + map->xD + map->dech, one.yp + i + map->decv + map->yD, color(one.z, two.z, i, one.yp - two.yp));
                        i += 1 - (2 * (dy > 0));
                }
        }
        else if (abs(dx) > abs(dy))
        {
                while (one.xp + i != two.xp)
                {
            if (((one.xp + i) + map->xD + map->dech > 0 && (one.xp + i) + map->xD + map->dech < WIDTH) && (one.yp + ((double) i * a) + map->decv + map->yD > 0 && one.yp + ((double) i * a) + map->yD + map->decv < HEIGHT))
                           pxl_to_img(map, (one.xp + i) + map->xD + map->dech, one.yp + ((double) i * a) + map->yD + map->decv , color(one.z, two.z, i, one.xp - two.xp));
                        i += 1 - (2 * (dx > 0));
                }
        }
}                   


/* SAVED BEFORE PXL TO IMG
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
*/