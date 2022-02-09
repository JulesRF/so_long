/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 16:33:20 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/02/09 19:47:11 by jroux-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "mlx.h"

typedef struct	s_sprite {
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
	int			player_x;
	int			player_y;
	t_sprite	*knight_sprite;
	t_sprite	*coin_sprite;
	t_sprite	*wall_sprite;
	t_sprite	*floor_sprite;
	t_sprite	*exit_sprite;
	t_sprite	*enemy_sprite;
}				t_data;

//get_next_line.c et get_next_line_utils.c
char	*get_next_line(int fd);
int		ft_strlen(char *str);
char	*ft_strdup(char *s1);
char	*ft_strjoin(char *s1, char *s2);
int		ft_is_next_line(char *str, char nl);
char	*ft_sep_after(char *src);

//ft_alloc_map.c
char	**ft_init(int line);
char	**ft_alloc_map(char *map_path);

//ft_checkrectangle.c
int		ft_specialstrlen(char *str);
void	ft_memcpy(char *dst, char *src, int len);
void	ft_memset(int *b, int c, int len);
int		ft_ischar(char *str, char c);
int		ft_checkrectangle(char *dest, int fd);

//ft_checkchar.c
int		ft_first(char *str);
int		ft_last(char *str);
int		ft_middle(char *str);
int		ft_checkchar1(char *dest, int line, int fd);
int		ft_checkchar2(char *dest, int fd);

//ft_checkmap.c
int		ft_checkname(char *str, char *set);
int		ft_checkchar(char *dest, int line, int fd);
int		ft_checkmap(char *map_path);

#endif