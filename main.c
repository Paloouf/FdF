/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 09:19:20 by ltressen          #+#    #+#             */
/*   Updated: 2023/05/18 15:05:54 by ltressen         ###   ########.fr       */
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
		map.cam.win_ptr = mlx_new_window(map.cam.mlx_ptr,
				WIDTH, HEIGHT, "WORK IN PROGRESS");
		read_file(&map, argv[1]);
		init_all(&map);
		draw_map(&map);
		mlx_key_hook(map.cam.win_ptr, key_events, &map);
		mlx_hook(map.cam.win_ptr, 17, 0L, close_cross, &map);
		mlx_loop(map.cam.mlx_ptr);
		mlx_destroy_display(map.cam.mlx_ptr);
		free(map.cam.mlx_ptr);
	}
	return (0);
}

int	close_cross(t_pbl *map)
{
	free_all(map);
	exit(EXIT_SUCCESS);
	return (0);
}

void	pxl_to_img(t_pbl *map, int x, int y, unsigned int color)
{
	char	*pixel;

	pixel = map->img.data_addr
		+ (y * map->img.line_len + x * (map->img.bpp / 8));
	*(int *)pixel = color;
}

void	init_all(t_pbl *map)
{
	int	x;
	int	y;

	init_map(map);
	y = 0;
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
}

void	init_map(t_pbl *map)
{
	map->cam.angle_x = 45 *(M_PI / 180);
	map->cam.angle_z = 35 * (M_PI / 180);
	map->zoom = 0;
	map->alt_z = 0;
	map->decv = 0;
	map->dech = 0;
	map->img.image = mlx_new_image(map->cam.mlx_ptr, WIDTH, HEIGHT);
	map->img.data_addr = mlx_get_data_addr(map->img.image,
			&map->img.bpp, &map->img.line_len, &map->img.endian);
}
