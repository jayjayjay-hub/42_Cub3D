#include "cub3D.h"

// line.c

/*
** 2点間の直線を求める関数
** vec1: 点1
** vec2: 点2
*/
t_line	line_from_points(t_vector vec1, t_vector vec2)
{
	t_line	ret;

	if (vec2.x - vec1.x == 0)
	{
		ret.inclination = 0;
		ret.intercept = vec1.x;
		return (ret);
	}
	ret.inclination = (vec2.y - vec1.y) / (vec2.x - vec1.x);
	ret.intercept = vec1.y - ret.inclination * vec1.x;
	return (ret);
}

/*
** ｘ座標からy座標を求める関数
** line: 直線
** x: x座標
*/
double	line_calc_y(t_line line, double x)
{
	if (line.inclination == 0)
		return (line.intercept);
	return (line.inclination * x + line.intercept);
}

/*
** y座標からx座標を求める関数
** line: 直線
** y: y座標
*/
double	line_calc_x(t_line line, double y)
{
	if (line.inclination == 0)
		return (line.intercept);
	return ((y - line.intercept) / line.inclination);
}
