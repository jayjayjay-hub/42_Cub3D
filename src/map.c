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

char	*set_path(char *map)
{
	while (*map == 32 || (*map >= 9 && *map <= 13))
		map++;
	return (map);
}

void	set_map_info(t_map *map_info, char *map)
{
	// ft_printf("map: %s\n", map);
	if (ft_strncmp(map, "NO", 2) == 0)
	{
		ft_printf("1\n");
		map_info->no = set_path(map += 2);
		ft_printf("%s\n", map_info->no);
	}
	else if (ft_strncmp(map, "SO", 2) == 0)
	{
		ft_printf("2\n");
		map_info->so = set_path(map += 2);
	}
	else if (ft_strncmp(map, "WE", 2) == 0)
	{
		ft_printf("3\n");
		map_info->we = set_path(map += 2);
	}
	else if (ft_strncmp(map, "EA", 2) == 0)
	{
		ft_printf("4\n");
		map_info->ea = set_path(map += 2);
	}
	// else if (ft_strncmp(map, "F", 2) == 0)
	// 	set_color(map_info->f, map);
	// else if (ft_strncmp(map, "C", 2) == 0)
	// 	set_color(map_info->c, map);
}

int	map_check(t_map *map_info)
{
	int	column = -1;
	char	*map;

	if (!map_info->map || !map_info->map[0])
		return (1);
	while (map_info->map[++column])
	{
		map = ft_strdup(map_info->map[column]);
		set_map_info(map_info, map);
		free(map);
	}
	// ft_printf("mapinfo->no: %s\n", map_info->no);
	if (!map_info->no || !map_info->so || !map_info->we || !map_info->ea
		|| !map_info->s || !map_info->f || !map_info->c)
		return (1);
	return (0);
}

int	map_scan(t_map *map_info, char *argv)
{
	int		y;
	int		fd;

	y = 0;
	fd = open(argv, O_RDONLY);
	map_info->map = (char **)malloc(sizeof(char *) * OPEN_MAX);
	while (1)
	{
		map_info->map[y] = get_next_line(fd);
		if (!map_info->map[y])
			break ;
		y++;
	}
	return (map_check(map_info));
}
