#include "cub3D.h"

// main.c

void	map_init(t_game *game)
{
	game->map.data = ft_split("1111111111111111111111111\n"
					"1000000000110000000000001\n"
					"1011000001110000002000001\n"
					"1001000000000000000000001\n"
					"1111111110110000011111111\n"
					"1000000000110000010000001\n"
					"1011101000000000010000001\n"
					"1011101111111111110000001\n"
					"1000000000000000010000001\n"
					"1111111111111111111111111", '\n');
	game->map.width = 25;
	game->map.height = 10;
}

/*
** ゲームの初期化
** mlxの初期化
** ウィンドウの作成
** プレイヤーの初期化
*/
void	game_init(t_game *game)
{
	window_init(game);
	game->player = player_init(200, 250, NORTH, 5);
	// 疑似的な壁
	mlx_line_put(game, ray_init(vector_init(300, 0), vector_init(0, 1)), 300, MGREEN);
	mlx_line_put(game, ray_init(vector_init(0, 300), vector_init(1, 0)), 300, MGREEN);
	mlx_line_put(game, ray_init(vector_init(300, 0), vector_init(-1, 1)), 500, MGREEN);
	draw_player(game, &game->player);
}

/*
** ゲームの更新
** プレイヤーの移動
** プレイヤーの描画
*/
int	game_update(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	// 疑似的な壁
	mlx_line_put(game, ray_init(vector_init(300, 0), vector_init(0, 1)), 300, MGREEN);
	mlx_line_put(game, ray_init(vector_init(0, 300), vector_init(1, 0)), 300, MGREEN);
	mlx_line_put(game, ray_init(vector_init(300, 0), vector_init(-1, 1)), 500, MGREEN);
	draw_player(game, &game->player);
	return (0);
}

/*
** ゲームのループ
** イベントの受け取り
** 描画
*/
void	game_loop(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, key_hook, game);
	mlx_loop(game->mlx);
}

/*
** メイン関数
** マップの読み込み
** ゲームの初期化
** ゲームのループ
*/
int	main(void)
{
	t_game	game;

	map_init(&game);
	game_init(&game);
	game_loop(&game);
	return (0);
}