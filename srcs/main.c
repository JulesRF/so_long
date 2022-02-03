/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 16:51:40 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/02/03 16:58:56 by jroux-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"    // a changer en "so_long.h" quand le makefile est termine

typedef struct	s_data {
	void 	*mlx_ptr;
	void	*mlx_win;
	void	*img;
	char	*addr;
	char	**map;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		line_size;
	int		column_size;
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

void	ft_swap(char *a, char *b)
{
	char temp;
	
	temp = *a;
	*a = *b;
	*b = temp;
}

void	ft_switch(char **map, int j, int i, int wantj, int wanti)
{
	//ft_swap(&map[i][j], &map[wanti][wantj]);
	char a;
	
	if (map[wantj][wanti] == '1')
		return ;
	a = map[j][i];
	map[j][i] = map[wantj][wanti];
	map[wantj][wanti] = a;	
}

void	ft_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
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
			// ft_mlx_pixel_put(data, i, j, 0x00FFB7C5);
			if (map[j / 100][i / 100] == '1')
				ft_mlx_pixel_put(data, i, j, 0x00FF0000);
			if (map[j / 100][i / 100] == '0')
				ft_mlx_pixel_put(data, i, j, 0x0000FF00);
			if (map[j / 100][i / 100] == 'C')
				ft_mlx_pixel_put(data, i, j, 0x000000FF);
			if (map[j / 100][i / 100] == 'E')
				ft_mlx_pixel_put(data, i, j, 0x0000FFFF);
			if (map[j / 100][i / 100] == 'P')
				ft_mlx_pixel_put(data, i, j, 0x00FFB7C5);
			j++;
		}
		i++;
	}
	// (void)x;
	// (void)y;
	// (void)map;
	// for (int i = 100; i < 400; i++) {
	// 	for (int j = 100; j < 400; j++) {
	// 		ft_mlx_pixel_put(data, i, j, 0x00FFB7C5);
	// 	}
	// }
}

int	ft_key(int key, void *param)
{
	int		i;
	int		j;
	// char	**dest;

	t_data *data;
	data = (t_data*)param;
	i = ft_wherepx(data->map);
	j = ft_wherepy(data->map);
	if (key == 13)
	{
		printf("EN HAUT\n");
		ft_switch((char **)data->map, j, i, j - 1, i);
	}
	else if (key == 2)
	{
		printf("A DROITE (S/o marine)\n");
		ft_switch(data->map, j, i, j, i + 1);
	}
	else if (key == 0)
	{
		printf("A GAUCHE (rpz meluch)\n");
		ft_switch(data->map, j, i, j, i - 1);
	}
	else if (key == 1)
	{
		printf("EN BAAAAAS\n");
		ft_switch(data->map, j, i, j + 1, i);
	}
	// printf("les coordonnes : j = %d, i = %d\n", j, i);
	// i = 0;
	mlx_destroy_image(data->mlx_ptr, data->img);
	data->img = mlx_new_image(data->mlx_ptr, data->line_size * 100, data->column_size * 100);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
	square(data, data->map, data->line_size * 100, data->column_size * 100);
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img, 0, 0);
	// dest = data->map;
	// while (i < 6)
	// {
	// 	printf("%s\n", dest[i]);
	// 	i++;
	// }
	return(0);
}

int	main(int argc, char **argv)
{
	// char	**map;
	int		i;
	// void 	*mlx_ptr;
	// void	*mlx_win;
	t_data	img;
	// int		line_size;
	// int		column_size;
	
	
	i = 0;
	if (argc != 2)
		return (write(1, "Error\nInvalid arguments number\n", 31), 1);
	if (ft_checkmap(argv[1]))
		return (1);
	img.map = ft_alloc_map(argv[1]);
	img.line_size = ft_strlen(img.map[0]);
	img.column_size = ft_maplen(img.map);
	while (i < img.column_size)
	{
		printf("%s\n", img.map[i]);
		i++;
	}
	printf("la taille d'une ligne = %d, et la taille d'une colone = %d\n", img.line_size, img.column_size);
	img.mlx_ptr = mlx_init();
	img.mlx_win = mlx_new_window(img.mlx_ptr, img.line_size * 100, img.column_size * 100, "so_long");
	printf("la fenetre doit etre de taille de ligne %d pixels et colone %d pixel\n", img.line_size * 100, img.column_size * 100);
	img.img = mlx_new_image(img.mlx_ptr, img.line_size * 100, img.column_size * 100);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	square(&img, img.map, img.line_size * 100, img.column_size * 100); 
	//printf("line len : %d\n", img.endian);
	// ft_mlx_pixel_put(&img, 1, 1, 0x00FF0000);
	mlx_key_hook(img.mlx_win, ft_key, &img);
	mlx_put_image_to_window(img.mlx_ptr, img.mlx_win, img.img, 0, 0);
	mlx_loop(img.mlx_ptr);
}