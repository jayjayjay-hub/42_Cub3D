#include "cub3D.h"

// window.c

/*
** ウィンドウの初期化
** game: ゲーム構造体
*/
void	window_init(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
}

/*
** ウィンドウの削除
** game: ゲーム構造体
*/
void	window_exit(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
}

/*
** 線分の描画
** game: ゲーム構造体
** t_ray: レイ構造体 (始点と方向)
** length: 線分の長さ
** color: 色
*/
void	mlx_line_put(t_game *game, t_ray ray, double length, int color)
{
	t_vector	end;
	t_line		line;

	end.x = ray.pos.x + ray.dir.x * length;
	end.y = ray.pos.y + ray.dir.y * length;
	line = line_from_points(ray.pos, end);
	if (fabs(ray.dir.x) > fabs(ray.dir.y))
	{
		if (ray.dir.x > 0)
		{
			while (ray.pos.x < end.x)
			{
				mlx_pixel_put(game->mlx, game->win, ray.pos.x, line_calc_y(line,
						ray.pos.x), color);
				ray.pos.x++;
			}
		}
		else
		{
			while (ray.pos.x > end.x)
			{
				mlx_pixel_put(game->mlx, game->win, ray.pos.x, line_calc_y(line,
						ray.pos.x), color);
				ray.pos.x--;
			}
		}
	}
	else
	{
		if (ray.dir.y > 0)
		{
			while (ray.pos.y < end.y)
			{
				mlx_pixel_put(game->mlx, game->win, line_calc_x(line,
						ray.pos.y), ray.pos.y, color);
				ray.pos.y++;
			}
		}
		else
		{
			while (ray.pos.y > end.y)
			{
				mlx_pixel_put(game->mlx, game->win, line_calc_x(line,
						ray.pos.y), ray.pos.y, color);
				ray.pos.y--;
			}
		}
	}
}

/*
** 円の描画
** game: ゲーム構造体
** point: 円の中心座標(t_vector.x: x座標, t_vector.y: y座標)
** radius: 半径
** color: 色
*/
void	draw_circle(t_game *game, t_vector point, int radius, int color)
{
	int	i;
	int	j;

	i = -radius;
	while (i < radius)
	{
		j = -radius;
		while (j < radius)
		{
			if (i * i + j * j < radius * radius)
				mlx_pixel_put(game->mlx, game->win, point.x + i, point.y + j,
					color);
			j++;
		}
		i++;
	}
}

/*
** 長方形の描画（塗りつぶし）
** game: ゲーム構造体
** pos: 長方形の真ん中の座標
** size: 長方形の大きさ (t_vector.x: 幅, t_vector.y: 高さ)
** color: 色
*/
void	draw_rect(t_game *game, t_vector pos, t_vector size, int color)
{
	int	i;
	int	j;

	i = -size.x / 2;
	while (i < size.x / 2)
	{
		j = -size.y / 2;
		while (j < size.y / 2)
		{
			mlx_pixel_put(game->mlx, game->win, pos.x + i, pos.y + j, color);
			j++;
		}
		i++;
	}
}
