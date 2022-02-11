/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 16:51:40 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/02/10 20:07:38 by jroux-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"    // a changer en "so_long.h" quand le makefile est termine

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
	mlx_string_put(data->mlx_ptr, data->mlx_win, 20, 20, 0, ft_strjoin2("nombre de pas : ", ft_itoa(data->step_count)));
	return (0);
}

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

void	ft_init_sprite(t_data *data)
{	
	data->knight_sprite = malloc(sizeof(t_sprite));
	data->coin_sprite = malloc(sizeof(t_sprite));
	data->floor_sprite = malloc(sizeof(t_sprite));
	data->wall_sprite = malloc(sizeof(t_sprite));
	data->exit_sprite = malloc(sizeof(t_sprite));
	if (ft_wherepx(data->map, 'X') != -1 && ft_wherepy(data->map, 'X') != -1)
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
	data->coin_num = ft_count_coin(data->map, data->line_size, data->column_size);
}

int	main(int argc, char **argv)
{
	int		i;
	t_data	*img;

	i = 0;
	if (argc != 2)
		return (printf("Error\nInvalid arguments number\n"), 1);
	if (ft_checkmap(argv[1]))
		return (1);
	img = malloc(sizeof(t_data));
	if (!img)
		return (1);
	ft_init_mstruct(img, argv[1]);
	ft_init_mlxwinimg(img);
	ft_init_sprite(img);
	ft_square(img, img->map, img->line_size * 100, img->column_size * 100);
	mlx_hook(img->mlx_win, 17, 0, ft_close, img);
	mlx_key_hook(img->mlx_win, ft_key, img);
	if (img->enemy_sprite)
		mlx_loop_hook(img->mlx_ptr, ft_time, img);
	mlx_put_image_to_window(img->mlx_ptr, img->mlx_win, img->img, 0, 0);
	mlx_string_put(img->mlx_ptr, img->mlx_win, 20, 20, 0, ft_strjoin2("nombre de pas : ", ft_itoa(img->step_count)));
	mlx_loop(img->mlx_ptr);
}
