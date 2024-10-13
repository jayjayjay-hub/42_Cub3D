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

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

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
t_vector	vector_reject(t_vector a, t_vector b);
t_vector	vector_rotate(t_vector a, double angle);

#endif