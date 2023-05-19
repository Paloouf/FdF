/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:41:14 by ltressen          #+#    #+#             */
/*   Updated: 2023/05/19 15:31:59 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_color(char *color)
{
	int	colors;
	int	i;

	colors = 0;
	i = 0;
	while (color[i])
	{
		if (color[i] >= '0' && color[i] <= '9')
			colors += (color[i] - 48) * (ft_power(16, ft_strlen(color) - i));
		else if (color[i] >= 'A' && color[i] <= 'F')
			colors += (color[i] - 55) * (ft_power(16, ft_strlen(color) - i));
		else if (color[i] >= 'a' && color[i] <= 'f')
			colors += (color[i] - 87) * (ft_power(16, ft_strlen(color) - i));
		i++;
	}
	return (colors);
}
/*
int	parsing_color(t_point one, t_point two, int i, int total)
{
	int	color_one;
	//int	color_two;

	color_one = 16777215;
	//color_two = 16777215;
	if (!one.colorflag && !two.colorflag)
		return (16777215);
	if (two.colorflag)
		color_one = get_color(two.colorhex);
	if (one.colorflag)
		color_one = get_color(one.colorhex);
	(void)i;
	(void)total;
	return (color_one);
}

int	hex_to_int(char *str)
{
	int	i;
	int	res;
	int	base;

	i = ft_strlen(str);
	base = 1;
	while(i > 1)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			res += (str[i] - 48) * base;
			base *= 16;
		}
		else if (str[i] >= 'A' && str[i] <= 'F')
		{
			res += (str[i] - 55) * base;
			base *= 16;
		}
		else if (str[i] >= 'a' && str[i] <= 'f')
		{
			res += (str[i] - 87) * base;
			base *= 16;
		}
		i--;
	}
	return (res-1);
}
*/
void	ft_intsplit(t_pbl *map, char *line)
{
	static int	x = 0;
	char		**tmp;
	int			y;
	char		**point;

	y = 0;
	tmp = ft_split(line, ' ');
	//ft_printf("%s \n", line);
	while (tmp[y] && tmp[y][0] != '\n')
		y++;
	map->wth = y;
	//ft_printf("%d\n", map->wth);
	map->pix[x] = ft_calloc(y, sizeof(t_point));
	//malloc(sizeof(t_point)*y);
	y = 0;
	while (tmp[y])
	{
		point = ft_split(tmp[y], 'x'); 
		map->pix[x][y].z = ft_atoi(point[0]);
		if (point[1])
		{
			map->pix[x][y].color = get_color(point[1]);
			//ft_printf("%d\n", map->pix[x][y].color);
			map->pix[0][0].colorflag = 1;
		}
		else
			map->pix[x][y].colorflag = 0;
		if (map->pix[x][y].z > map->zmax)
			map->zmax = map->pix[x][y].z;
		if (map->pix[x][y].z < map->zmin)
			map->zmin = map->pix[x][y].z;
		free(tmp[y]);
		//free(point);
		y++;
	}
	free(tmp);
	x++;
}

void	read_file(t_pbl *map, char *name)
{
	int		file;
	int		i;
	char	*line;

	i = 1;
	file = open(name, O_RDONLY);
	line = get_next_line(file);
	while (line)
	{
		free(line);
		line = get_next_line(file);
		i++;
	}
	close(file);
	map->hgt = i - 1;
	map->pix = malloc(sizeof(t_point *) * i - 1);
	file = open(name, O_RDONLY);
	line = get_next_line(file);
	while (i > 1)
	{
		ft_intsplit(map, line);
		free(line);
		line = get_next_line(file);
		i--;
	}
	return ;
}
