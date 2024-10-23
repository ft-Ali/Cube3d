/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:17:17 by alsiavos          #+#    #+#             */
/*   Updated: 2024/10/23 13:16:24 by alsiavos         ###   ########.fr       */
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
 * parse_textures - extrait les chemins des textures (NO, SO, WE, EA) du fichier
 */
void	parse_textures(t_game *game, int map_fd)
{
	char	*line;

	while ((line = get_next_line(map_fd)) != NULL)
	{
		if (ft_strncmp(line, "NO", 2) == 0)
			game->map.north_path = ft_strdup(ft_strtrim(&line[2], " \n"));
		else if (ft_strncmp(line, "SO", 2) == 0)
			game->map.south_path = ft_strdup(ft_strtrim(&line[2], " \n"));
		else if (ft_strncmp(line, "WE", 2) == 0)
			game->map.west_path = ft_strdup(ft_strtrim(&line[2], " \n"));
		else if (ft_strncmp(line, "EA", 2) == 0)
			game->map.east_path = ft_strdup(ft_strtrim(&line[2], " \n"));
		// Si on rencontre une ligne de carte, on stoppe la lecture des textures
		else if (ft_isdigit(line[0]) || line[0] == ' ')
		{
			free(line);
			break ;
		}
		free(line);
	}
	// Vérification que toutes les textures ont été trouvées
	if (!game->map.north_path || !game->map.south_path || !game->map.east_path
		|| !game->map.west_path)
		handle_error(game, ERR_TEX_MISSING);
}
int count_split(char **split)
{
	int count;

	count = 0;
	while (split[count])
		count++;
	return (count);
}
/**
 * parse_colors - extrait les couleurs du sol (F) et du plafond (C) du fichier
 */


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

	// char *line;
	line_map = ft_strdup("");
	while ((line_tmp = get_next_line(map_fd)) != NULL)
	{
		// Si la ligne est vide, il y a une erreur de format dans la carte
		if (ft_strlen(line_tmp) == 0 || line_tmp[0] == '\n')
		{
			free(line_tmp);
			continue;
			// free(line_map);
		}
		// Concatène les lignes pour former la carte complète
		line_map = ft_freejoin(line_map, line_tmp, ft_strlen(line_map),
				ft_strlen(line_tmp));
		free(line_tmp);
	}
	// Split la carte en lignes dans le tableau 2D
	game->map.grid = ft_split(line_map, '\n');
	game->map.height = check_map_height(game->map.grid);
	// Nettoyage
	free(line_map);
}
void print_data(t_game *game)
{
    int i = 0;

    // Afficher les textures
    ft_printf(BOLD "🖼️ Textures:\n" RESET);
    ft_printf("  North: %s\n", game->map.north_path);
    ft_printf("  South: %s\n", game->map.south_path);
    ft_printf("  West: %s\n", game->map.west_path);
    ft_printf("  East: %s\n", game->map.east_path);

    // Afficher les couleurs
    ft_printf(BOLD "🎨 Colors:\n" RESET);
    ft_printf("  Floor: %d\n", game->map.f_color);
    ft_printf("  Ceiling: %d\n", game->map.c_color);

    // Afficher la carte
    ft_printf(BOLD "🗺️ Map:\n" RESET);
    while (game->map.grid[i])
    {
        ft_printf("  %s\n", game->map.grid[i]);
        i++;
    }
    ft_printf("  Height: %d\n", game->map.height);
}

void	parse_init(t_game *game, char *path)
{
	int map_fd;

	
	check_file_extension(path);
	map_fd = check_and_open_file(game, path);
	parse_textures(game, map_fd);

	parse_map(game, map_fd);
	print_data(game);
	
	close(map_fd);
}