/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:17:17 by alsiavos          #+#    #+#             */
/*   Updated: 2024/11/25 15:49:27 by jules            ###   ########.fr       */
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

int	translate_color(int *rgb)
{
	int	color;

	color = (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
	return (color);
}

void	parse_init(t_game *game, char *path)
{
	int map_fd;

	check_file_extension(path);
	map_fd = check_and_open_file(game, path);
	parse_map_config(game, map_fd);

	// printf("MAP color: %s\n", game->map->f_color);
	parse_color(game, game->map->f_color, 'F');
	parse_color(game, game->map->c_color, 'C');
	game->map->fcolor_i = translate_color(game->map->f_tab);
	game->map->ccolor_i = translate_color(game->map->c_tab);
	check_map_valid(game);
	// check_format(game); a faire pour pas que la map deborder de l'ecran

	close(map_fd);
}