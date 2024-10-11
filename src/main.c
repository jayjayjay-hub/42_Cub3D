/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:09:37 by jtakahas          #+#    #+#             */
/*   Updated: 2024/10/09 13:51:33 by kosnakam         ###   ########.fr       */
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
			if (mlx.map[y] && mlx.map[y][x] == '1')
			{
				put_pixel(img, x * PIXELSIZE, y * PIXELSIZE, '1');
			}
			if (mlx.map[y] && mlx.map[y][x] == '0')
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
	if (mlx.map[upy] && mlx.map[upy][upx] == '1')
		put_pixel(img, upx * PIXELSIZE, upy * PIXELSIZE, '1');
	else if (mlx.map[upy] && mlx.map[upy][upx] == '0')
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
	create_map(mlx);
	mlx_hook(mlx.win, 17, 1L << 2, close_window, &mlx);
	mlx_hook(mlx.win, 2, 1L << 0, key_press, &mlx);
	mlx_loop_hook(mlx.mlx, put_color, &mlx);
	mlx_hook(mlx.win, 3, 1L << 1, key_release, &mlx);
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
