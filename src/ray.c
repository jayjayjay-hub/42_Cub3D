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

/*
** レイの始点
** ray: レイ
** ray.pos
*/
t_vector	ray_begin(t_ray ray)
{
	return (ray.pos);
}

/*
** レイの終点
** ray: レイ
** ray.pos + ray.dir
*/
t_vector	ray_end(t_ray ray)
{
	return (vector_add(ray.pos, ray.dir));
}
