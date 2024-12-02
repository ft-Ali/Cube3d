/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:17:17 by alsiavos          #+#    #+#             */
/*   Updated: 2024/12/02 08:32:14 by alsiavos         ###   ########.fr       */
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

int	translate_color(int *rgb)
{
	int	color;

	color = (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
	return (color);
}

void	init_bools(t_game *game)
{
	game->f_no = false;
	game->f_so = false;
	game->f_we = false;
	game->f_ea = false;
	game->f_f = false;
	game->f_c = false;
}

void	parse_init(t_game *game, char *path)
{
	int	map_fd;

	check_file_extension(game, path);
	map_fd = check_and_open_file(game, path);
	parse_map_config(game, map_fd);
	parse_color(game, game->map->f_color, 'F');
	parse_color(game, game->map->c_color, 'C');
	game->map->fcolor_i = translate_color(game->map->f_tab);
	game->map->ccolor_i = translate_color(game->map->c_tab);
	check_map_valid(game);
	close(map_fd);
}
