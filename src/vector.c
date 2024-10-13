#include "cub3D.h"

// vector.c

t_vector	vector_add(t_vector a, t_vector b)
{
	/*
	** ベクトルの足し算
	** a = (a.x, a.y)
	** b = (b.x, b.y)
	** a + b = (a.x + b.x, a.y + b.y)
	*/
	t_vector	ret;

	ret.x = a.x + b.x;
	ret.y = a.y + b.y;
	return (ret);
}

t_vector	vector_sub(t_vector a, t_vector b)
{
	/*
	** ベクトルの引き算
	** a = (a.x, a.y)
	** b = (b.x, b.y)
	** a - b = (a.x - b.x, a.y - b.y)
	*/
	t_vector	ret;

	ret.x = a.x - b.x;
	ret.y = a.y - b.y;
	return (ret);
}

t_vector	vector_mul(t_vector a, double b)
{
	/*
	** ベクトルのスカラー倍
	** a = (a.x, a.y)
	** b = スカラー
	** a * b = (a.x * b, a.y * b)
	*/
	t_vector	ret;

	ret.x = a.x * b;
	ret.y = a.y * b;
	return (ret);
}

t_vector	vector_div(t_vector a, double b)
{
	/*
	** ベクトルのスカラー倍
	** a = (a.x, a.y)
	** b = スカラー
	** a / b = (a.x / b, a.y / b)
	*/
	t_vector	ret;

	ret.x = a.x / b;
	ret.y = a.y / b;
	return (ret);
}

double	vector_len(t_vector a)
{
	/*
	** ベクトルの長さ
	** a = (a.x, a.y)
	** |a| = √(a.x^2 + a.y^2)
	*/
	return (sqrt(a.x * a.x + a.y * a.y));
}

t_vector	vector_normalize(t_vector a)
{
	/*
	** ベクトルの正規化 (長さを1にする)
	** a = (a.x, a.y)
	** |a| = √(a.x^2 + a.y^2)
	** a / |a| = (a.x / |a|, a.y / |a|)
	*/
	double	len;

	len = vector_len(a);
	return (vector_div(a, len));
}

double	vector_dot(t_vector a, t_vector b)
{
	/*
	** ベクトルの内積
	** a = (a.x, a.y)
	** b = (b.x, b.y)
	** a・b = a.x * b.x + a.y * b.y
	*/
	return (a.x * b.x + a.y * b.y);
}

double	vector_cross(t_vector a, t_vector b)
{
	/*
	** ベクトルの外積
	** a = (a.x, a.y)
	** b = (b.x, b.y)
	** a×b = a.x * b.y - a.y * b.x
	*/
	return (a.x * b.y - a.y * b.x);
}

t_vector	vector_rotate(t_vector a, double angle)
{
	/*
	** ベクトルの回転
	** a = (a.x, a.y)
	** angle = 回転角度
	** (a.x * cos(angle) - a.y * sin(angle), a.x * sin(angle) + a.y * cos(angle))
	*/
	t_vector	ret;

	ret.x = a.x * cos(angle) - a.y * sin(angle);
	ret.y = a.x * sin(angle) + a.y * cos(angle);
	return (ret);
}

t_vector	vector_from_angle(double angle)
{
	/*
	** 角度からベクトルを作成
	** angle = 角度
	** (cos(angle), sin(angle))
	*/
	t_vector	ret;

	ret.x = cos(angle);
	ret.y = sin(angle);
	return (ret);
}

double	vector_angle(t_vector a)
{
	/*
	** ベクトルの角度
	** a = (a.x, a.y)
	** atan2(a.y, a.x)
	*/
	return (atan2(a.y, a.x));
}

t_vector	vector_from_to(t_vector from, t_vector to)
{
	/*
	** 2点間のベクトル
	** from = (from.x, from.y)
	** to = (to.x, to.y)
	** to - from = (to.x - from.x, to.y - from.y)
	*/
	t_vector	ret;

	ret.x = to.x - from.x;
	ret.y = to.y - from.y;
	return (ret);
}

t_vector	vector_reflect(t_vector a, t_vector normal)
{
	/*
	** ベクトルの反射
	** a = (a.x, a.y)
	** normal = 法線ベクトル
	** a - 2 * (a・normal) * normal
	*/
	return (vector_sub(a, vector_mul(normal, 2 * vector_dot(a, normal))));
}

t_vector	vector_project(t_vector a, t_vector b)
{
	/*
	** ベクトルの射影
	** a = (a.x, a.y)
	** b = (b.x, b.y)
	** (a・b / |b|^2) * b
	*/
	return (vector_mul(b, vector_dot(a, b) / vector_dot(b, b)));
}

t_vector	vector_reject(t_vector a, t_vector b)
{
	/*
	** ベクトルの拒絶
	** a = (a.x, a.y)
	** b = (b.x, b.y)
	** a - (a・b / |b|^2) * b
	*/
	return (vector_sub(a, vector_project(a, b)));
}
