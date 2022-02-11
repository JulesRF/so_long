/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 12:04:54 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/02/10 20:14:27 by jroux-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"    // a changer en "so_long.h" quand le makefile est termine

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

int	ft_checkchar1(char *dest, int line, int fd)
{
	int	i;

	i = 1;
	while (dest != NULL || i == 1)
	{
		dest = get_next_line(fd);
		if (dest == NULL)
			break ;
		if (i == 1 && ft_first(dest) != 0)
			return (free(dest), write(1, "Error\nInvalid map form.\n", 24), 1);
		else if (i >= line && ft_last(dest) != 0)
			return (free(dest), write(1, "Error\nInvalid map form.\n", 24), 1);
		else if ((i < line && i > 0) && (ft_middle(dest) != 0))
			return (free(dest), write(1, "Error\nInvalid map form.\n", 24), 1);
		free (dest);
		i++;
	}
	return (0);
}

int	ft_checkchar2(char *dest, int fd)
{
	int	count[3];  //C  P  E
	int	i;
	
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
