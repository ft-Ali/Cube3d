/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:53:15 by alsiavos          #+#    #+#             */
/*   Updated: 2024/11/28 14:21:42 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	parse_texture_path(char *line, char **texture_path,
		const char *identifier)
{
	char	*trimmed_line;

	if (*texture_path)
		free(*texture_path);
	trimmed_line = ft_strtrim(&line[ft_strlen(identifier)], " \n");
	*texture_path = ft_strdup(trimmed_line);
	free(trimmed_line);
}

void	parse_color_value(char *line, char **color, const char *identifier)
{
	char	*trimmed_line;

	if (*color)
		free(*color);
	trimmed_line = ft_strtrim(&line[ft_strlen(identifier)], " \n");
	*color = ft_strdup(trimmed_line);
	free(trimmed_line);
}

void	append_map_line(char **tmp_map, char *line)
{
	*tmp_map = ft_freejoin(*tmp_map, line, ft_strlen(*tmp_map),
			ft_strlen(line));
}

void	process_line(char *line, t_game *game, char **tmp_map)
{
	if ((ft_strncmp(line, "NO", 2) == 0) && (!game->f_NO))
		(game->f_NO = true, (line, &game->map->north_path, "NO"));
	else if (ft_strncmp(line, "SO", 2) == 0)
		parse_texture_path(line, &game->map->south_path, "SO");
	else if (ft_strncmp(line, "WE", 2) == 0)
		parse_texture_path(line, &game->map->west_path, "WE");
	else if (ft_strncmp(line, "EA", 2) == 0)
		parse_texture_path(line, &game->map->east_path, "EA");
	else if (ft_strncmp(line, "F", 1) == 0)
		parse_color_value(line, &game->map->f_color, "F");
	else if (ft_strncmp(line, "C", 1) == 0)
		parse_color_value(line, &game->map->c_color, "C");
	else if (ft_isdigit(line[0]) || line[0] == ' ')
		append_map_line(tmp_map, line);
}

void	parse_map_config(t_game *game, int map_fd)
{
	char	*line;
	char	*tmp_map;

	tmp_map = ft_strdup("");
	line = get_next_line(map_fd);
	while (line)
	{
		process_line(line, game, &tmp_map);
		free(line);
		line = get_next_line(map_fd);
	}
	game->map->grid = ft_split(tmp_map, '\n');
	free(tmp_map);
	game->map->height = check_map_height(game->map->grid);
	game->map->width = map_width(game);
	// game->map->grid[game->map->height][game->map->width] = '\0';
	check_textures(game);
}

/**
 * parse_textures - extrait les chemins des textures (NO, SO, WE, EA) du fichier
 */
// void	parse_textures(t_game *game, int map_fd)
// {
// 	char	*line;
// 	char	*trimmed_line;
// 	char	*tmp_map;
// 	int		i;

// 	i = 0;
// 	tmp_map = ft_strdup("");
// 	line = get_next_line(map_fd);
// 	while (line)
// 	{
// 		if (ft_strncmp(line, "NO", 2) == 0)
// 		{
// 			trimmed_line = ft_strtrim(&line[3], " \n");
// 			game->map->north_path = ft_strdup(trimmed_line);
// 			free(trimmed_line);
// 		}
// 		else if (ft_strncmp(line, "SO", 2) == 0)
// 		{
// 			trimmed_line = ft_strtrim(&line[3], " \n");
// 			game->map->south_path = ft_strdup(trimmed_line);
// 			free(trimmed_line);
// 		}
// 		else if (ft_strncmp(line, "WE", 2) == 0)
// 		{
// 			trimmed_line = ft_strtrim(&line[3], " \n");
// 			game->map->west_path = ft_strdup(trimmed_line);
// 			free(trimmed_line);
// 		}
// 		else if (ft_strncmp(line, "EA", 2) == 0)
// 		{
// 			trimmed_line = ft_strtrim(&line[3], " \n");
// 			game->map->east_path = ft_strdup(trimmed_line);
// 			free(trimmed_line);
// 		}
// 		else if (ft_strncmp(line, "F", 1) == 0)
// 		{
// 			trimmed_line = ft_strtrim(&line[2], " \n");
// 			game->map->f_color = ft_strdup(trimmed_line);
// 			free(trimmed_line);
// 		}
// 		else if (ft_strncmp(line, "C", 1) == 0)
// 		{
// 			trimmed_line = ft_strtrim(&line[2], " \n");
// 			game->map->c_color = ft_strdup(trimmed_line);
// 			free(trimmed_line);
// 		}
// 		else if (ft_isdigit(line[0]) || line[0] == ' ')
// 		{
// 			tmp_map = ft_freejoin(tmp_map, line, ft_strlen(tmp_map),
// ft_strlen(line));
// 		}
// 		free(line);
// 		line = get_next_line(map_fd);
// 	}

// 	game->map->grid = ft_split(tmp_map, '\n');
// 	game->map->height = check_map_height(game->map->grid);
// 	check_textures(game);
// 	free(tmp_map);
// }
