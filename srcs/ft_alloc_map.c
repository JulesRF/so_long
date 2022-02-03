/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 12:12:01 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/02/01 16:55:28 by jroux-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"    // a changer

char **ft_init(int line)
{
	char	**init;
	init = malloc(sizeof(char *) * (line + 1));
	if (!init)
		return (write(1,"Error\nmalloc fail", 17), NULL);
	init[0] = 0;
	return (init);
}

char	**ft_alloc_map(char *map_path)
{
	char	**dest;
	char	*temp;
	int		fd;
	int		i;
	int		line;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (write(1, "Error\nfailed to open map\n", 25), NULL);
	line = ft_checkrectangle(map_path, fd);
	dest = ft_init(line);
	if (!dest)
		return (NULL);
	close (fd);
	fd = open(map_path, O_RDONLY);
	i = 0;
	while (i < line)
	{
		temp = get_next_line(fd);
		if (ft_ischar(temp, '\n'))
		{
			temp[ft_specialstrlen(temp)] = '\0';
		}
		dest[i] = ft_strdup(temp);
		free (temp);
		i++;
	}
	dest[i] = 0;
	return (dest);
}