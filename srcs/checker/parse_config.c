/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:20:25 by alsiavos          #+#    #+#             */
/*   Updated: 2024/11/30 20:36:39 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	check_map_height(char **map)
{
	int	k;

	k = 0;
	while (map[k])
		k++;
	return (k);
}

int	map_width(t_game *game)
{
	int	i;
	int	max_width;
	int	current_length;

	i = 0;
	max_width = 0;
	while (game->map->grid[i])
	{
		current_length = ft_strlen(game->map->grid[i]);
		if (current_length > max_width)
			max_width = current_length;
		i++;
	}
	game->map->width = max_width;
	return (max_width);
}

bool	process_line(char *line, t_game *game, char **tmp_map)
{
	if ((ft_strncmp(line, "NO", 2) == 0))
		parse_tex(line, &game->map->north_path, "NO", game);
	else if (ft_strncmp(line, "SO", 2) == 0)
		parse_tex(line, &game->map->south_path, "SO", game);
	else if (ft_strncmp(line, "WE", 2) == 0)
		parse_tex(line, &game->map->west_path, "WE", game);
	else if (ft_strncmp(line, "EA", 2) == 0)
		parse_tex(line, &game->map->east_path, "EA", game);
	else if (ft_strncmp(line, "F", 1) == 0)
		parse_rgb(line, &game->map->f_color, "F", game);
	else if (ft_strncmp(line, "C", 1) == 0)
		parse_rgb(line, &game->map->c_color, "C", game);
	else if (ft_isdigit(line[0]) || line[0] == ' ')
		if (!append_map_line(tmp_map, line, game))
			return (false);
	return (true);
}

void	parse_map_config(t_game *game, int map_fd)
{
	char	*line;
	char	*tmp_map;

	tmp_map = ft_strdup("");
	line = get_next_line(map_fd);
	while (line)
	{
		if (!process_line(line, game, &tmp_map))
			(free(line), free(tmp_map), handle_error(game,
					"Error: Invalid map configuration"));
		check_double(line, game, tmp_map);
		free(line);
		line = get_next_line(map_fd);
	}
	game->map->grid = ft_split(tmp_map, '\n');
	free(tmp_map);
	game->map->height = check_map_height(game->map->grid);
	game->map->width = map_width(game);
	check_textures(game);
}
