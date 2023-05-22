/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 10:38:08 by ltressen          #+#    #+#             */
/*   Updated: 2023/05/22 11:14:20 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define MENU_TAB 30
#define LINE_SIZE 30
#define CONTROL_BOX 280

void	print_str(t_pbl *map, int x, int y, char *str)
{
	mlx_string_put(map->cam.mlx_ptr, map->cam.win_ptr, x, y, TEXT_COLOR, str);
}

void	draw_controls(t_pbl *map)
{
	int	line;

	line = CONTROL_BOX;
	print_str(map, MENU_TAB, line, "CONTROLS");
	line += LINE_SIZE;
	print_str(map, MENU_TAB, line, "+/- : Zoom in/out");
	line += LINE_SIZE;
	print_str(map, MENU_TAB, line, "WASD : Translate");
	line += LINE_SIZE;
	print_str(map, MENU_TAB, line, "Q-E : Rotate");
	line += LINE_SIZE;
	print_str(map, MENU_TAB, line, "R-F : Change Angle");
	line += LINE_SIZE;
	print_str(map, MENU_TAB, line, "G-T : Change Altitude");
	line += LINE_SIZE;
	print_str(map, MENU_TAB, line, "X : Reset to Isometric");
	line += LINE_SIZE;
	print_str(map, MENU_TAB, line, "V : Set to Dimetric");
	line += LINE_SIZE;
	print_str(map, MENU_TAB, line, "B : Set to Trimetric");
}
