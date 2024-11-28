/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:53:15 by alsiavos          #+#    #+#             */
/*   Updated: 2024/11/28 18:53:58 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	true_order(t_order *order, const char *token)
{
	if (ft_strncmp(token, "NO", 2) == 0)
		order->no = true;
	else if (ft_strncmp(token, "SO", 2) == 0)
		order->so = true;
	else if (ft_strncmp(token, "WE", 2) == 0)
		order->we = true;
	else if (ft_strncmp(token, "EA", 2) == 0)
		order->ea = true;
	else if (ft_strncmp(token, "F", 1) == 0)
		order->f = true;
	else if (ft_strncmp(token, "C", 1) == 0)
		order->c = true;
}

bool	check_order_valid(t_order *order)
{
	// printf("no: %d, so: %d, we: %d, ea: %d, f: %d, c: %d\n", order->no, order->so, order->we, order->ea, order->f, order->c);
	if (order->no == false || order->so == false || order->we == false || order->ea == false || order->f == false || order->c == false)
		return (false);
	return true;
}

void	parse_texture_path(char *line, char **texture_path, const char *identifier, t_game *game)
{
	char	*trimmed_line;

	if (*texture_path)
		free(*texture_path);
	true_order(game->order, identifier);
	trimmed_line = ft_strtrim(&line[ft_strlen(identifier)], " \n");
	*texture_path = ft_strdup(trimmed_line);
	free(trimmed_line);
}

void	parse_color_value(char *line, char **color, const char *identifier, t_game *game)
{
	char	*trimmed_line;

	if (*color)
		free(*color);
	true_order(game->order, identifier);
	trimmed_line = ft_strtrim(&line[ft_strlen(identifier)], " \n");
	*color = ft_strdup(trimmed_line);
	free(trimmed_line);
}

bool	append_map_line(char **tmp_map, char *line, t_game *game)
{
	if (!check_order_valid(game->order))
		return (false);
	*tmp_map = ft_freejoin(*tmp_map, line, ft_strlen(*tmp_map),
			ft_strlen(line));
	return (true);
}

bool	process_line(char *line, t_game *game, char **tmp_map)
{
	if ((ft_strncmp(line, "NO", 2) == 0))
		parse_texture_path(line, &game->map->north_path, "NO", game);
	else if (ft_strncmp(line, "SO", 2) == 0)
		parse_texture_path(line, &game->map->south_path, "SO", game);
	else if (ft_strncmp(line, "WE", 2) == 0)
		parse_texture_path(line, &game->map->west_path, "WE", game);
	else if (ft_strncmp(line, "EA", 2) == 0)
		parse_texture_path(line, &game->map->east_path, "EA", game);
	else if (ft_strncmp(line, "F", 1) == 0)
		parse_color_value(line, &game->map->f_color, "F", game);
	else if (ft_strncmp(line, "C", 1) == 0)
		parse_color_value(line, &game->map->c_color, "C", game);
	else if (ft_isdigit(line[0]) || line[0] == ' ')
		if (!append_map_line(tmp_map, line, game))
			return (false);
	return (true);
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

void	parse_map_config(t_game *game, int map_fd)
{
	char	*line;
	char	*tmp_map;
	tmp_map = ft_strdup("");
	line = get_next_line(map_fd);
	while (line)
	{
		if (!process_line(line, game, &tmp_map))
			(free(line), free(tmp_map), handle_error(game, "Error: Invalid map configuration"));
		check_double(line, game);
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
