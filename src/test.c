// // #include "cub3D.h"
// // #include <math.h>

// // int main(void)
// // {
// // 		void	*mlx_ptr;
// // 		void	*win_ptr;
// // 		void	*img_ptr;
// // 		char	*img_data;
// // 		int	 bpp;
// // 		int	 size_line;
// // 		int	 endian;
// // 		int	 x, y;

// // 		// MiniLibX 初期化
// // 		mlx_ptr = mlx_init();

// // 		// ウィンドウの作成（幅800、高さ600）
// // 		win_ptr = mlx_new_window(mlx_ptr, 800, 600, "New Image Example");

// // 		// 新しい画像を作成（幅800、高さ600）
// // 		img_ptr = mlx_new_image(mlx_ptr, 800, 600);

// // 		// 画像データにアクセス
// // 		img_data = mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);
// // 	// ft_printf("bpp: %d\n", bpp);
// // 	// ft_printf("size_line: %d\n", size_line);
// // 	// ft_printf("endian: %d\n", endian);
// // 		// 画像にピクセルを描画（緑のピクセル）
// // 		for (y = 0; y < 600; y++)
// // 		{
// // 			for (x = 0; x < 800; x++)
// // 			{
// // 				// 座標 (x, y) に色を設定（16進数で #02A630 → RGB(2, 166, 48)）
// // 				int color = (2 << 16) | (166 << 8) | 48;
					// RGB値を結合して24ビットカラーにする
// // 				// ピクセルを img_data に設定
// // 				*(int *)(img_data + (y * size_line + x * (bpp / 8))) = color;
// // 			}
// // 		}

// // 		// 画像をウィンドウに表示
// // 		mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);

// // 		// イベントループ
// // 		mlx_loop(mlx_ptr);

// // 		return (0);
// // }

// // #define PI 3.14159265

// // // 回転させる角度（ラジアンで指定）
// // #define ANGLE 45 * (PI / 180)

// // int rotate_image(void *mlx_ptr, void *win_ptr, void *img_ptr,
	// int img_width, int img_height)
// // {
// // 		int x, y;
// // 		int new_x, new_y;
// // 		int color;
// // 		void *new_img_ptr;
// // 		char *new_img_data;
// // 		int bpp, size_line, endian;
// // 		int new_img_width = img_width;
// // 		int new_img_height = img_height;

// // 		// 新しい画像を作成
// // 		new_img_ptr = mlx_new_image(mlx_ptr, new_img_width, new_img_height);
// // 		new_img_data = mlx_get_data_addr(new_img_ptr, &bpp, &size_line,
				// &endian);

// // 		// 元の画像のピクセルデータを取得
// // 		char *img_data = mlx_get_data_addr(img_ptr, &bpp, &size_line,
				// &endian);

// // 		// ピクセルごとに新しい座標に配置
// // 		for (y = 0; y < img_height; y++)
// // 		{
// // 			for (x = 0; x < img_width; x++)
// // 			{
// // 				// 元の画像のピクセルカラーを取得
// // 				color = *(int *)(img_data + (y * size_line + x * (bpp / 8)));

// // 				// 回転後の座標を計算
// // 				new_x = (int)(cos(ANGLE) * x - sin(ANGLE) * y);
// // 				new_y = (int)(sin(ANGLE) * x + cos(ANGLE) * y);

// // 				// 新しい座標が画像の範囲内にあるか確認
// // 				if (new_x >= 0 && new_x < new_img_width && new_y >= 0
					// && new_y < new_img_height)
// // 				{
// // 					// 新しい画像にピクセルを設定
// // 					*(int *)(new_img_data + (new_y * size_line + new_x * (bpp
									// / 8))) = color;
// // 				}
// // 			}
// // 		}
// // 		// 新しい画像をウィンドウに表示
// // 		mlx_put_image_to_window(mlx_ptr, win_ptr, new_img_ptr, 400, 400);
// // 		return (0);
// // }

// // int main(void)
// // {
// // 		void *mlx_ptr;
// // 		void *win_ptr;
// // 		void *img_ptr;
// // 		int img_width, img_height;

// // 		// MiniLibX 初期化
// // 		mlx_ptr = mlx_init();
// // 		win_ptr = mlx_new_window(mlx_ptr, 800, 600, "Rotated Image");

// // 		// 画像の読み込み
// // 		img_ptr = mlx_xpm_file_to_image(mlx_ptr, "./img/eagle.xpm",
				// &img_width, &img_height);

// // 		// 画像の回転
// // 		rotate_image(mlx_ptr, win_ptr, img_ptr, img_width, img_height);

// // 		// イベントループ
// // 		mlx_loop(mlx_ptr);

// // 		return (0);
// // }

// #define BG_COLOR 0x02A630  // 背景の緑色

// // 画像の背景を緑色で塗りつぶし、XPM画像を貼り付ける関数
// void render_image_with_xpm(void *mlx_ptr, void *win_ptr, char *xpm_file)
// {
// 	int win_width = 800;
// 	int win_height = 600;
// 	int img_width = 64, img_height = 64;
// 	void *bg_img_ptr;
// 	void *xpm_img_ptr;
// 	char *bg_img_data;
// 	int bpp, size_line, endian;
// 	int x, y;

// 	// 背景用の画像を作成（800x600）
// 	bg_img_ptr = mlx_new_image(mlx_ptr, win_width, win_height);
// 	bg_img_data = mlx_get_data_addr(bg_img_ptr, &bpp, &size_line, &endian);

// 	// 背景画像を緑色で塗りつぶす
// 	for (y = 0; y < win_height; y++)
// 	{
// 		for (x = 0; x < win_width; x++)
// 		{
// 			*(int *)(bg_img_data + (y * size_line + x * (bpp / 8))) = BG_COLOR;
// 		}
// 	}

// 	// XPM画像を読み込む
// 	xpm_img_ptr = mlx_xpm_file_to_image(mlx_ptr, xpm_file, &img_width,
			// &img_height);
// 	if (!xpm_img_ptr)
// 	{
// 		ft_printf("Failed to load XPM file: %s\n", xpm_file);
// 		return ;
// 	}

// 	// XPM画像を背景画像に貼り付ける
// 	char *xpm_img_data = mlx_get_data_addr(xpm_img_ptr, &bpp, &size_line,
			// &endian);

// 	// XPM画像の座標を設定（中央に配置）
// 	// int offset_x = (win_width - img_width) / 2;
// 	// int offset_y = (win_height - img_height) / 2;

// 	// XPM画像を背景にコピー
// 	for (y = 0; y < img_height; y++)
// 	{
// 		for (x = 0; x < img_width; x++)
// 		{
// 			unsigned int color = *(int *)(xpm_img_data + (y * size_line + x
						// * (bpp / 8)));
// 			if (color != 0xFF000000)  // 透明色を無視（XPMの透明色が黒ならここで判定）
// 			{
// 				*(int *)(bg_img_data + (y * size_line + x * (bpp / 8))) = color;
// 			}
// 		}
// 	}
// 	// 最後に背景画像をウィンドウに一度だけ表示
// 	mlx_put_image_to_window(mlx_ptr, win_ptr, bg_img_ptr, 0, 0);
// }

// int main(void)
// {
// 	void *mlx_ptr;
// 	void *win_ptr;

// 	// MiniLibX 初期化
// 	mlx_ptr = mlx_init();
// 	if (!mlx_ptr)
// 	{
// 		ft_printf("Failed to initialize MiniLibX\n");
// 		return (1);
// 	}

// 	// ウィンドウの作成（幅800、高さ600）
// 	win_ptr = mlx_new_window(mlx_ptr, 800, 600,
			// "Green Background with XPM Image");

// 	// 背景に緑色を塗りつぶしてXPM画像を貼り付け
// 	render_image_with_xpm(mlx_ptr, win_ptr, "./img/eagle.xpm");

// 	// イベントループ
// 	mlx_loop(mlx_ptr);

// 	return (0);
// }