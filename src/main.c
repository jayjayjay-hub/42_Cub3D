#include "cub3D.h"

// 画面に点を表示する関数だけのプログラム
int main(void)
{
	// 画面の大きさを指定
	int width = 640;
	int height = 480;
	// 画面の大きさを指定
	void *mlx = mlx_init();
	void *win = mlx_new_window(mlx, width, height, "mlx 42");
	// 画面の大きさを指定
	int x = width / 2;
	int y = height / 2;
	// 画面の大きさを指定
	mlx_pixel_put(mlx, win, x, y, 0x00FF0000);
	mlx_loop(mlx);
	return (0);
}
