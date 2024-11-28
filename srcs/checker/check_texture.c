/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:53:15 by alsiavos          #+#    #+#             */
/*   Updated: 2024/11/28 16:58:05 by alsiavos         ###   ########.fr       */
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
	if ((ft_strncmp(line, "NO", 2) == 0)/*  && (!game->f_NO) */)
	{
		// game->f_NO = true;
		parse_texture_path(line, &game->map->north_path, "NO");
	}
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
void check_double(char *line, t_game *game)
{
	if (ft_strncmp(line, "NO", 2) == 0)
	{
		if (game->f_NO)
			handle_error(game, "Error: Duplicate NO texture");
		game->f_NO = true;
	}
	else if (ft_strncmp(line, "SO", 2) == 0)
	{
		if (game->f_SO)
			handle_error(game, "Error: Duplicate SO texture");
		game->f_SO = true;
	}
	else if (ft_strncmp(line, "WE", 2) == 0)
	{
		if (game->f_WE)
			handle_error(game, "Error: Duplicate WE texture");
		game->f_WE = true;
	}
	else if (ft_strncmp(line, "EA", 2) == 0)
	{
		if (game->f_EA)
			handle_error(game, "Error: Duplicate EA texture");
		game->f_EA = true;
	}
	else if (ft_strncmp(line, "F", 1) == 0)
	{
		if (game->f_F)
			handle_error(game, "Error: Duplicate F color");
		game->f_F = true;
	}
	else if (ft_strncmp(line, "C", 1) == 0)
	{
		if (game->f_C)
			handle_error(game, "Error: Duplicate C color");
		game->f_C = true;
	}
}

void check_order_valid(char *line, t_game *game)
{
	int i = 0;
	while (line[i]){
	printf("line[i]: %c\n", line[i]);
		i++;
	}
		
	if(line[i - 1] != '1'){
		
		handle_error(game, "Error: Invalid map order");}
}

void	parse_map_config(t_game *game, int map_fd)
{
	char	*line;
	char	*tmp_map;
	int count = 0;
	tmp_map = ft_strdup("");
	line = get_next_line(map_fd);
	printf("line: %s\n", line);
	while (line)
	{
		process_line(line, game, &tmp_map);
		check_double(line, game);
		free(line);
		count++;
		line = get_next_line(map_fd);
	}
	printf("%d\n", count);
	
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
