/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_enemy_move.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 19:52:56 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/02/14 15:39:55 by jroux-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

void	ft_switch_enemy(t_data *data, int enemy_x, int enemy_y)
{
	char	c;

	if (data->map[enemy_y][enemy_x + data->enemy_dir] == 'P')
	{
		printf("Oh non, vous êtes repéré !\n");
		ft_exit(data);
	}
	if (data->map[enemy_y][enemy_x + data->enemy_dir] != '0')
	{
		if (data->enemy_dir == 1)
			data->enemy_dir = -1;
		else
			data->enemy_dir = 1;
		return ;
	}
	c = data->map[enemy_y][enemy_x];
	data->map[enemy_y][enemy_x] = data->map[enemy_y][enemy_x + data->enemy_dir];
	data->map[enemy_y][enemy_x + data->enemy_dir] = c;
}

void	ft_enemy_move(t_data *data)
{
	int	x;
	int	y;

	x = ft_wherepx(data->map, 'X');
	y = ft_wherepy(data->map, 'X');
	ft_switch_enemy(data, x, y);
	mlx_destroy_image(data->mlx_ptr, data->img);
	data->img = mlx_new_image(data->mlx_ptr, data->line_size * 100,
			data->column_size * 100);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	ft_square(data, data->map, data->line_size * 100, data->column_size * 100);
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img, 0, 0);
	ft_text(data);
	mlx_string_put(data->mlx_ptr, data->mlx_win, 20, 20, 0, data->text);
}

int	ft_time(t_data *data)
{
	clock_t	time;
	int		res;

	time = clock();
	res = (time - data->ms) * 1000 / CLOCKS_PER_SEC;
	if (res >= 400)
	{
		if (data->enemy_switch == 1)
			data->enemy_switch = 2;
		else
			data->enemy_switch = 1;
		data->ms = clock();
		ft_enemy_move(data);
	}
	return (0);
}
