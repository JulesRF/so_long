/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 19:29:10 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/02/11 16:15:45 by jroux-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"    // a changer

static int	ft_count(int n)
{
	int	count;

	count = 1;
	while (n >= 10)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static char	*ft_rev(char *str, int size, int moins, int i)
{
	int		j;
	char	temp;

	if (moins == 1)
		str[i] = 45;
	i = 0;
	j = size - 1;
	while (i < j)
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}
	str[size] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	char	*dest;
	int		size;
	int		i;
	int		moins;

	i = 0;
	moins = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		moins = 1;
		n = n * -1;
	}
	size = ft_count(n) + moins;
	dest = malloc(sizeof(char) * size + 1);
	if (!dest)
		return (NULL);
	while (i < size - moins)
	{
		dest[i++] = n % 10 + 48;
		n = n / 10;
	}
	return (ft_rev(dest, size, moins, i));
}

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*dest;
	int		size_dest;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	size_dest = ft_strlen(s1) + ft_strlen(s2);
	i = 0;
	j = 0;
	dest = malloc(sizeof(char) * size_dest + 1);
	if (!dest)
		return (NULL);
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	while (s2[j])
		dest[i++] = s2[j++];
	dest[i] = '\0';
	free (s2);
	return (dest);
}
