#include "cub3D.h"

int check_map_spell(char **argv)
{
	if (ft_strrchr(argv[1], '.') == 0
		|| ft_strncmp(ft_strrchr(argv[1], '.'), ".cub", 4) != 0)
		return (1);
	return (0);
}

int	check_path_spell(char *path)
{
	if (*path == 32 || (*path >= 9 && *path <= 13))
		return (1);
	return (0);
}

void	set_path(char **target, char *map)
{
	while (*map == 32 || (*map >= 9 && *map <= 13))
		map++;
	*target = ft_strdup(map);
}

int	set_color(int *target, char *map)
{
	int	*rgb;
	int	i = -1;

	rgb = (int *)malloc(sizeof(int) * 3);
	while (*map == 32 || (*map >= 9 && *map <= 13))
		map++;
	while (++i < 3)
	{
		rgb[i] = ft_atoi(map);
		while (ft_isdigit(*map))
			map++;
		if (*map == ',' || *map == '\n')
			map++;
		else
			return (1);
	}
	*target = (rgb[0] << 16) + (rgb[1] << 8) + rgb[2];
	return (0);
}

int	set_map_info(t_map *map_info, char *map)
{
	if (ft_strncmp(map, "NO", 2) == 0 && check_path_spell(map += 2))
		set_path(&map_info->no, map);
	else if (ft_strncmp(map, "SO", 2) == 0 && check_path_spell(map += 2))
		set_path(&map_info->so, map);
	else if (ft_strncmp(map, "WE", 2) == 0 && check_path_spell(map += 2))
		set_path(&map_info->we, map);
	else if (ft_strncmp(map, "EA", 2) == 0 && check_path_spell(map += 2))
		set_path(&map_info->ea, map);
	else if (ft_strncmp(map, "F", 1) == 0 && check_path_spell(map += 1))
		return (set_color(&map_info->f, map));
	else if (ft_strncmp(map, "C", 1) == 0 && check_path_spell(map += 1))
		return (set_color(&map_info->c, map));
	return (0);
}

int	map_check(t_map *map_info)
{
	int	column = -1;

	if (!map_info->map || !map_info->map[0])
		return (1);
	while (map_info->map[++column])
	{
		if (set_map_info(map_info, map_info->map[column]))
			return (1);
	}
	if (!map_info->no || !map_info->so || !map_info->we || !map_info->ea
		|| map_info->f == -1 || map_info->c == -1)
		return (1);
	return (0);
}

int	map_info_init(t_map **map_info)
{
	(*map_info)->map = (char **)malloc(sizeof(char *) * 30);
	if (!(*map_info)->map)
		return (1);
	(*map_info)->no = NULL;
	(*map_info)->so = NULL;
	(*map_info)->we = NULL;
	(*map_info)->ea = NULL;
	(*map_info)->f = -1;
	(*map_info)->c = -1;
	return (0);
}

int	map_scan(t_map *map_info, char *argv)
{
	int		y;
	int		fd;

	y = 0;
	fd = open(argv, O_RDONLY);
	if (fd == -1 || map_info_init(&map_info))
		return (1);
	while (1)
	{
		map_info->map[y] = get_next_line(fd);
		if (!map_info->map[y])
			break ;
		y++;
	}
	return (map_check(map_info));
}
