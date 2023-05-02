/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:41:14 by ltressen          #+#    #+#             */
/*   Updated: 2023/05/02 15:20:47 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	*ft_intsplit(char *line)
{
	int	*result;
	char	**tmp;
	int	i;

	i = 0;
	tmp = ft_split(line, ' ');
	while(tmp[i])
		i++;
	result = (int *)malloc(sizeof(int) * (i + 1));
	result[i] = '\0';
	i = 0;
	while (tmp[i])
	{
		result[i] = ft_atoi(tmp[i]);
		i++;
	}
	free(tmp);
	return (result);
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
	map->tab = (int **)malloc(sizeof(int *) * (i + 1));
	map->tab[i] = '\0';
	file = open(name, O_RDONLY);
	line = get_next_line(file);
	i = 0;
	while (line)
	{
		map->tab[i] = ft_intsplit(line);
		line = get_next_line(file);
		i++;
 	}
	return ;
}