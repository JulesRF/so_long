/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkrectangle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 12:10:48 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/02/08 17:20:46 by jroux-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

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

void	ft_memcpy(char *dst, char *src, int len)
{
	int			i;

	i = 0;
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
}

void	ft_memset(int *b, int c, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		b[i] = (unsigned char)c;
		i++;
	}
}

int	ft_ischar(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

int	ft_checkrectangle(char *dest, int fd)
{
	int		map_lenght;
	int		line;
	
	map_lenght = -1;
	line = 0; 
	while (dest != NULL || line == 0)
	{
		dest = get_next_line(fd);
		if (dest == NULL)
			break;
		if (ft_specialstrlen(dest) < 3)
			return(free(dest), printf("Error\nInvalid map"), 0);
		if (map_lenght == -1)
			map_lenght = ft_specialstrlen(dest);
		if (map_lenght != ft_specialstrlen(dest))
			return (free(dest), write(1, "Error\nInvalid map\n", 18), 0);
		free(dest);
		line++;
	}
	if (line < 3)
		return(printf("Error\nInvalid map\n"), 0);
	return (line);
}
