/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:41:14 by ltressen          #+#    #+#             */
/*   Updated: 2023/05/10 13:50:54 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_intsplit(t_pbl *map, char *line)
{
	static int x = 0;
	char	**tmp;
	int	y;

	y = 0;
	tmp = ft_split(line, ' ');
	while(tmp[y])
		y++;
	map->wth = y;
	map->pix[x] = ft_calloc(y + 1, sizeof(t_point));
	y = 0;
	while (tmp[y])
	{
		map->pix[x][y].z = ft_atoi(tmp[y]);
		y++;
	}
	free(tmp);
	x++;
}

void	read_file(t_pbl *map, char *name)
{
	int	file;
	char	*line;
	int	i;


	i = 1;
	file = open(name, O_RDONLY);
	line = get_next_line(file);
	while (line)
	{
		line = get_next_line(file);
		i++;
	}
	close(file);
	map->hgt = i - 1;
	map->pix = malloc(sizeof(t_point *) * i + 1);
	file = open(name, O_RDONLY);
	line = get_next_line(file);
	while (line)
	{
		ft_intsplit(map, line);
		line = get_next_line(file);
 	}
	return ;
}

