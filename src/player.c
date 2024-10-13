#include "cub3D.h"

// player.c

/*
** プレイヤーの初期化
** x, y: プレイヤーの初期位置
** angle: プレイヤーの初期角度
** speed: プレイヤーの移動速度
*/
t_player	player_init(double x, double y, double angle, double speed)
{
	t_player	ret;

	ret.pos.x = x;
	ret.pos.y = y;
	ret.dir = vector_from_angle(angle);
	ret.angle = angle;
	ret.speed = speed;
	return (ret);
}

/*
** プレイヤーを描画する関数
** 半径5の円を描画
** プレイヤーの視界は3radianごとに線を引く (60度)
** プレイヤーの向きは赤い線で表示
** game: ゲーム構造体
** player: プレイヤー構造体
*/
void	drow_player(t_game *game, t_player *player)
{
	int		x;
	t_vector	dir;

	// まず画面をクリア
	mlx_clear_window(game->mlx, game->win);
	// プレイヤーの描画
	x = -5;
	while (x < 6)
	{
		mlx_pixel_put(game->mlx, game->win, player->pos.x + x, player->pos.y, 0x00FF0000);
		mlx_pixel_put(game->mlx, game->win, player->pos.x, player->pos.y + x, 0x00FF0000);
		x++;
	}
	// プレイヤーの向き
	dir = vector_mul(player->dir, 50);
	mlx_pixel_put(game->mlx, game->win, player->pos.x, player->pos.y, 0x00FF0000);
	mlx_pixel_put(game->mlx, game->win, player->pos.x + dir.x, player->pos.y + dir.y, 0x00FF0000);
	// プレイヤーの視界
	x = 0;
	while (x < 60)
	{
		dir = vector_rotate(player->dir, x * M_PI / 180);
		mlx_pixel_put(game->mlx, game->win, player->pos.x + dir.x * 100, player->pos.y + dir.y * 100, 0x00FF0000);
		x++;
	}
	x = 0;
	while (x > -60)
	{
		dir = vector_rotate(player->dir, x * M_PI / 180);
		mlx_pixel_put(game->mlx, game->win, player->pos.x + dir.x * 100, player->pos.y + dir.y * 100, 0x00FF0000);
		x--;
	}
}

/*
** プレイヤーを動かす関数
** UP: プレイヤーを前進させる
** DOWN: プレイヤーを後退させる
** LEFT: プレイヤーを左に移動させる
** RIGHT: プレイヤーを右に移動させる
** UP_ARROW: プレイヤーを右に回転させる
** DOWN_ARROW: プレイヤーを左に回転させる
** player: プレイヤー構造体
** keycode: キーコード
*/
int	key_hook(int keycode, t_game *game)
{
	t_player	*player;

	player = &game->player;
	if (keycode == ESC)
		window_exit(game);
	if (keycode == UP)
	{
		player->pos.x += player->dir.x * player->speed;
		player->pos.y += player->dir.y * player->speed;
	}
	if (keycode == DOWN)
	{
		player->pos.x -= player->dir.x * player->speed;
		player->pos.y -= player->dir.y * player->speed;
	}
	if (keycode == LEFT)
	{
		player->pos.x += player->dir.y * player->speed;
		player->pos.y -= player->dir.x * player->speed;
	}
	if (keycode == RIGHT)
	{
		player->pos.x -= player->dir.y * player->speed;
		player->pos.y += player->dir.x * player->speed;
	}
	if (keycode == RIGHT_ARROW)
		player->dir = vector_rotate(player->dir, 0.1);
	if (keycode == LEFT_ARROW)
		player->dir = vector_rotate(player->dir, -0.1);
	drow_player(game, player);
	return (0);
}
