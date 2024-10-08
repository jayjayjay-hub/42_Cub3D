/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:10:51 by jtakahas          #+#    #+#             */
/*   Updated: 2024/10/08 16:50:03 by kosnakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"

# include "mlx.h"

# include <fcntl.h>

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
// max size for mac window
#  define MAX_WIDTH 2560
#  define MAX_HEIGHT 1400
// max size for mac image (42x42) : 2560 / 42 = 60, 1400 / 42 = 33
#  define MAX_WIDTH_IMAGE 60
#  define MAX_HEIGHT_IMAGE 33
// max size for mac image (42x42) : 60 * 33 = 1980
#  define MAX_IMAGE 1980
// max size for mac read :
	//(MAX_WIDTH_IMAGE + 1) * MAX_HEIGHT_IMAGE = 61 * 33 = 2013
#  define MAX_READ_SIZE 2013
#  define READ_SIZE 2500
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
// max size for linux window
#  define MAX_WIDTH 1920
#  define MAX_HEIGHT 1080
// max size for linux image (42x42) : 1920 / 42 = 45, 1080 / 42 = 25
#  define MAX_WIDTH_IMAGE 45
#  define MAX_HEIGHT_IMAGE 25
// max size for linux image (42x42) : 45 * 25 = 1125
#  define MAX_IMAGE 1125
// max size for linux read :
	// (MAX_WIDTH_IMAGE + 1) * MAX_HEIGHT_IMAGE = 46 * 25 = 1150
#  define MAX_READ_SIZE 1150
#  define READ_SIZE 1500
#  define DESTROYNOTIFY DestroyNotify
#  define STRUCTURENOTIFYMASK StructureNotifyMask
# endif

# define WINWIDTH 1200
# define WINHEIGHT 800
# define PIXELSIZE 40
# define CHARSPEED 50

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	int		up;
	int		down;
	int		left;
	int		right;
	int		x;
	int		y;
	char	**map;
	struct s_img	*img;
}	t_mlx;

typedef struct s_img
{
	struct s_mlx	mlx;
	void	*img;
	char	*relative_path;
	int		img_width;
	int		img_height;
}	t_img;

void	put_wall(t_mlx mlx);

#endif