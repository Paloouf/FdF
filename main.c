/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 09:19:20 by ltressen          #+#    #+#             */
/*   Updated: 2023/05/10 18:11:49 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*int	deal_key(int key, void *param)
{
	(void)key;
	(void)param;
	static int	x = 0;
	static int	y = 0;
	if (key == 'w')
		y--;
	if (key == 's')
		y++;
	if (key == 'a')
		x--;
	if (key == 'd')
		x++;
	//mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0xFFFFFF);
	return (0);
}*/

int	main(int argc, char **argv)
{
	t_pbl	map;
	int	i;
	int	j;
	
	i = 0;
	j = 0;
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
		//ft_printf("ptdr");
		print_map(&map);
		
	}
	return (0);

}

void	init_all(t_pbl *map)
{
	int	x;
	int	y;

	map->cam.angle_x = 15 *(M_PI / 180);
	map->cam.angle_y = 0;
	map->cam.angle_z = 35.26 * (M_PI / 180);
	map->cam.mlx_ptr = mlx_init();
	
	y = 0;

	//ft_printf("%d \t %d \n", map->wth, map->hgt);
	while(y < map->hgt)
	{
		//ft_printf("\n %d \n", y);
		x = 0;
		while(x < map->wth)
		{
			//ft_printf("%d ", x);
			map->pix[y][x].xp = ((WIDTH / map->wth) * x) + ((WIDTH % (map->wth)/2)+ ((WIDTH / map->wth) / 2));
			map->pix[y][x].yp = ((HEIGHT / map->hgt) * y) + ((HEIGHT % (map->hgt)/2) + ((HEIGHT / map->hgt) / 2));
			map->pix[y][x].zp = ((HEIGHT / map->hgt) * map->pix[y][x].z) + (HEIGHT % (map->hgt)/2);
			x++;
		}
		y++;
	}
	//lol = map->wth / 2;
	//mdr = map->hgt / 2;
}

void	print_map(t_pbl *map)
{
	int	y;
	int	x;


	y = 0;
	x = 0;
	map->cam.win_ptr = mlx_new_window(map->cam.mlx_ptr, WIDTH, HEIGHT, "Push Swap c'est cringe");
	while(x < map->wth)
	{
		y = 0;
		while(y < map->hgt)
		{
			draw_map(map);
			//mlx_pixel_put(map->cam.mlx_ptr, map->cam.win_ptr, map->pix[y][x].xp, map->pix[y][x].yp, 0xFFFFFF);
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