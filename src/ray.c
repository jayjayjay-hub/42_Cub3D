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
** レイの直線を求める関数
** ray: レイ構造体
*/
t_line	ray_to_line(t_ray ray)
{
	t_line	ret;

	if (ray.dir.x == 0)
	{
		ret.inclination = 0;
		ret.intercept = ray.pos.x;
		return (ret);
	}
	ret.inclination = ray.dir.y / ray.dir.x;
	ret.intercept = ray.pos.y - ret.inclination * ray.pos.x;
	return (ret);
}

/*
** レイから線分を求める関数
** ray: レイ構造体
** length: 線分の長さ
*/
t_line_segment	ray_to_segment(t_ray ray, double length)
{
	t_line_segment	ret;

	ret.start = ray.pos;
	ret.end.x = ray.pos.x + ray.dir.x * length;
	ret.end.y = ray.pos.y + ray.dir.y * length;
	ret.line = ray_to_line(ray);
	return (ret);
}
