/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:41:16 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/02/14 13:54:45 by jroux-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

void	ft_init_sprite2(t_data *data, t_sprite *sprite)
{
	sprite->img = mlx_xpm_file_to_image(data->mlx_ptr,
			sprite->path, &sprite->img_width,
			&sprite->img_heigth);
	if (!sprite->img)
		exit(1);
	sprite->data = (int *)mlx_get_data_addr(sprite->img,
			&sprite->bpp, &sprite->line_length,
			&sprite->endian);
}

void	ft_init_enemy(t_data *data)
{
	data->enemy_sprite = malloc(sizeof(t_sprite));
	data->enemy2_sprite = malloc(sizeof(t_sprite));
	data->enemy_sprite->path = "./textures/chevalier_droite.xpm";
	data->enemy2_sprite->path = "./textures/chevalier_bas.xpm";
	data->enemy_dir = 1;
	data->enemy_switch = 1;
	ft_init_sprite2(data, data->enemy_sprite);
	ft_init_sprite2(data, data->enemy2_sprite);
}

void	ft_init_sprite(t_data *data)
{	
	data->knight_sprite = malloc(sizeof(t_sprite));
	data->coin_sprite = malloc(sizeof(t_sprite));
	data->floor_sprite = malloc(sizeof(t_sprite));
	data->wall_sprite = malloc(sizeof(t_sprite));
	data->exit_sprite = malloc(sizeof(t_sprite));
	if (ft_wherepx(data->map, 'X') != -1 && ft_wherepy(data->map, 'X') != -1)
		ft_init_enemy(data);
	if (!data->knight_sprite || !data->coin_sprite || !data->floor_sprite
		|| !data->wall_sprite || !data->exit_sprite)
		exit(1);
	data->knight_sprite->path = "./textures/player.xpm";
	data->coin_sprite->path = "./textures/gemme2.xpm";
	data->floor_sprite->path = "./textures/floor2.xpm";
	data->wall_sprite->path = "./textures/wall.xpm";
	data->exit_sprite->path = "./textures/exit.xpm";
	ft_init_sprite2(data, data->knight_sprite);
	ft_init_sprite2(data, data->coin_sprite);
	ft_init_sprite2(data, data->floor_sprite);
	ft_init_sprite2(data, data->wall_sprite);
	ft_init_sprite2(data, data->exit_sprite);
}

void	ft_init_mlxwinimg(t_data *data)
{
	data->mlx_ptr = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx_ptr, data->line_size * 100,
			data->column_size * 100, "so_long");
	data->img = mlx_new_image(data->mlx_ptr, data->line_size * 100,
			data->column_size * 100);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
}

void	ft_init_mstruct(t_data *data, char *arg)
{
	data->ms = clock();
	data->step_count = 0;
	data->map = ft_alloc_map(arg);
	data->line_size = ft_strlen(data->map[0]);
	data->column_size = ft_maplen(data->map);
	data->coin_num = ft_count_coin(data->map, data->line_size,
			data->column_size);
	data->text = NULL;
}
