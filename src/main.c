#include "cub3D.h"

int check_map(char **argv)
{
	if (ft_strrchr(argv[1], '.') == 0
		|| ft_strcmp(ft_strrchr(argv[1], '.'), ".cub") != 0)
		return (1);
	return (0);
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
	raycasting(game, &game->player);
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
	raycasting(game, &game->player);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2 || check_map(argv))
		exit(0);
	game_init(&game);
	game_loop(&game);
	return (0);
}
