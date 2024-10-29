/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:17:17 by alsiavos          #+#    #+#             */
/*   Updated: 2024/10/29 11:24:35 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

int	check_and_open_file(t_game *game, char *file)
{
	int	map_fd;

	map_fd = open(file, __O_DIRECTORY);
	if (map_fd != -1)
	{
		close(map_fd);
		handle_error(game, "Error: directory or map does not exist");
	}
	map_fd = open(file, O_RDONLY);
	if (map_fd == -1)
	{
		close(map_fd);
		handle_error(game, "Map does not exist");
	}
	return (map_fd);
}
void	check_file_extension(char *path)
{
	int	len;
	int	i;

	len = ft_strlen(path);
	i = len - 4;
	if (ft_strncmp(&path[i], ".cub", 4) != 0)
	{
		ft_printf(RED BOLD "Error\n" RESET);
		ft_printf(RED "File is not a .cub file\n" RESET);
		exit(0);
	}
}


/**
 * check_map_height - renvoie la hauteur de la carte
 */
int	check_map_height(char **map)
{
	int	k;

	k = 0;
	while (map[k])
		k++;
	return (k);
}

/**
 * parse_map - extrait la carte à partir du fichier
 */
void	parse_map(t_game *game, int map_fd)
{
	char	*line_map;
	char	*line_tmp;
	
	line_tmp = get_next_line(map_fd);
	printf("line_map: %s\n", line_tmp);
	while (line_tmp)
	{
		line_map = ft_strjoin(line_map, line_tmp);
		free(line_tmp);
		line_tmp = get_next_line(map_fd);
	}
	game->map.grid = ft_split(line_map, '\n');
	game->map.height = check_map_height(game->map.grid);
	free(line_tmp);
	free(line_map);
}

void	parse_init(t_game *game, char *path)
{
	int map_fd;
	
	
	check_file_extension(path);
	map_fd = check_and_open_file(game, path);
	parse_map_config(game, map_fd);
	
	// printf("MAP color: %s\n", game->map.f_color);
	parse_color(game, game->map.f_color, 'F');
	parse_color(game, game->map.c_color, 'C');
	// check_map_valid(game, map_fd);
	print_data(game);
	
	close(map_fd);
}