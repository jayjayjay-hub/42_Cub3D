/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:09:37 by jtakahas          #+#    #+#             */
/*   Updated: 2024/09/28 19:14:13 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(void)
{
	void	*mlx;
	void	*win;
	int		x;
	int		y;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 800, 600, "Hello world!");
	y = 0;
	while (y < 600)
	{
		x = 0;
		while (x < 800)
		{
			mlx_pixel_put(mlx, win, x, y, 0x00FF0000);
			x++;
		}
		y++;
	}
	mlx_loop(mlx);
	return (0);
}
