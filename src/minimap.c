#include "cub3D.h"

// small_map.c

/*
** ミニマップの初期化
** game: ゲーム構造体
*/
void	init_minimap(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map_info->map[y])
	{
		x = 0;
		while (game->map_info->map[y][x])
		{
			if (game->map_info->map[y][x] == '1')
				draw_rect(game,
					vector_init(x * MINIMAP_RECT_SIZE + MINIMAP_RECT_SIZE_HALF, y * MINIMAP_RECT_SIZE + MINIMAP_RECT_SIZE_HALF),
					vector_init(MINIMAP_RECT_SIZE, MINIMAP_RECT_SIZE),
					MWHITE);
			else if (game->map_info->map[y][x] == '0')
			{
				x++;
				continue;
			}
				// draw_rect(game,
				// 	vector_init(x * MINIMAP_RECT_SIZE + MINIMAP_RECT_SIZE_HALF, y * MINIMAP_RECT_SIZE + MINIMAP_RECT_SIZE_HALF),
				// 	vector_init(MINIMAP_RECT_SIZE, MINIMAP_RECT_SIZE),
				// 	MBLACK);
			else if (game->map_info->map[y][x] == 'N' || game->map_info->map[y][x] == 'S' || game->map_info->map[y][x] == 'W' || game->map_info->map[y][x] == 'E')
				game->player = player_init(vector_init(x * MINIMAP_RECT_SIZE + MINIMAP_RECT_SIZE_HALF, y * MINIMAP_RECT_SIZE + MINIMAP_RECT_SIZE_HALF), game->map_info->map[y][x], PLAYER_SPEED);
			x++;
		}
		y++;
	}
}

/*
** ミニマップの表示
** game: ゲーム構造体
*/
void	put_minimap(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map_info->map[y])
	{
		x = 0;
		while (game->map_info->map[y][x])
		{
			if (game->map_info->map[y][x] == '1')
				draw_rect(game,
					vector_init(x * MINIMAP_RECT_SIZE + MINIMAP_RECT_SIZE_HALF, y * MINIMAP_RECT_SIZE + MINIMAP_RECT_SIZE_HALF),
					vector_init(MINIMAP_RECT_SIZE, MINIMAP_RECT_SIZE),
					MWHITE);
			else if (game->map_info->map[y][x] == '0')
				draw_rect(game,
					vector_init(x * MINIMAP_RECT_SIZE + MINIMAP_RECT_SIZE_HALF, y * MINIMAP_RECT_SIZE + MINIMAP_RECT_SIZE_HALF),
					vector_init(MINIMAP_RECT_SIZE, MINIMAP_RECT_SIZE),
					MBLACK);
			x++;
		}
		y++;
	}
}

/*
** ミニマップとプレイヤーの描画
** game: ゲーム構造体
** player: プレイヤー構造体
*/
void	minimap(t_game *game)
{
	put_minimap(game);
	draw_player(game, &game->player);
}