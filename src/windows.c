#include "cub3D.h"

int	close_window(void *mlx, void *win)
{
	mlx_destroy_window(mlx, win);
	exit(0);
}