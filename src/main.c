/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:09:37 by jtakahas          #+#    #+#             */
/*   Updated: 2024/10/07 17:12:55 by kosnakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
	{
		mlx_pixel_put(mlx->mlx, mlx->win, mlx->x / CHARSPEED, mlx->y-- / CHARSPEED, 0x00FF0000);
		// mlx_pixel_put(mlx->mlx, mlx->win, mlx->x / CHARSPEED, mlx->y / CHARSPEED, 0x00000000);
	}
	if (mlx->down == 1)
	{
		mlx_pixel_put(mlx->mlx, mlx->win, mlx->x / CHARSPEED, mlx->y++ / CHARSPEED, 0x00FF0000);
		// mlx_pixel_put(mlx->mlx, mlx->win, mlx->x / CHARSPEED, mlx->y / CHARSPEED, 0x00000000);
	}
	if (mlx->right == 1)
	{
		mlx_pixel_put(mlx->mlx, mlx->win, mlx->x++ / CHARSPEED, mlx->y / CHARSPEED, 0x00FF0000);
		// mlx_pixel_put(mlx->mlx, mlx->win, mlx->x / CHARSPEED, mlx->y / CHARSPEED, 0x00000000);
	}
	if (mlx->left == 1)
	{
		mlx_pixel_put(mlx->mlx, mlx->win, mlx->x-- / CHARSPEED, mlx->y / CHARSPEED, 0x00FF0000);
		// mlx_pixel_put(mlx->mlx, mlx->win, mlx->x / CHARSPEED, mlx->y / CHARSPEED, 0x00000000);
	}
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

void	put_img(t_img img, int x, int y)
{
	img.img_width = 20;
	img.img_height = 20;
	img.img = mlx_xpm_file_to_image(img.mlx.mlx,
			img.relative_path, &img.img_width, &img.img_height);
	mlx_put_image_to_window(img.mlx.mlx, img.mlx.win, img.img, y, x);
}

void	put_wall(t_mlx mlx)
{
	int	x = 0;
	int	y = 0;
	t_img	img;

	img.relative_path = "./img/0.xpm";
	img.mlx = mlx;
	while (y < WINHEIGHT / PIXELSIZE)
	{
		x = 0;
		while (x < WINWIDTH / PIXELSIZE)
		{
			if (mlx.map[x] && mlx.map[x][y] == '1')
				put_img(img, x * PIXELSIZE, y * PIXELSIZE);
			x++;
		}
		y++;
	}
}

void	cub(t_mlx mlx)
{
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, WINWIDTH, WINHEIGHT, "cub3D");
	put_wall(mlx);
	mlx_loop_hook(mlx.mlx, put_color, &mlx);
	mlx_hook(mlx.win, 2, 1L << 0, key_press, &mlx);
	mlx_hook(mlx.win, 3, 1L << 1, key_release, &mlx);
	mlx_hook(mlx.win, 17, 1L << 2, ft_close_window, &mlx);
	mlx_loop(mlx.mlx);
}

void	map_scan(t_mlx *mlx, char *argv)
{
	int		y;
	int		fd;

	y = 0;
	fd = open(argv, O_RDONLY);
	mlx->map = (char **)malloc(sizeof(char *) * OPEN_MAX);
	while (y < WINWIDTH / PIXELSIZE)
	{
		mlx->map[y] = get_next_line(fd);
		y++;
	}
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;

	mlx.x = 60 * CHARSPEED;
	mlx.y = 60 * CHARSPEED;
	if (argc != 2 || check_map(argv))
		exit(0);
	map_scan(&mlx, argv[1]);
	cub(mlx);
	return (0);
}
