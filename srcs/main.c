/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 16:51:40 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/02/08 15:22:10 by jroux-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"    // a changer en "so_long.h" quand le makefile est termine

typedef	struct	s_sprite {
	char	*path;
	void	*img;
	int		*data;
	int		img_width;
	int		img_heigth;
	int		bpp;
	int		line_length;
	int		endian;
}				t_sprite;

typedef struct	s_data {
	void 		*mlx_ptr;
	void		*mlx_win;
	void		*img;
	char		*addr;
	char		**map;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			line_size;
	int			column_size;
	int			coin_num;
	t_sprite	*knight_sprite;
	t_sprite	*coin_sprite;
	t_sprite	*wall_sprite;
	t_sprite	*floor_sprite;
	t_sprite	*exit_sprite;
}				t_data;

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
	int j;

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
	int j;

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
	system("leaks a.out");
	exit(0);
}

void	ft_switch(t_data *data, int j, int i, int wantj, int wanti)
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
	else if (data->map[wantj][wanti] == 'E' && coin_count == data->coin_num)
	{
		printf("Felicitation, vous avez collecté toutes les gemmes, merci Chevalier !\n");
		ft_exit(data);
	}
	a = data->map[j][i];
	data->map[j][i] = data->map[wantj][wanti];
	data->map[wantj][wanti] = a;
	step_count++;
	printf("Nombre de pas : %d\n", step_count);
	printf("Nombre de collectibles ramasse : %d\n", coin_count);
}

void	ft_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	ft_tpixel(t_data *data, t_sprite *sprite, double ratiox, double ratioy)
{
	int	res;
	double	coefx;
	double	coefy;

	coefx = sprite->img_width * ratiox;
	coefy = sprite->img_heigth * ratioy;
	//coefy = 32 * ratioy;
	// printf("ratiox = %f ratioy = %f\n", (float)ratiox, (float)ratioy);
	// printf("res = %d\n", (int)(sprite->img_width * ratiox + sprite->img_width * (int)(sprite->img_heigth * ratioy)));
	//res = sprite->right_img[((int)(sprite->img_width * coefy) + (int)coefx) * (1 / 8)];
	//printf("sprite->img_width : %d\n", sprite->img_width);
	// res = sprite->data[(int)(sprite->img_width * ratiox + sprite->img_width * (int)(sprite->img_heigth * ratioy))];
	res = sprite->data[(int)(coefx + sprite->img_width * (int)(coefy))];
	if (res == -16777216)
	 	res = data->floor_sprite->data[(int)(data->floor_sprite->img_width
		* ratiox + data->floor_sprite->img_width
		* (int)(data->floor_sprite->img_heigth * ratioy))];
	return(res);
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
			ft_mlx_pixel_put(data, x + i, y + j, ft_tpixel(data, sprite, i / 100, j / 100));
			j++;
		}
		i++;
	}
}

void	ft_draw_square(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	//printf("x = %d, y = %d, color = %d\n", x, y, color);
	//printf("square %d\n", color);
	while (x + i < x + 100)
	{
		j = 0;
		while (y + j < y + 100)
		{
			ft_mlx_pixel_put(data, x + i, y + j, color);
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
			j += 100;
		}
		i += 100;;
	}
}

int	ft_key(int key, void *param)
{
	int		i;
	int		j;

	t_data *data;
	data = (t_data*)param;
	i = ft_wherepx(data->map);
	j = ft_wherepy(data->map);
	if (key == 53)
	 	ft_exit(data);
	else if (key == 13)
		ft_switch(data, j, i, j - 1, i);
	else if (key == 2)
		ft_switch(data, j, i, j, i + 1);
	else if (key == 0)
		ft_switch(data, j, i, j, i - 1);
	else if (key == 1)
		ft_switch(data, j, i, j + 1, i);
	mlx_destroy_image(data->mlx_ptr, data->img);
	data->img = mlx_new_image(data->mlx_ptr, data->line_size * 100, data->column_size * 100);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
	square(data, data->map, data->line_size * 100, data->column_size * 100);
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img, 0, 0);
	return(0);
}

int	main(int argc, char **argv)
{
	int		i;
	t_data	*img;
	//t_sprite	knight;
	
	i = 0;
	if (argc != 2)
		return (printf("Error\nInvalid arguments number\n"), 1);
	if (ft_checkmap(argv[1]))
		return (1);
	img = malloc(sizeof(t_data));
	img->knight_sprite = malloc(sizeof(t_sprite));
	img->wall_sprite = malloc(sizeof(t_sprite));
	img->floor_sprite = malloc(sizeof(t_sprite));
	img->coin_sprite = malloc(sizeof(t_sprite));
	img->exit_sprite = malloc(sizeof(t_sprite));

	img->map = ft_alloc_map(argv[1]);
	img->line_size = ft_strlen(img->map[0]);
	img->column_size = ft_maplen(img->map);
	img->coin_num = ft_count_coin(img->map, img->line_size, img->column_size);
	printf("Il y a %d gemmes sur la map\n", img->coin_num);
	
	img->knight_sprite->path = "./textures/chevalier_droite.xpm";
	img->coin_sprite->path = "./textures/gemme2.xpm";
	img->floor_sprite->path = "./textures/floor2.xpm";
	img->wall_sprite->path = "./textures/wall.xpm";
	img->exit_sprite->path = "./textures/exit.xpm";
	
	
	printf("%s\n", img->knight_sprite->path);
	while (i < img->column_size)
	{
		printf("%s\n", img->map[i]);
		i++;
	}
	printf("la taille d'une ligne = %d, et la taille d'une colone = %d\n", img->line_size, img->column_size);
	img->mlx_ptr = mlx_init();
	img->mlx_win = mlx_new_window(img->mlx_ptr, img->line_size * 100, img->column_size * 100, "so_long");
	
	img->knight_sprite->img = mlx_xpm_file_to_image(img->mlx_ptr, img->knight_sprite->path, &img->knight_sprite->img_width, &img->knight_sprite->img_heigth);
	img->knight_sprite->data = (int*)mlx_get_data_addr(img->knight_sprite->img, &img->knight_sprite->bpp, &img->knight_sprite->line_length, &img->knight_sprite->endian);
	img->coin_sprite->img = mlx_xpm_file_to_image(img->mlx_ptr, img->coin_sprite->path, &img->coin_sprite->img_width, &img->coin_sprite->img_heigth);
	img->coin_sprite->data = (int*)mlx_get_data_addr(img->coin_sprite->img, &img->coin_sprite->bpp, &img->coin_sprite->line_length, &img->coin_sprite->endian);
	img->floor_sprite->img = mlx_xpm_file_to_image(img->mlx_ptr, img->floor_sprite->path, &img->floor_sprite->img_width, &img->floor_sprite->img_heigth);
	img->floor_sprite->data = (int*)mlx_get_data_addr(img->floor_sprite->img, &img->floor_sprite->bpp, &img->floor_sprite->line_length, &img->floor_sprite->endian);
	img->wall_sprite->img = mlx_xpm_file_to_image(img->mlx_ptr, img->wall_sprite->path, &img->wall_sprite->img_width, &img->wall_sprite->img_heigth);
	img->wall_sprite->data = (int*)mlx_get_data_addr(img->wall_sprite->img, &img->wall_sprite->bpp, &img->wall_sprite->line_length, &img->wall_sprite->endian);
	img->exit_sprite->img = mlx_xpm_file_to_image(img->mlx_ptr, img->exit_sprite->path, &img->exit_sprite->img_width, &img->exit_sprite->img_heigth);
	img->exit_sprite->data = (int*)mlx_get_data_addr(img->exit_sprite->img, &img->exit_sprite->bpp, &img->exit_sprite->line_length, &img->exit_sprite->endian);
	
	printf("la fenetre doit etre de taille de ligne %d pixels et colone %d pixel\n", img->line_size * 100, img->column_size * 100);
	img->img = mlx_new_image(img->mlx_ptr, img->line_size * 100, img->column_size * 100);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
	square(img, img->map, img->line_size * 100, img->column_size * 100); 
	//printf("line len : %d\n", img->endian);
	// ft_mlx_pixel_put(&img, 1, 1, 0x00FF0000);
	mlx_key_hook(img->mlx_win, ft_key, img);
	mlx_put_image_to_window(img->mlx_ptr, img->mlx_win, img->img, 0, 0);
	// mlx_put_image_to_window(img->mlx_ptr, img->mlx_win, knight.right_img, 0, 0);
	mlx_loop(img->mlx_ptr);
}