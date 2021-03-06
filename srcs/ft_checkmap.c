/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkmap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 11:59:38 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/02/14 15:39:36 by jroux-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

int	ft_test(char *str, char *set, int count, int i)
{
	if (count != 1)
		return (1);
	if ((str[i - 1] != set[3] || str[i - 2] != set[2] || str[i - 3] != set[1]
			|| str[i - 4] != set [0]))
		return (1);
	return (0);
}

int	ft_checkname(char *str, char *set)
{
	int		i;
	int		j;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		j = 0;
		if (str[i] == set[j])
		{
			while (str[i] == set[j] && j < 4)
			{
				i++;
				j++;
			}
			if (j == 4)
				count++;
			i = i - j;
		}
		i++;
	}
	if (ft_test(str, set, count, i))
		return (write(1, "Error\nInvalid map file name\n", 28), 1);
	return (0);
}

int	ft_checkchar(char *map_path, char *dest, int line, int fd)
{
	if (ft_checkchar1(dest, line, fd))
		return (1);
	close (fd);
	fd = open(map_path, O_RDONLY);
	if (ft_checkchar2(dest, fd))
		return (close(fd), 1);
	close (fd);
	return (0);
}

int	ft_checkmap(char *map_path)
{
	int		line;
	int		fd;
	char	*dest;

	dest = NULL;
	if (ft_checkname(map_path, ".ber"))
		return (1);
	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (write(1, "Error\nfailed to open map\n", 25), 1);
	line = ft_checkrectangle(dest, fd);
	close (fd);
	if (line == 0)
		return (1);
	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (write(1, "Error\nfailed to open map\n", 25), 1);
	if (ft_checkchar(map_path, dest, line, fd))
		return (1);
	return (0);
}
