/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_square.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 19:56:33 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/02/14 15:42:44 by jroux-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

void	ft_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	ft_tkpixel(t_data *data, t_sprite *sprite, double rx, double ry)
{
	int		res;
	double	coefx;
	double	coefy;

	coefx = sprite->img_width * rx;
	coefy = sprite->img_heigth * ry;
	res = sprite->data[(int)(coefx + sprite->img_width * (int)(coefy))];
	if (res == -16777216)
	{
		res = data->floor_sprite->data[(int)(data->floor_sprite->img_width
				* rx + data->floor_sprite->img_width
				* (int)(data->floor_sprite->img_heigth * ry))];
	}
	return (res);
}

void	ft_draw_sprite(t_data *data, int x, int y, t_sprite *sprite)
{
	double	i;
	double	j;

	i = 0;
	while (x + i < x + 100)
	{
		j = 0;
		while (y + j < y + 100)
		{
			ft_mlx_pixel_put(data, x + i, y + j,
				ft_tkpixel(data, sprite, i / 100, j / 100));
			j++;
		}
		i++;
	}
}

void	ft_draw_enemy(t_data *data, int i, int j)
{
	if (data->enemy_switch == 1)
		ft_draw_sprite(data, i, j, data->enemy_sprite);
	else if (data->enemy_switch == 2)
		ft_draw_sprite(data, i, j, data->enemy2_sprite);
}

void	ft_square(t_data *data, char **map, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < x)
	{
		j = 0;
		while (j < y)
		{
			if (map[j / 100][i / 100] == '1')
				ft_draw_sprite(data, i, j, data->wall_sprite);
			if (map[j / 100][i / 100] == '0')
				ft_draw_sprite(data, i, j, data->floor_sprite);
			if (map[j / 100][i / 100] == 'C')
				ft_draw_sprite(data, i, j, data->coin_sprite);
			if (map[j / 100][i / 100] == 'E')
				ft_draw_sprite(data, i, j, data->exit_sprite);
			if (map[j / 100][i / 100] == 'P')
				ft_draw_sprite(data, i, j, data->knight_sprite);
			if (map[j / 100][i / 100] == 'X')
				ft_draw_enemy(data, i, j);
			j += 100;
		}
		i += 100;
	}
}
