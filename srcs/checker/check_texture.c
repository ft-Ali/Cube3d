/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:53:15 by alsiavos          #+#    #+#             */
/*   Updated: 2024/10/28 16:30:31 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

char	*ft_strcat(char *dest, char *src)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	if (dest == NULL)
	{
		dest = src;
		return (dest);
	}
	while (dest[i] != '\0')
		++i;
	j = 0;
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		++j;
	}
	dest[i] = '\0';
	return (dest);
}

void	check_textures(t_game *game)
{
	const char	*ext = ".xpm";
	size_t		ext_len;

	ext_len = ft_strlen(ext);
	if (!game->map.north_path || !game->map.south_path || !game->map.west_path
		|| !game->map.east_path)
		handle_error(game, "Error: Missing textures");
	if (ft_strlen(game->map.north_path) < ext_len
		|| ft_strncmp(game->map.north_path + ft_strlen(game->map.north_path)
			- ext_len, ext, ext_len) != 0)
		handle_error(game, ERR_FILE_NOT_XPM);
	if (ft_strlen(game->map.south_path) < ext_len
		|| ft_strncmp(game->map.south_path + ft_strlen(game->map.south_path)
			- ext_len, ext, ext_len) != 0)
		handle_error(game, ERR_FILE_NOT_XPM);
	if (ft_strlen(game->map.west_path) < ext_len
		|| ft_strncmp(game->map.west_path + ft_strlen(game->map.west_path)
			- ext_len, ext, ext_len) != 0)
		handle_error(game, ERR_FILE_NOT_XPM);
	if (ft_strlen(game->map.east_path) < ext_len
		|| ft_strncmp(game->map.east_path + ft_strlen(game->map.east_path)
			- ext_len, ext, ext_len) != 0)
		handle_error(game, ERR_FILE_NOT_XPM);
}

/**
 * parse_textures - extrait les chemins des textures (NO, SO, WE, EA) du fichier
 */
void	parse_textures(t_game *game, int map_fd)
{
	char	*line;
	char	*trimmed_line;
	char	*tmp_map;
	int		i;

	i = 0;
	tmp_map = NULL;
	line = get_next_line(map_fd);
	while (line)
	{
		if (ft_strncmp(line, "NO", 2) == 0)
		{
			trimmed_line = ft_strtrim(&line[3], " \n");
			game->map.north_path = ft_strdup(trimmed_line);
			free(trimmed_line);
		}
		else if (ft_strncmp(line, "SO", 2) == 0)
		{
			trimmed_line = ft_strtrim(&line[3], " \n");
			game->map.south_path = ft_strdup(trimmed_line);
			free(trimmed_line);
		}
		else if (ft_strncmp(line, "WE", 2) == 0)
		{
			trimmed_line = ft_strtrim(&line[3], " \n");
			game->map.west_path = ft_strdup(trimmed_line);
			free(trimmed_line);
		}
		else if (ft_strncmp(line, "EA", 2) == 0)
		{
			trimmed_line = ft_strtrim(&line[3], " \n");
			game->map.east_path = ft_strdup(trimmed_line);
			free(trimmed_line);
		}
		else if (ft_strncmp(line, "F", 1) == 0)
		{
			trimmed_line = ft_strtrim(&line[2], " \n");
			game->map.f_color = ft_strdup(trimmed_line);
			free(trimmed_line);
		}
		else if (ft_strncmp(line, "C", 1) == 0)
		{
			trimmed_line = ft_strtrim(&line[2], " \n");
			game->map.c_color = ft_strdup(trimmed_line);
			free(trimmed_line);
		}
		else if (ft_isdigit(line[0]) || line[0] == ' ')
		{
			printf("tmp_map 1: %s\n", tmp_map);
			tmp_map = ft_strcat(tmp_map, line);
			printf("tmp_map 2: %s\n", tmp_map);
		}
		free(line);
		// if(trimmed_line)
		// 	free(trimmed_line);
		line = get_next_line(map_fd);
	}
	game->map.grid = ft_split(game->map.grid[0], '\n');
	check_textures(game);
}
