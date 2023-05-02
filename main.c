/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 09:19:20 by ltressen          #+#    #+#             */
/*   Updated: 2023/04/27 15:28:54 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	deal_key(int key, void *param)
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
}

int	main(void)
{
	void *mlx_ptr;
	void *win_ptr;
	int i;


	i = 10;
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 3840, 2160, "Alex le con");
	while (i++ < 40000000)
	{
		mlx_pixel_put(mlx_ptr, win_ptr, 3*i, i, 0xFFFFFF);
		mlx_pixel_put(mlx_ptr, win_ptr, i, i * 2, 0xFFFFFF);
		mlx_pixel_put(mlx_ptr, win_ptr, 3 * i, i / 9, 0xFFFFFF);
	}
	mlx_key_hook(win_ptr, deal_key, (void *)0);
	mlx_loop(mlx_ptr);
}


/*
void	events(keyevent)
{
	if (keyevent == XK_Escape)
		close_window
}*/