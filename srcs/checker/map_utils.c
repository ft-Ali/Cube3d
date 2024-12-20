/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:07:21 by alsiavos          #+#    #+#             */
/*   Updated: 2024/12/02 08:32:32 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

bool	append_map_line(char **tmp_map, char *line, t_game *game)
{
	if (!check_order_valid(game->order))
		return (false);
	*tmp_map = ft_freejoin(*tmp_map, line, ft_strlen(*tmp_map),
			ft_strlen(line));
	return (true);
}

void	handle_flag(char *line, bool *flag, t_game *game, char *tmp_map)
{
	if (line && *flag)
	{
		free(line);
		free(tmp_map);
		handle_error(game, "Error: Duplicate texture or color");
	}
	*flag = true;
}

void	check_double(char *line, t_game *game, char *tmp_map)
{
	(void)tmp_map;
	if (ft_strncmp(line, "NO", 2) == 0)
		handle_flag(line, &game->f_no, game, tmp_map);
	else if (ft_strncmp(line, "SO", 2) == 0)
		handle_flag(line, &game->f_so, game, tmp_map);
	else if (ft_strncmp(line, "WE", 2) == 0)
		handle_flag(line, &game->f_we, game, tmp_map);
	else if (ft_strncmp(line, "EA", 2) == 0)
		handle_flag(line, &game->f_ea, game, tmp_map);
	else if (ft_strncmp(line, "F", 1) == 0)
		handle_flag(line, &game->f_f, game, tmp_map);
	else if (ft_strncmp(line, "C", 1) == 0)
		handle_flag(line, &game->f_c, game, tmp_map);
}

void	map_replace(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map->grid[i])
	{
		j = 0;
		while (game->map->grid[i][j])
		{
			if (is_space(game->map->grid[i][j]))
				game->map->grid[i][j] = '1';
			j++;
		}
		i++;
	}
}
