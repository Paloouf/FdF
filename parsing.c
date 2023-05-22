/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:41:14 by ltressen          #+#    #+#             */
/*   Updated: 2023/05/22 11:24:28 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	color_parse(t_point one, t_point two)
{
	if (one.z > two.z)
		return (one.color);
	if (two.color > one.z)
		return (two.color);
	else
		return (16777215);
}

int	get_color(char *color)
{
	int	colors;
	int	i;

	colors = 0;
	i = 0;
	while (color[i])
	{
		if (color[i] >= '0' && color[i] <= '9')
			colors += (color[i] - 48)
				* (ft_power(16, ft_strlen(color) - i - 1));
		else if (color[i] >= 'A' && color[i] <= 'F')
			colors += (color[i] - 55)
				* (ft_power(16, ft_strlen(color) - i - 1));
		else if (color[i] >= 'a' && color[i] <= 'f')
			colors += (color[i] - 87)
				* (ft_power(16, ft_strlen(color) - i - 1));
		i++;
	}
	return (colors);
}

void	ft_intsplit(t_pbl *map, char *line)
{
	static int	x = 0;
	char		**tmp;
	int			y;
	char		**point;

	y = 0;
	tmp = ft_split(line, ' ');
	while (tmp[y] && tmp[y][0] != '\n')
		y++;
	map->wth = y;
	map->pix[x] = ft_calloc(y, sizeof(t_point));
	y = 0;
	while (tmp[y])
	{
		point = ft_split(tmp[y], 'x');
		intsplit_parse(map, point, x, y);
		free(tmp[y]);
		y++;
	}
	free(tmp);
	x++;
}

void	intsplit_parse(t_pbl *map, char **point, int x, int y)
{
	map->pix[x][y].z = ft_atoi(point[0]);
	if (point[1])
	{
		map->pix[x][y].color = get_color(point[1]);
		map->pix[0][0].colorflag = 1;
	}
	else
		map->pix[x][y].colorflag = 0;
	if (map->pix[x][y].z > map->zmax)
		map->zmax = map->pix[x][y].z;
	if (map->pix[x][y].z < map->zmin)
		map->zmin = map->pix[x][y].z;
	free(point[0]);
	free(point[1]);
	free(point);
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
	while (i-- > 1)
	{
		ft_intsplit(map, line);
		free(line);
		line = get_next_line(file);
	}
	return ;
}
