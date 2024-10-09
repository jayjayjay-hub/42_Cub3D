#include "cub3D.h"


int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			index;
	unsigned char	c1;
	unsigned char	c2;

	index = 0;
	while (s1[index] || s2[index])
	{
		c1 = (unsigned char)s1[index];
		c2 = (unsigned char)s2[index];
		if (c1 != c2)
			return (c1 - c2);
		index++;
	}
	return (0);
}

int check_map_spell(char **argv)
{
	if (ft_strrchr(argv[1], '.') == 0
		|| ft_strcmp(ft_strrchr(argv[1], '.'), ".cub") != 0)
		return (1);
	return (0);
}

// void	set_path(t_map *map_info, char *map)
// {
// 	while (*map == 32 || (*map >= 9 && *map <= 13))
// 		map++;
// 	map_info->map = map;
// }

// void	set_map_info(t_map *map_info, char *map)
// {
// 	if (ft_strcmp(map, "NO") == 0)
// 		map_info->no = map;
// 	else if (ft_strcmp(map, "SO") == 0)
// 		map_info->so = map;
// 	else if (ft_strcmp(map, "WE") == 0)
// 		map_info->we = map;
// 	else if (ft_strcmp(map, "EA") == 0)
// 		map_info->ea = map;
// 	else if (ft_strcmp(map, "F") == 0)
// 		map_info->f = map;
// 	else if (ft_strcmp(map, "C") == 0)
// 		map_info->c = map;
// }

// int	map_check(t_map *map_info)
// {
// 	int	column = -1;
// 	char	*map;

// 	if (!map_info->map || !map_info->map[0])
// 		return (1);
// 	while (map_info->map[++column])
// 	{
// 		map = ft_strdup(map_info->map[column]);
// 		set_map_info(map_info, map);
// 	}
// }

int	map_scan(t_map *map_info, char *argv)
{
	int		y;
	int		fd;

	y = 0;
	fd = open(argv, O_RDONLY);
	map_info->map = (char **)malloc(sizeof(char *) * OPEN_MAX);
	while (y < WINWIDTH / PIXELSIZE)
	{
		map_info->map[y] = get_next_line(fd);
		y++;
	}
	// return (map_check(map_info));
	return (0);
}
