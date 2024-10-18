#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"

# include "mlx.h"

# include <fcntl.h>
# include <math.h>
# include <stdio.h>

# ifdef __APPLE__
// key code for mac
#  define ESC 53
#  define UP 13
#  define DOWN 1
#  define LEFT 0
#  define RIGHT 2
#  define UP_ARROW 126
#  define DOWN_ARROW 125
#  define LEFT_ARROW 123
#  define RIGHT_ARROW 124
#  define DESTROYNOTIFY 17
// 1L << 17
#  define STRUCTURENOTIFYMASK 131072
# endif

# ifdef __linux__
// include for linux miniLibX
#  include <X11/X.h>
#  include <X11/keysym.h>
// key code for linux
#  define ESC 65307
#  define UP 119
#  define DOWN 115
#  define LEFT 97
#  define RIGHT 100
#  define UP_ARROW 65362
#  define DOWN_ARROW 65364
#  define LEFT_ARROW 65361
#  define RIGHT_ARROW 65363
#  define DESTROYNOTIFY DestroyNotify
#  define STRUCTURENOTIFYMASK StructureNotifyMask
# endif

# define TILE_SIZE 64
# define BACKGROUND_SIZE 256

# define M_PI 3.14159265358979323846
# define M_PI_2 1.57079632679489661923

# define WIN_WIDTH 640
# define WIN_HEIGHT 480

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_ray
{
	/*
	** レイ (光線)
	** レイの始点
	** x, y: 始点の座標
	*/
	t_vector	pos; // rayの視点からの位置ベクトル
	t_vector	dir; // rayの方向ベクトル
}	t_ray;

typedef struct s_line
{
	double	inclination;
	double	intercept;
}	t_line;

typedef struct s_player
{
	t_vector	pos;
	t_vector	dir;
	double		angle; // radian
	double		speed;
}	t_player;

typedef struct s_texture
{
	void	*img;
	int		*data;
	int		width;
	int		height;
}	t_texture;

typedef struct s_map
{
	int		width;
	int		height;
	char	**data;
}	t_map;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_player	player;
	t_texture	north;
	t_texture	south;
	t_texture	west;
	t_texture	east;
	t_texture	ceiling;
	t_texture	floor;
	t_map		map;
}	t_game;

/* main.c (メイン関数) */

int			game_update(t_game *game);

/* vector.c (ベクトルの計算) */

t_vector	vector_add(t_vector a, t_vector b);
t_vector	vector_sub(t_vector a, t_vector b);
t_vector	vector_mul(t_vector a, double b);
t_vector	vector_div(t_vector a, double b);
t_vector	vector_normalize(t_vector a);
double		vector_len(t_vector a);
double		vector_dot(t_vector a, t_vector b);
double		vector_cross(t_vector a, t_vector b);
t_vector	vector_from_to(t_vector from, t_vector to);
t_vector	vector_reflect(t_vector a, t_vector normal);
t_vector	vector_project(t_vector a, t_vector b);
t_vector	vector_rotate(t_vector a, double angle);
t_vector	vector_from_angle(double angle);

/* ray.c (レイの計算) */

t_ray		ray_init(t_vector pos, t_vector dir);
void		draw_ray(t_game *game, t_ray ray, double length, int color);

/* player.c (プレイヤーの計算) */

t_player	player_init(double x, double y, double angle, double speed);
void		draw_player(t_game *game, t_player *player);
int			key_hook(int keycode, t_game *game);

/* window.c (ウィンドウの計算) */

void	window_init(t_game *game);
void	window_exit(t_game *game);
void	draw_map(t_game *game);
void	draw_square(t_game *game, int x, int y, int size, int color);
void	mlx_line_put(t_game *game, t_ray ray, double length, int color);

/* line.c (直線の計算) */

t_line	line_from_points(t_vector vec1, t_vector vec2);
double	line_calc_y(t_line line, double x);
double	line_calc_x(t_line line, double y);


#endif