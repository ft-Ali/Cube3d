/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:17:17 by alsiavos          #+#    #+#             */
/*   Updated: 2024/11/28 16:25:09 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

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
	game->fd = map_fd;
	return (map_fd);
}
void	check_file_extension(t_game *game, char *path)
{
	int	len;
	int	i;

	len = ft_strlen(path);
	i = len - 4;
	if (ft_strncmp(&path[i], ".cub", 4) != 0)
		handle_error(game, "File is not a .cub file");
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

void init_bools(t_game *game)
{
	game->f_NO = false;
	game->f_SO = false;
	game->f_WE = false;
	game->f_EA = false;
	game->f_F = false;
	game->f_C = false;
}
// void check_map_order(t_game *game)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (game->map->grid[i])
// 	{
// 		j = 0;
// 		while (game->map->grid[i][j])
// 		{
// 			if (game->map->grid[i][j] == 'N' || game->map->grid[i][j] == 'S' || game->map->grid[i][j] == 'E' || game->map->grid[i][j] == 'W')
// 			{
// 				if (game->map->grid[i][j] == 'N' || game->map->grid[i][j] == 'S')
// 				{
// 					if (game->map->grid[i][j + 1] != '1' && game->map->grid[i][j + 1] != ' ')
// 						handle_error(game, "Error: Invalid map order");
// 				}
// 				if (game->map->grid[i][j] == 'E' || game->map->grid[i][j] == 'W')
// 				{
// 					if (game->map->grid[i + 1][j] != '1' && game->map->grid[i + 1][j] != ' ')
// 						handle_error(game, "Error: Invalid map order");
// 				}
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }

void	parse_init(t_game *game, char *path)
{
	int map_fd;

	check_file_extension(game, path);
	map_fd = check_and_open_file(game, path);
	parse_map_config(game, map_fd);

	// printf("MAP color: %s\n", game->map->f_color);
	parse_color(game, game->map->f_color, 'F');
	parse_color(game, game->map->c_color, 'C');
	game->map->fcolor_i = translate_color(game->map->f_tab);
	game->map->ccolor_i = translate_color(game->map->c_tab);
	check_map_valid(game);
	// check_map_order(game);
	// check_format(game); a faire pour pas que la map deborder de l'ecran

	close(map_fd);
}