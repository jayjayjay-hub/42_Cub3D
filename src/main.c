/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:09:37 by jtakahas          #+#    #+#             */
/*   Updated: 2024/10/17 15:06:04 by kosnakam         ###   ########.fr       */
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

int	close_window(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->win);
	exit(0);
}

void	put_pixel(t_img img, int x, int y, char pixel)
{
	img.img_width = 0;
	img.img_height = 0;
	if (pixel == '0')
		img.relative_path = "./img/0.xpm";
	else if (pixel == '1')
		img.relative_path = "./img/1.xpm";
	else if (pixel == 'p')
		img.relative_path = "./img/p.xpm";
	img.img = mlx_xpm_file_to_image(img.mlx.mlx,
			img.relative_path, &img.img_width, &img.img_height);
	mlx_put_image_to_window(img.mlx.mlx, img.mlx.win, img.img, x, y);
	// mlx_new_image
	// mlx_put_image_to_window
}

void	create_map(t_mlx mlx)
{
	int	y = 0;
	int	x = 0;
	t_img	img;

	img.mlx = mlx;
	img.img_width = 40;
	img.img_height = 40;
	while (x < WINHEIGHT / PIXELSIZE)
	{
		y = 0;
		while (y < WINWIDTH / PIXELSIZE)
		{
			if (mlx.map_info->map[y] && mlx.map_info->map[y][x] == '1')
			{
				put_pixel(img, x * PIXELSIZE, y * PIXELSIZE, '1');
			}
			if (mlx.map_info->map[y] && mlx.map_info->map[y][x] == '0')
			{
				put_pixel(img, x * PIXELSIZE, y * PIXELSIZE, '0');
			}
			y++;
		}
		x++;
	}
}

void	map_refresh(t_mlx mlx, int ox, int oy)
{
	int	upy;
	int	upx;
	t_img	img;

	img.mlx = mlx;
	upy = oy / PIXELSIZE / CHARSPEED;
	upx = ox / PIXELSIZE / CHARSPEED;
	if (mlx.map_info->map[upy] && mlx.map_info->map[upy][upx] == '1')
		put_pixel(img, upx * PIXELSIZE, upy * PIXELSIZE, '1');
	else if (mlx.map_info->map[upy] && mlx.map_info->map[upy][upx] == '0')
		put_pixel(img, upx * PIXELSIZE, upy * PIXELSIZE, '0');
}

int put_color(t_mlx *mlx)
{
	t_img	img;

	img.mlx = *mlx;
	if (mlx->up == 1)
	{
		map_refresh(*mlx, mlx->x, mlx->y);
		put_pixel(img, mlx->x / CHARSPEED, mlx->y-- / CHARSPEED, 'p');
	}
	if (mlx->down == 1)
	{
		map_refresh(*mlx, mlx->x, mlx->y);
		put_pixel(img, mlx->x / CHARSPEED, mlx->y++ / CHARSPEED, 'p');
	}
	if (mlx->left == 1)
	{
		map_refresh(*mlx, mlx->x, mlx->y);
		put_pixel(img, mlx->x-- / CHARSPEED, mlx->y / CHARSPEED, 'p');
	}
	if (mlx->right == 1)
	{
		map_refresh(*mlx, mlx->x, mlx->y);
		put_pixel(img, mlx->x++ / CHARSPEED, mlx->y / CHARSPEED, 'p');
	}
	return (0);
}

void	cub(t_mlx mlx)
{
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, WINWIDTH, WINHEIGHT, "cub3D");
	// create_map(mlx);
	mlx_hook(mlx.win, 17, 1L << 2, close_window, &mlx);
	mlx_hook(mlx.win, 2, 1L << 0, key_press, &mlx);
	// mlx_loop_hook(mlx.mlx, put_color, &mlx);
	// mlx_hook(mlx.win, 3, 1L << 1, key_release, &mlx);
	mlx_pixel_put(mlx.mlx, mlx.win, 60, 60, mlx.map_info->f);
	mlx_pixel_put(mlx.mlx, mlx.win, 80, 80, mlx.map_info->c);
	mlx_loop(mlx.mlx);
}

void	ft_free(t_map *map_info)
{
	int	i = -1;
	if (map_info->no)
		free(map_info->no);
	if (map_info->so)
		free(map_info->so);
	if (map_info->we)
		free(map_info->we);
	if (map_info->ea)
		free(map_info->ea);
	while (map_info->map[++i])
		free(map_info->map[i]);
	free(map_info->map);
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;
	t_map	map_info;

	mlx.x = 60 * CHARSPEED;
	mlx.y = 60 * CHARSPEED;
	mlx.map_info = &map_info;
	if (argc != 2 || check_map_spell(argv))
		exit(0);
	if (map_scan(mlx.map_info, argv[1]))
		exit(0);
	cub(mlx);
	ft_free(mlx.map_info);
	return (0);
}
