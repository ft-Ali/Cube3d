/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:17:17 by alsiavos          #+#    #+#             */
/*   Updated: 2024/10/22 15:14:27 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

int	check_and_open_file(t_game *game, char *file)
{
	int	map_fd;

	map_fd = open(file, O_DIRECTORY);
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
void check_file_extension(char *path)
{
	int len;
	int i;

	len = ft_strlen(path);
	i = len - 4;
	if (ft_strncmp(&path[i], ".cub", 4) != 0)
	{
		ft_printf(RED BOLD "Error\n" RESET);
		ft_printf(RED "File is not a .cub file\n" RESET);
		exit(0);
	}
}


void parse_init(t_game *game, char *path)
{
	int fd;
	char *line;

	
	check_file_extension(path);
	fd = check_and_open_file(game, path);
	game->map.start_line = 0;
	line = get_next_line(fd);
	while (line)
	{
		parse_textures_color(game, line); // parse textures and colors a modifier car il faut check les colors rgb et les textures
		parse_map(game, line); // parse map qui va check la map et la stocker dans la structure si elle est valide
		free(line);
		line = get_next_line(fd);
	}
}
	