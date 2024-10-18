/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:09:37 by jtakahas          #+#    #+#             */
/*   Updated: 2024/10/18 17:13:06 by kosnakam         ###   ########.fr       */
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
	if (pixel == '0')
		img.relative_path = "./img/0.xpm";
	else if (pixel == '1')
		img.relative_path = "./img/1.xpm";
	else if (pixel == 'p')
		img.relative_path = "./img/p.xpm";
	img.img = mlx_xpm_file_to_image(img.mlx->mlx,
			img.relative_path, &img.img_width, &img.img_height);
	mlx_put_image_to_window(img.mlx->mlx, img.mlx->win, img.img, x, y);
}

void	put_map(t_mlx mlx)
{
	int	x = 0;
	int	y = 0;

    for (y = 0; y < MAPHEIGHT; y++)
    {
        for (x = 0; x < MAPWIDTH; x++)
        {
            // ピクセルを img_data に設定
            *(int *)(mlx.img->data + (y * mlx.img->size_line + x * (mlx.img->bpp / 8))) = mlx.map_info->f;
        }
    }
    // 画像をウィンドウに表示
    mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img->img, 0, 0);
}

int routine(t_mlx *mlx)
{
	t_img	img;

	img.mlx = mlx;
	if (mlx->up == 1)
	{
		// map_refresh(*mlx, mlx->x, mlx->y);
		put_map(*mlx);
		mlx_pixel_put(mlx->mlx, mlx->win, mlx->x, mlx->y--, 0);
		// put_pixel(img, mlx->x / CHARSPEED, mlx->y-- / CHARSPEED, 'p');
	}
	if (mlx->down == 1)
	{
		// map_refresh(*mlx, mlx->x, mlx->y);
		put_map(*mlx);
		mlx_pixel_put(mlx->mlx, mlx->win, mlx->x, mlx->y++, 0);
		// put_pixel(img, mlx->x / CHARSPEED, mlx->y++ / CHARSPEED, 'p');
	}
	if (mlx->left == 1)
	{
		// map_refresh(*mlx, mlx->x, mlx->y);
		put_map(*mlx);
		mlx_pixel_put(mlx->mlx, mlx->win, mlx->x--, mlx->y, 0);
		// put_pixel(img, mlx->x-- / CHARSPEED, mlx->y / CHARSPEED, 'p');
	}
	if (mlx->right == 1)
	{
		// map_refresh(*mlx, mlx->x, mlx->y);
		put_map(*mlx);
		mlx_pixel_put(mlx->mlx, mlx->win, mlx->x++, mlx->y, 0);
		// put_pixel(img, mlx->x++ / CHARSPEED, mlx->y / CHARSPEED, 'p');
	}
	return (0);
}

void	cub(t_mlx mlx)
{
	t_img	img;

	img.mlx = &mlx;
	mlx.img = &img;
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, WINWIDTH, WINHEIGHT, "cub3D");
	img.img = mlx_new_image(mlx.mlx, MAPWIDTH, MAPHEIGHT);
	img.data = mlx_get_data_addr(img.img, &img.bpp, &img.size_line, &img.endian);
	put_map(mlx);
	mlx_hook(mlx.win, 17, 1L << 2, close_window, &mlx);
	mlx_hook(mlx.win, 2, 1L << 0, key_press, &mlx);
	mlx_loop_hook(mlx.mlx, routine, &mlx);
	mlx_hook(mlx.win, 3, 1L << 1, key_release, &mlx);
	// mlx_pixel_put(mlx.mlx, mlx.win, 60, 60, mlx.map_info->f);
	// mlx_pixel_put(mlx.mlx, mlx.win, 80, 80, mlx.map_info->c);
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

	mlx.x = 60;
	mlx.y = 60;
	mlx.map_info = &map_info;
	if (argc != 2 || check_map_spell(argv))
		exit(0);
	if (map_scan(mlx.map_info, argv[1]))
		exit(0);
	cub(mlx);
	ft_free(mlx.map_info);
	return (0);
}
