/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:41:14 by ltressen          #+#    #+#             */
/*   Updated: 2023/05/18 18:01:43 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
/*
int	get_color(char *color)
{
	int	colors;
	int	i;

	colors = 0;
	i = 2;
	while (i < 8)
	{
		if (color[i] >= '0' && color[i] <= '9')
			colors += (ft_power(color[i] - 48, i - 1));
		else
			colors += (ft_power(color[i] - 49, i - 1));
		i++;
	}
	return (colors);
}

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
*/
int	hex_to_int(char *str)
{
	int	i;
	int	res;

	i = 2;
	while(str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			res += ft_power(str[i] - 48, 8 -i);
		else if (str[i] >= 'A' && str[i] <= 'F')
			res += ft_power(str[i] - 49,  8 -i);
		else if (str[i] >= 'a' && str[i] <= 'f')
			res += ft_power(str[i] - 81,  8 -i);
		i++;
	}
	return (res);
}

void	ft_intsplit(t_pbl *map, char *line)
{
	static int	x = 0;
	char		**tmp;
	int			y;
	char		**point;

	y = 0;
	tmp = ft_split(line, ' ');
	while (tmp[y])
		y++;
	map->wth = y;
	map->pix[x] = ft_calloc(y + 1, sizeof(t_point));
	y = 0;
	while (tmp[y])
	{
		point = ft_split(tmp[y], ','); 
		map->pix[x][y].z = ft_atoi(point[0]);
		if (point[1])
		{
			map->pix[x][y].color = hex_to_int(point[1]);
			map->pix[x][y].colorflag = 1;
		}
		if (map->pix[x][y].z > map->zmax)
			map->zmax = map->pix[x][y].z;
		if (map->pix[x][y].z < map->zmin)
			map->zmin = map->pix[x][y].z;
		free(tmp[y]);
		free(point);
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
	map->pix = malloc(sizeof(t_point *) * i);
	file = open(name, O_RDONLY);
	line = get_next_line(file);
	while (line)
	{
		ft_intsplit(map, line);
		free(line);
		line = get_next_line(file);
	}
	return ;
}
