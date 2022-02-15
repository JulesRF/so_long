/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 16:51:40 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/02/14 13:54:26 by jroux-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

int	main(int argc, char **argv)
{
	t_data	*img;

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
	mlx_string_put(img->mlx_ptr, img->mlx_win, 20, 20, 0, "nombre de pas : 0");
	mlx_loop(img->mlx_ptr);
}
