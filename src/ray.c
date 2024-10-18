#include "cub3D.h"

// ray.c

/*
** レイの初期化
** pos: レイの始点
** dir: レイの方向
*/
t_ray	ray_init(t_vector pos, t_vector dir)
{
	t_ray	ret;

	ret.pos = pos;
	ret.dir = dir;
	return (ret);
}
