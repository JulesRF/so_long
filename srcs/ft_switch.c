/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_switch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 20:07:47 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/02/10 20:09:49 by jroux-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"    // a changer

void	ft_exit(t_data *data)
{
	// int	i;
	(void)data;
	// i = 0;
	// free(data->knight_sprite);
	// free(data->coin_sprite);
	// free(data->wall_sprite);
	// free(data->exit_sprite);
	// free(data->floor_sprite);
	// free(data->enemy_sprite);
	// while (data->map[i] != 0)
	// {
	// 	free(data->map[i]);
	// 	i++;
	// }
	// free(data);
	// while (1)
	// 	;
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
