/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_switch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 20:07:47 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/02/14 14:15:39 by jroux-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

void	ft_exit(t_data *data)
{
	(void)data;
	exit(0);
}

void	ft_switch(t_data *data, int wantj, int wanti)
{
	static int	coin_count = 0;
	char		a;

	if (data->map[wantj][wanti] == '1' || (data->map[wantj][wanti] == 'E'
		&& coin_count != data->coin_num))
		return ;
	else if (data->map[wantj][wanti] == 'C')
	{
		coin_count++;
		data->map[wantj][wanti] = '0';
	}
	else if (data->map[wantj][wanti] == 'X')
	{
		printf("Oh non, vous êtes repéré !\n");
		ft_exit(data);
	}
	else if (data->map[wantj][wanti] == 'E' && coin_count == data->coin_num)
	{
		printf("Felicitations Chevalier, \
vous avez collecté toutes les gemmes\n");
		ft_exit(data);
	}
	a = data->map[data->player_y][data->player_x];
	data->map[data->player_y][data->player_x] = data->map[wantj][wanti];
	data->map[wantj][wanti] = a;
	data->step_count++;
}

int	ft_close(int input, void *param)
{
	t_data	*data;

	(void)input;
	data = (t_data *)param;
	ft_exit(data);
	return (0);
}

void	ft_text(t_data *data)
{
	if (data->text)
		free (data->text);
	data->text = ft_strjoin2("nombre de pas : ", ft_itoa(data->step_count));
}

int	ft_key(int key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	data->player_x = ft_wherepx(data->map, 'P');
	data->player_y = ft_wherepy(data->map, 'P');
	if (key == 53)
		ft_exit(data);
	else if (key == 13)
		ft_switch(data, data->player_y - 1, data->player_x);
	else if (key == 2)
		ft_switch(data, data->player_y, data->player_x + 1);
	else if (key == 0)
		ft_switch(data, data->player_y, data->player_x - 1);
	else if (key == 1)
		ft_switch(data, data->player_y + 1, data->player_x);
	mlx_destroy_image(data->mlx_ptr, data->img);
	data->img = mlx_new_image(data->mlx_ptr, data->line_size * 100,
			data->column_size * 100);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	ft_square(data, data->map, data->line_size * 100, data->column_size * 100);
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img, 0, 0);
	ft_text(data);
	mlx_string_put(data->mlx_ptr, data->mlx_win, 20, 20, 0, data->text);
	return (0);
}
