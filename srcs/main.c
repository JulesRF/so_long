/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 16:51:40 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/01/27 16:29:58 by jroux-fo         ###   ########.fr       */
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

int	ft_first(char *str)
{
	int	i;
	int	len;

	len = ft_specialstrlen(str);
	i = 0;
	while (str[i])
	{
		if (str[i] != '1' && i != len)
			return (1);
		i++;
	}
	return (0);
}

int	ft_last(char *str)
{
	int	i;
	int	len;

	i = 0;
	while (str[i])
		i++;
	len = i;
	i = 0;
	while (str[i])
	{
		if (str[i] != '1')
		{
			if (i == len - 1 && str[i] == '\n')
				break ;
			else
				return (1);
		}
		i++;
	}
	return (0);
}

int	ft_middle(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '1')
		return (1);
	while (str[i])
		i++;
	if (str[i - 2] != '1')
		return (1);
	return (0);
}

int	ft_checkname(char *str)
{
	int		i;
	int		j;
	int		count;
	char	set[4];

	ft_memcpy(set, ".ber", 4);
	i = 0;
	j = 0;
	count = 0;
	while (str[i])
	{
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
			j = 0;
		}
		i++;
	}
	if (count != 1)
		return (write(1, "Error\nInvalid map file name\n", 28), 1);
	return (0);
}

int	ft_checkchar1(int line, int fd)
{
	char	*dest;
	int 	i;

	i = 1;
	while (dest != NULL || i == 1)
	{
		dest = get_next_line(fd);
		if (dest == NULL)
			break;
		if (i == 1 && ft_first(dest) != 0)
			return (free(dest), write(1, "Error\nInvalid map form.\n", 24), 1);
		else if (i >= line && ft_last(dest) != 0)
			return (free(dest), write(1, "Error\nInvalid map form.\n", 24), 1);
		else if((i < line && i > 0) && (ft_middle(dest) != 0))
			return (free(dest), write(1, "Error\nInvalid map form.\n", 24), 1);
		free (dest);
		i++;
	}
	return (0);
}

int	ft_checkchar2(int fd)
{
	char	*dest;    //C  P  E  
	int		count[3];
	int		i;
	
	ft_memset(count, 0, 3);
	i = 1;
	while (dest != NULL || i == 1)
	{
		dest = get_next_line(fd);
		if (dest == NULL)
			break;
		count[0] = count[0] + ft_ischar(dest, 'C'); // inutile en realite
		count[1] = count[1] + ft_ischar(dest, 'P');
		count[2] = count[2] + ft_ischar(dest, 'E');
		if (count[1] > 1 || count[2] > 1)
			return (free(dest), write(1, "Error\nInvalid map form. 4\n", 26), 1);
		free (dest);
		i++;
	}
	return (0);
}


int	ft_checkchar(char *map_path, int line)
{
	int	fd;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (write(1, "Error\nfailed to open map\n", 25), 1);
	if (ft_checkchar1(line, fd))
	{
		close (fd);
		return (1);
	}
	if (ft_checkchar2(fd))
	{
	 	close (fd);
	 	return (1);
	}
	close (fd);
	return (0);
}

int	ft_checkrectangle(char *map_path)
{
	int	fd;
	int	map_lenght;
	int	line;
	char	*dest;
	
	map_lenght = -1;
	line = 0;
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
		{
			close (fd);
			return (free(dest), write(1, "Error\nInvalid map\n", 18), 0);
		}
		free(dest);
		line++;
	}
	close (fd);
	return (line);
}

int	ft_checkmap(char *map_path)
{
	int	line;
	
	if (ft_checkname(map_path))
		return (1);
	line = ft_checkrectangle(map_path);
	if (line == 0)
		return (1);
	ft_checkchar(map_path, line);
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (write(1, "Error\nInvalid arguments number\n", 31), 1);
	printf("le resultat : %d\n", ft_checkmap(argv[1]));
}