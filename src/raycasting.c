#include "cub3D.h"

// raycasting.c

void	check_wall(t_game *game, t_line_segment ray)
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
		draw_circle(game, intersection.x, intersection.y, 3, MWHITE);
	intersection = line_intersection(ray, segment_2);
	if (intersection.x != -1 && intersection.y != -1)
		draw_circle(game, intersection.x, intersection.y, 3, MWHITE);
	intersection = line_intersection(ray, segment_3);
	if (intersection.x != -1 && intersection.y != -1)
		draw_circle(game, intersection.x, intersection.y, 3, MWHITE);
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
	check_wall(game, ray);
	while (x <= 20)
	{
		dir = vector_rotate(player->dir, x * angle_step);
		ray = ray_to_segment(ray_init(player->pos, dir), 150);
		check_wall(game, ray);
		dir = vector_rotate(player->dir, -x * angle_step);
		ray = ray_to_segment(ray_init(player->pos, dir), 150);
		check_wall(game, ray);
		x++;
	}
}
