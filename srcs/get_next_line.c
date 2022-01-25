/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 10:28:05 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/01/25 12:29:02 by jroux-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"  // a changer

char	*get_next_line(int fd)
{
	char		buffer[16 + 1];
	char		*line;
	static char	*save = NULL;
	int			ret;

	ret = 1;
	if (fd < 0 || 16 <= 0)
		return (NULL);
	while (!ft_is_next_line(save, '\n') && ret > 0)
	{
		ret = read(fd, buffer, 16);
		if (ret <= 0)
			break ;
		buffer[ret] = '\0';
		save = ft_strjoin(save, buffer);
	}
	line = ft_strdup(save);
	save = ft_sep_after(save);
	return (line);
}
