/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 16:51:40 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/01/25 15:57:46 by jroux-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"    // a changer en "so_long.h" quand le makefile est termine

int	ft_specialstrlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	if (str[i - 1] == '\n')
		i--;
	return (i);
}

int	ft_checkname(char *str)
{
	int	i;
	int	j;
	int	count;
	char set[4] = ".ber";

	i = 0;
	j = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == set[j])
		{
			while (str[i] == set[j])
			{
				i++;
				j++;
			}
			if (j = ft_strlen(set))
				count++;
			printf("i avant = %d\n", i);
			i = i - j;
			printf("i apres = %d\n", i);
			printf("j = %d\n", j);
			j = 0;
		}
		i++;
	}
	if (count == 1)
		return (0);
	return (write(1, "Error\nInvalid map file name\n", 28), 1);
}

int	ft_checkrectangle(char *map_path)
{
	int	fd;
	int	map_lenght;
	char	*dest;
	
	map_lenght = -1;
	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (write(1, "Error\nfailed to open map\n", 25), 1);
	while (dest != NULL)
	{
		dest = get_next_line(fd);
		if (dest == NULL)
			break;
		if (map_lenght == -1)
			map_lenght = ft_specialstrlen(dest);
		if (map_lenght != ft_specialstrlen(dest))
			return (free(dest), write(1, "Error\nInvalid map\n", 18), 1);
		free(dest);
	}
	return (0);
}

int	ft_checkmap(char *map_path)
{
	ft_checkname(map_path);
	if (ft_checkrectangle(map_path) == 1)
		return (1);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (write(1, "Error\nInvalid arguments number\n", 31), 1);
	printf("%d\n", ft_checkname(argv[1]));
}