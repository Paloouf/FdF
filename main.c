/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 09:19:20 by ltressen          #+#    #+#             */
/*   Updated: 2023/05/15 14:53:10 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_pbl	map;

	map.zmax = 0;
	map.zmin = 0;
	if (argc == 2)
	{	
		map.cam.mlx_ptr = mlx_init();
		map.cam.win_ptr = mlx_new_window(map.cam.mlx_ptr, WIDTH, HEIGHT, "WORK IN PROGRESS");
		read_file(&map, argv[1]);
		init_all(&map);
		draw_map(&map);
		mlx_key_hook(map.cam.win_ptr, key_events,  &map);
		mlx_loop(map.cam.mlx_ptr);
	}
	return (0);
}

void	pxl_to_img(t_pbl *map, int x, int y, unsigned int color)
{
	char	*pixel;

	pixel = map->img.data_addr + (y * map->img.line_len + x * (map->img.bpp / 8));
	*(int *)pixel = color;
}

/*	code pour print le tableau parsed;
	int	i;
	int	j;
	
	i = 0;
	j = 0;	
	while (i < map.hgt)
	{	
		j = 0;
		while (j < map.wth)
			ft_printf("%d ", map.pix[i][j++].z);
		ft_printf("\n");
		i++;
	}
*/
void	init_all(t_pbl *map)
{
	int	x;
	int	y;

	map->cam.angle_x = 45 *(M_PI / 180);
	map->cam.angle_y = 0;
	map->cam.angle_z = 35 * (M_PI / 180);
	map->zoom = 0;
	map->img.image = mlx_new_image(map->cam.mlx_ptr, WIDTH, HEIGHT);
	map->img.data_addr = mlx_get_data_addr(map->img.image, &map->img.bpp, &map->img.line_len, &map->img.endian);
	y = 0;
	while(y < map->hgt)
	{
		x = 0;
		while(x < map->wth)
		{
			map->pix[y][x].xp = x * ((1000+map->zoom)/map->wth);//(((WIDTH / map->wth)/2) * x) + ((WIDTH % (map->wth)/2)+ ((WIDTH / map->wth) / 2));
			map->pix[y][x].yp = y * ((1000+map->zoom)/map->wth);//(((HEIGHT / map->hgt)/2) * y) + ((HEIGHT % (map->hgt)/2) + ((HEIGHT / map->hgt) / 2));
			map->pix[y][x].zp = (map->pix[y][x].z * 50)/(map->zmax - map->zmin);/* + (HEIGHT % (map->hgt)/4);*/
			x++;
		}
		y++;
	}
}

void	re_init(t_pbl *map)
{
	int	x;
	int	y;

	y = 0;
	if (map->zoom > -900)
	{
		while(y < map->hgt)
		{
			x = 0;
			while(x < map->wth)
			{
				map->pix[y][x].xp = x * ((1000+map->zoom)/map->wth);//(((WIDTH / map->wth)/2) * x) + ((WIDTH % (map->wth)/2)+ ((WIDTH / map->wth) / 2));
				map->pix[y][x].yp = y * ((1000+map->zoom)/map->wth);//(((HEIGHT / map->hgt)/2) * y) + ((HEIGHT % (map->hgt)/2) + ((HEIGHT / map->hgt) / 2));
				map->pix[y][x].zp = (map->pix[y][x].z * 50)/(map->zmax - map->zmin);/* + (HEIGHT % (map->hgt)/4);*/
				x++;
			}
			y++;
		}
		erase_img(map);
		draw_map(map);
	}
}

void	erase_img(t_pbl *map)
{
	map->img.image = mlx_new_image(map->cam.mlx_ptr, WIDTH, HEIGHT);
	map->img.data_addr = mlx_get_data_addr(map->img.image, &map->img.bpp, &map->img.line_len, &map->img.endian);
}