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
** map の描画
** 簡易的に25 * 25 のマップを描画
** 1: ■ 0: 空白
**	"1111111111111111111111111"
**	"1000000000110000000000001"
**	"1011000001110000002000001"
**	"1001000000000000000000001"
**	"1111111110110000011111111"
**	"1000000000110000010000001"
**	"1011101000000000010000001"
**	"1011101111111111110000001"
**	"1000000000000000010000001"
**	"1111111111111111111111111"
*/
void	draw_map(t_game *game)
{
	char	*mapstr = "\
				1111111111111111111111111\
				1000000000110000000000001\
				1011000001110000002000001\
				1001000000000000000000001\
				1111111110110000011111111\
				1000000000110000010000001\
				1011101000000000010000001\
				1011101111111111110000001\
				1000000000000000010000001\
				1111111111111111111111111";
	int		x;
	int		y;

	y = 0;
	x = 0;
	while (y < 10)
	{
		x = 0;
		while (x < 25)
		{
			if (mapstr[y * 25 + x] == '1')
				draw_square(game, x * 25, y * 25, 25, 0x00FF00);
			else
				draw_square(game, x * 25, y * 25, 25, 0x000000);
			x++;
		}
		y++;
	}
}

void	draw_square(t_game *game, int x, int y, int size, int color)
{
	int		i;
	int		j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			mlx_pixel_put(game->mlx, game->win, x + i, y + j, color);
			j++;
		}
		i++;
	}
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
			while (ray.pos.x < end.x)
			{
				mlx_pixel_put(game->mlx, game->win, ray.pos.x, line_calc_y(line, ray.pos.x), color);
				ray.pos.x++;
			}
		else
			while (ray.pos.x > end.x)
			{
				mlx_pixel_put(game->mlx, game->win, ray.pos.x, line_calc_y(line, ray.pos.x), color);
				ray.pos.x--;
			}
	}
	else
	{
		if (ray.dir.y > 0)
			while (ray.pos.y < end.y)
			{
				mlx_pixel_put(game->mlx, game->win, line_calc_x(line, ray.pos.y), ray.pos.y, color);
				ray.pos.y++;
			}
		else
			while (ray.pos.y > end.y)
			{
				mlx_pixel_put(game->mlx, game->win, line_calc_x(line, ray.pos.y), ray.pos.y, color);
				ray.pos.y--;
			}
	}
}
