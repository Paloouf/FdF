/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 09:19:20 by ltressen          #+#    #+#             */
/*   Updated: 2023/05/11 12:00:40 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_pbl	map;
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	map.zmax = 0;
	map.zmin = 0;
	if (argc == 2)
	{
		read_file(&map, argv[1]);
		init_all(&map);
		while (i < map.hgt)
		{	
			j = 0;
			while (j < map.wth)
				ft_printf("%d ", map.pix[i][j++].z);
			ft_printf("\n");
			i++;
		}
		print_map(&map);
	}
	return (0);
}

void	init_all(t_pbl *map)
{
	int	x;
	int	y;

	map->cam.angle_x = 45 *(M_PI / 180);
	map->cam.angle_y = 0;
	map->cam.angle_z = 35.26 * (M_PI / 180);
	map->cam.mlx_ptr = mlx_init();
	y = 0;
	//ft_printf("max %d  min %d", map->zmax, map->zmin);
	while(y < map->hgt)
	{
		x = 0;
		while(x < map->wth)
		{
			map->pix[y][x].xp = (((WIDTH / map->wth)/1.5) * x) + ((WIDTH % (map->wth)/1.5)+ ((WIDTH / map->wth) / 2)) + WIDTH/3;
			map->pix[y][x].yp = (((HEIGHT / map->hgt)/1.5) * y) + ((HEIGHT % (map->hgt)/1.5) + ((HEIGHT / map->hgt) / 2)) - HEIGHT/2;
			map->pix[y][x].zp = (((WIDTH / map->wth) + (HEIGHT / map->hgt))) * (map->pix[y][x].z*(10/(map->zmax - map->zmin)));//(((HEIGHT / map->hgt)/4)) * map->pix[y][x].z + (HEIGHT % (map->hgt)/4);
			x++;
		}
		y++;
	}
}

void	print_map(t_pbl *map)
{
	int	y;
	int	x;


	y = 0;
	x = 0;
	map->cam.win_ptr = mlx_new_window(map->cam.mlx_ptr, WIDTH, HEIGHT, "Yo Eddy");
	while(x < map->wth)
	{
		y = 0;
		while(y < map->hgt)
		{
			draw_map(map);
			y++;
		}
		x++;
	}
	mlx_loop_hook(map->cam.mlx_ptr, &no_event, &map);
	mlx_key_hook(map->cam.win_ptr, &key_events,  &map);
	mlx_loop(map->cam.mlx_ptr);
	mlx_destroy_display(map->cam.mlx_ptr);
	free(map->cam.mlx_ptr);
}