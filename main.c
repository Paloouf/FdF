/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 09:19:20 by ltressen          #+#    #+#             */
/*   Updated: 2023/05/12 20:10:04 by ltressen         ###   ########.fr       */
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
	ft_printf("PAS MORT\n");
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
		ft_printf("TOUJOURS PAS\n");
		draw_map(map);
	}
}
