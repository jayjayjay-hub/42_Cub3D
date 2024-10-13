/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:09:37 by jtakahas          #+#    #+#             */
/*   Updated: 2024/10/09 15:58:46by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

typedef struct s_player
{
	double	x;
	double	y;
	double	angle;
	double	speed;
	void	*mlx;
	void	*win;
}	t_player;

#define M_PI_2 1.57079632679489661923
#define M_PI 3.14159265358979323846

// プレイヤーを描画する関数 (5 * 5 の正方形 + 視野90度の線)
void	drow_player(void *mlx, void *win, t_player *player)
{
	// まず画面をクリア
	mlx_clear_window(mlx, win);
	int	x;
	int	y;

	y = -2;
	while (++y < 3)
	{
		x = -2;
		while (++x < 3)
			mlx_pixel_put(mlx, win, player->x + x - 1, player->y + y - 1, 0x00FF0000);
	}
	x = 0;
	// angle から 45度ずつ左右に線を引く
	while (x < 45)
	{
		mlx_pixel_put(mlx, win, player->x + cos(player->angle + x * M_PI / 180) * 100, player->y + sin(player->angle + x * M_PI / 180) * 100, 0x00FF0000);
		mlx_pixel_put(mlx, win, player->x + cos(player->angle - x * M_PI / 180) * 100, player->y + sin(player->angle - x * M_PI / 180) * 100, 0x00FF0000);
		x++;
	}
}

// プレイヤーを動かす関数
int	key_hook(int keycode, t_player *player)
{
	if (keycode == UP)
	{
		printf("UP\n");
		player->x += cos(player->angle) * player->speed;
		player->y += sin(player->angle) * player->speed;
	}
	if (keycode == DOWN)
	{
		printf("DOWN\n");
		player->x -= cos(player->angle) * player->speed;
		player->y -= sin(player->angle) * player->speed;
	}
	if (keycode == LEFT)
	{
		printf("LEFT\n");
		player->x += cos(player->angle - M_PI_2) * player->speed;
		player->y += sin(player->angle - M_PI_2) * player->speed;
	}
	if (keycode == RIGHT)
	{
		printf("RIGHT\n");
		player->x += cos(player->angle + M_PI_2) * player->speed;
		player->y += sin(player->angle + M_PI_2) * player->speed;
	}
	if (keycode == UP_ARROW)
		player->angle += 0.1;
	if (keycode == DOWN_ARROW)
		player->angle -= 0.1;
	if (keycode == LEFT_ARROW)
		player->angle -= 0.1;
	if (keycode == RIGHT_ARROW)
		player->angle += 0.1;
	drow_player(player->mlx, player->win, player);
	return (0);
}

void	init_player(t_player *player, void *mlx, void *win)
{
	player->x = 400;
	player->y = 400;
	player->angle = M_PI_2 * 3;
	player->speed = 10;
	player->mlx = mlx;
	player->win = win;
}

int	close_window(void *mlx, void *win)
{
	mlx_destroy_window(mlx, win);
	exit(0);
}

int	main(void)
{
	void	*mlx;
	void	*win;
	t_player	player;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 800, 800, "Hello world!");
	init_player(&player, mlx, win);
	drow_player(mlx, win, &player);
	mlx_hook(win, 2, 1L << 0, key_hook, &player);
	mlx_loop(mlx);
	return (0);
}
