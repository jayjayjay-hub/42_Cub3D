#include "cub3D.h"

// raycasting.c

void	check_wall(t_game *game, t_line_segment ray, int num)
{
	t_line_segment	segment_1;
	t_line_segment	segment_2;
	t_line_segment	segment_3;
	t_vector		intersection;

	segment_1 = line_segment_init(vector_init(300, 0), vector_init(300, 300));
	segment_2 = line_segment_init(vector_init(0, 300), vector_init(300, 300));
	segment_3 = line_segment_init(vector_init(300, 0), vector_init(0, 300));
	intersection = line_intersection(ray, segment_1);
	if (intersection.x != -1 && intersection.y != -1)
	{
		draw_circle(game, intersection.x, intersection.y, 3, MWHITE);
		draw_wall(game, num, vector_len(vector_from_to(ray.start, intersection)));
	}
	intersection = line_intersection(ray, segment_2);
	if (intersection.x != -1 && intersection.y != -1)
	{
		draw_circle(game, intersection.x, intersection.y, 3, MWHITE);
		draw_wall(game, num, vector_len(vector_from_to(ray.start, intersection)));
	}
	intersection = line_intersection(ray, segment_3);
	if (intersection.x != -1 && intersection.y != -1)
	{
		draw_circle(game, intersection.x, intersection.y, 3, MWHITE);
		draw_wall(game, num, vector_len(vector_from_to(ray.start, intersection)));
	}
}

/*
** レイキャスティング
** プレイヤーの視界に沿ってレイを飛ばし、壁との交点を求める
** game: ゲーム構造体
** player: プレイヤー構造体
*/
void	raycasting(t_game *game, t_player *player)
{
	t_line_segment	ray;
	double	angle_step;
	t_vector	dir;
	int		x;

	x = 1;
	angle_step = (M_PI / 3) / 20; // 60度（π/3）を20分割
	ray = ray_to_segment(ray_init(player->pos, player->dir), 150);
	check_wall(game, ray, 0);
	while (x <= 20)
	{
		dir = vector_rotate(player->dir, x * angle_step);
		ray = ray_to_segment(ray_init(player->pos, dir), 150);
		check_wall(game, ray, x);
		dir = vector_rotate(player->dir, -x * angle_step);
		ray = ray_to_segment(ray_init(player->pos, dir), 150);
		check_wall(game, ray, x * -1);
		x++;
	}
}

/*
** 壁を描画する関数
** game: ゲーム構造体
** num: レイの番号
** distance: 壁までの距離
*/
void	draw_wall(t_game *game, int num, double distance)
{
	t_vector	start;
	t_vector	size;
	double		rate;

	printf("distance: %f\n", distance);
	rate = 300 / (distance * 0.005);
	start = vector_init(1000, 300);
	size = vector_init(10, rate);
	start.x += num * 20;
	draw_rect(game, start, size, MBLUE);
}
