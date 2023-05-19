/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:14:39 by ltressen          #+#    #+#             */
/*   Updated: 2023/05/19 13:28:04 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	reset(t_pbl *map)
{
	map->cam.angle_x = 45 * (M_PI / 180);
	map->cam.angle_z = 35 * (M_PI / 180);
	map->zoom = 0;
	map->alt_z = 0;
	map->decv = 0;
	map->dech = 0;
	re_init(map);
}

void	re_init(t_pbl *map)
{
	int	x;
	int	y;

	y = 0;
	if (map->zoom > -900)
	{
		while (y < map->hgt)
		{
			x = 0;
			while (x < map->wth)
			{
				map->pix[y][x].xp = x * (1000 + map->zoom) / (map->wth);
				map->pix[y][x].yp = y * (1000 + map->zoom) / (map->hgt);
				map->pix[y][x].zp = (map->pix[y][x].z * ((50
						+ (map->alt_z) + ((1000 + map->zoom)/ 2)))
				/ (map->zmax - map->zmin));
				x++;
			}
			y++;
		}
		erase_img(map);
		draw_map(map);
	}
}
/*				map->pix[y][x].zp = (map->pix[y][x].z * ((50
							+ (map->alt_z) + ((1000 + map->zoom) / 2)))
					/ (map->zmax - map->zmin));
*/
void	erase_img(t_pbl *map)
{
	if (map->img.image)
		mlx_destroy_image(map->cam.mlx_ptr, map->img.image);
	map->img.image = mlx_new_image(map->cam.mlx_ptr, WIDTH, HEIGHT);
	map->img.data_addr = mlx_get_data_addr(map->img.image,
			&map->img.bpp, &map->img.line_len, &map->img.endian);
}
