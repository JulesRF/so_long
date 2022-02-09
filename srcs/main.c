/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 16:51:40 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/02/09 23:08:12 by jroux-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"    // a changer en "so_long.h" quand le makefile est termine
#include <time.h>

int	ft_maplen(char **list)
{
	int	i;

	i = 0;
	while (list[i] != 0)
		i++;
	return (i);
}

int	ft_wherepx(char **map)
{
	int	i;
	int	j;

	j = 0;
	while (map[j] != 0)
	{
		i = 0;
		while (map[j][i] != '\0')
		{
			if (map[j][i] == 'P')
				return (i);
			i++;
		}
		j++;
	}
	return (0);
}

int	ft_wherepy(char **map)
{
	int	i;
	int	j;

	j = 0;
	while (map[j] != 0)
	{
		i = 0;
		while (map[j][i] != '\0')
		{
			if (map[j][i] == 'P')
				return (j);
			i++;
		}
		j++;
	}
	return (0);
}

int	ft_count_coin(char **map, int line, int column)
{
	int	j;
	int	res;

	(void)line;
	j = 0;
	res = 0;
	while (j < column)
	{
		res = res + ft_ischar(map[j], 'C');
		j++;
	}
	return (res);
}

void	ft_exit(t_data *data)
{
	data = NULL;
	exit(0);
}

void	ft_switch(t_data *data, int wantj, int wanti)
{
	static int	step_count = 0;
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
	step_count++;
	printf("Nombre de pas : %d\n", step_count);
	printf("Nombre de collectibles ramasse : %d\n", coin_count);
}

void	ft_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	ft_tkpixel(t_data *data, t_sprite *sprite, double ratiox, double ratioy)
{
	int		res;
	double	coefx;
	double	coefy;

	coefx = sprite->img_width * ratiox;
	coefy = sprite->img_heigth * ratioy;
	res = sprite->data[(int)(coefx + sprite->img_width * (int)(coefy))];
	if (res == -16777216)
	{
		res = data->floor_sprite->data[(int)(data->floor_sprite->img_width
				* ratiox + data->floor_sprite->img_width
				* (int)(data->floor_sprite->img_heigth * ratioy))];
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

void	square(t_data *data, char **map, int x, int y)
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
				ft_draw_sprite(data, i, j, data->enemy_sprite);
			j += 100;
		}
		i += 100;
	}
}

int	ft_close(int input, void *param)
{
	t_data	*data;

	(void)input;
	data = (t_data *)param;
	ft_exit(data);
	return (0);
}

int	ft_key(int key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	data->player_x = ft_wherepx(data->map);
	data->player_y = ft_wherepy(data->map);
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
	square(data, data->map, data->line_size * 100, data->column_size * 100);
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img, 0, 0);
	return (0);
}

void	ft_init_sprite2(t_data *data, t_sprite *sprite)
{
	sprite->img = mlx_xpm_file_to_image(data->mlx_ptr,
				sprite->path, &sprite->img_width,
				&sprite->img_heigth);
	sprite->data = (int *)mlx_get_data_addr(sprite->img,
				&sprite->bpp, &sprite->line_length,
				&sprite->endian);
}

void	ft_init_sprite(t_data *data)
{	
	data->knight_sprite = malloc(sizeof(t_sprite));
	data->knight_sprite->path = "./textures/player.xpm";
	data->coin_sprite = malloc(sizeof(t_sprite));
	data->coin_sprite->path = "./textures/gemme2.xpm";
	data->floor_sprite = malloc(sizeof(t_sprite));
	data->floor_sprite->path = "./textures/floor2.xpm";
	data->wall_sprite = malloc(sizeof(t_sprite));
	data->wall_sprite->path = "./textures/wall.xpm";
	data->exit_sprite = malloc(sizeof(t_sprite));
	data->exit_sprite->path = "./textures/exit.xpm";
	data->enemy_sprite = malloc(sizeof(t_sprite));
	data->enemy_sprite->path = "./textures/chevalier_droite.xpm";
	ft_init_sprite2(data, data->knight_sprite);
	ft_init_sprite2(data, data->coin_sprite);
	ft_init_sprite2(data, data->floor_sprite);
	ft_init_sprite2(data, data->wall_sprite);
	ft_init_sprite2(data, data->exit_sprite);
	ft_init_sprite2(data, data->enemy_sprite);
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
	data->map = ft_alloc_map(arg);
	data->line_size = ft_strlen(data->map[0]);
	data->column_size = ft_maplen(data->map);
	data->coin_num = ft_count_coin(data->map, data->line_size, data->column_size);
}

int	ft_time(t_data *data)
{
	clock_t						time;
	static unsigned long int	secondes = 0;
	
	(void)data;
	time = clock();
	if (time / CLOCKS_PER_SEC != secondes)
	{
		secondes = time / CLOCKS_PER_SEC;
		ft_switch()
		printf("%lu\n", secondes);
	}
	return (0);
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
	ft_init_mstruct(img, argv[1]);
	printf("Il y a %d gemmes sur la map\n", img->coin_num);
	while (i < img->column_size)
	{
		printf("%s\n", img->map[i]);
		i++;
	}
	ft_init_mlxwinimg(img);
	ft_init_sprite(img);
	square(img, img->map, img->line_size * 100, img->column_size * 100);
	mlx_hook(img->mlx_win, 17, 0, ft_close, img);
	mlx_key_hook(img->mlx_win, ft_key, img);
	mlx_loop_hook(img->mlx_ptr, ft_time, img);
	mlx_put_image_to_window(img->mlx_ptr, img->mlx_win, img->img, 0, 0);
	mlx_loop(img->mlx_ptr);
}
