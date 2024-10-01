/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:09:37 by jtakahas          #+#    #+#             */
/*   Updated: 2024/10/01 14:06:04 by kosnakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	int		up;
	int		down;
	int		left;
	int		right;
	int		x;
	int		y;
}	t_mlx;


int key_press(int key_code, t_mlx *mlx)
{
	if (key_code == ESC)
		exit(0);
	if (key_code == UP)
		mlx->up = 1;
	if (key_code == DOWN)
		mlx->down = 1;
	if (key_code == LEFT)
		mlx->left = 1;
	if (key_code == RIGHT)
		mlx->right = 1;
	return (0);
}

int put_color(t_mlx *mlx)
{
	if (mlx->up == 1)
		mlx_pixel_put(mlx->mlx, mlx->win, mlx->x / 100, mlx->y-- / 100, 0x00FF0000);
	if (mlx->down == 1)
		mlx_pixel_put(mlx->mlx, mlx->win, mlx->x / 100, mlx->y++ / 100, 0x00FF0000);
	if (mlx->right == 1)
		mlx_pixel_put(mlx->mlx, mlx->win, mlx->x++ / 100, mlx->y / 100, 0x00FF0000);
	if (mlx->left == 1)
		mlx_pixel_put(mlx->mlx, mlx->win, mlx->x-- / 100, mlx->y / 100, 0x00FF0000);
	return (0);
}

int key_release(int key_code, t_mlx *mlx)
{
	if (key_code == UP)
		mlx->up = 0;
	if (key_code == DOWN)
		mlx->down = 0;
	if (key_code == LEFT)
		mlx->left = 0;
	if (key_code == RIGHT)
		mlx->right = 0;
	return (0);
}

int	ft_close_window(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->win);
	exit(0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			index;
	unsigned char	c1;
	unsigned char	c2;

	index = 0;
	while (s1[index] || s2[index])
	{
		c1 = (unsigned char)s1[index];
		c2 = (unsigned char)s2[index];
		if (c1 != c2)
			return (c1 - c2);
		index++;
	}
	return (0);
}

int check_map(char **argv)
{
	if (ft_strrchr(argv[1], '.') == 0
		|| ft_strcmp(ft_strrchr(argv[1], '.'), ".cub") != 0)
		return (1);
	
	return (0);
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;

	mlx.x = 0;
	mlx.y = 0;
	if (argc != 2 || check_map(argv))
		exit(0);
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, 800, 600, "cub3D");
	mlx_hook(mlx.win, 17, 1L << 2, ft_close_window, &mlx);
	mlx_hook(mlx.win, 2, 1L << 0, key_press, &mlx);
	mlx_loop_hook(mlx.mlx, put_color, &mlx);
	mlx_hook(mlx.win, 3, 1L << 1, key_release, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
