#include "cub3D.h"

// small_map.c

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
				draw_rect(game, vector_init(x * 10 + 5, y * 10 + 5), vector_init(10, 10), MWHITE);
			else if (game->map_info->map[y][x] == '0')
				draw_rect(game, vector_init(x * 10 + 5, y * 10 + 5), vector_init(10, 10), MBLACK);
			x++;
		}
		y++;
	}
}
