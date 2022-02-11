/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 20:03:49 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/02/10 20:06:10 by jroux-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"    // a changer

int	ft_maplen(char **list)
{
	int	i;

	i = 0;
	while (list[i] != 0)
		i++;
	return (i);
}

int	ft_wherepx(char **map, char p)
{
	int	i;
	int	j;

	j = 0;
	while (map[j] != 0)
	{
		i = 0;
		while (map[j][i] != '\0')
		{
			if (map[j][i] == p)
				return (i);
			i++;
		}
		j++;
	}
	return (-1);
}

int	ft_wherepy(char **map, char p)
{
	int	i;
	int	j;

	j = 0;
	while (map[j] != 0)
	{
		i = 0;
		while (map[j][i] != '\0')
		{
			if (map[j][i] == p)
				return (j);
			i++;
		}
		j++;
	}
	return (-1);
}

int	ft_count_coin(char **map, int line, int column)
{
	int	j;
	int	res;

	(void)line;
	j = 0;
	res = 0;
	while (j < column)
	{
		res = res + ft_ischar(map[j], 'C');
		j++;
	}
	return (res);
}