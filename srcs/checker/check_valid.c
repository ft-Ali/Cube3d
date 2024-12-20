/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:01:56 by alsiavos          #+#    #+#             */
/*   Updated: 2024/11/29 13:09:15 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	map_height_valid(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (game->map->grid[i])
	{
		j = 0;
		while (game->map->grid[i][j])
		{
			j++;
		}
		if (j > game->map->width)
			game->map->width = j;
		i++;
	}
	game->map->height = i;
	if (game->map->height < 3 || game->map->width < 3)
		handle_error(game, ERR_MAP_TOO_SMALL);
}

void	check_one_player(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map->grid[i])
	{
		j = 0;
		while (game->map->grid[i][j])
		{
			if (game->map->grid[i][j] == 'N' || game->map->grid[i][j] == 'S'
				|| game->map->grid[i][j] == 'E' || game->map->grid[i][j] == 'W')
			{
				if (game->map->player_x != 0 || game->map->player_y != 0)
					handle_error(game, ERR_NUM_PLAYER);
				game->map->player_x = i;
				game->map->player_y = j;
			}
			j++;
		}
		i++;
	}
	if (game->map->player_x == 0 || game->map->player_y == 0)
		handle_error(game, ERR_PLAYER_DIR);
}

void	check_enclosure_border(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map->grid[i])
	{
		j = 0;
		while (game->map->grid[i][j])
		{
			if (i == 0 || i == game->map->height - 1 || j == 0
				|| j == game->map->width - 1)
			{
				if (game->map->grid[i][j] != '1'
					&& game->map->grid[i][j] != ' ')
					handle_error(game, ERR_MAP_NO_WALLS);
			}
			j++;
		}
		i++;
	}
}

void	check_enclosure_side(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (game->map->grid[++i])
	{
		j = 0;
		while (game->map->grid[i][j])
		{
			if (isstartorground(game->map->grid[i][j]))
			{
				if (i == 0 || j == 0 || game->map->grid[i + 1] == NULL || j
					+ 1 >= ft_sstrlen(game->map->grid[i]))
				{
					handle_error(game, ERR_MAP_NO_WALLS);
				}
				if (game->map->grid[i - 1][j] == ' ' ||
					game->map->grid[i + 1][j] == ' ' ||
					game->map->grid[i][j - 1] == ' ' ||
					game->map->grid[i][j + 1] == ' ')
					map_replace(game);
			}
			j++;
		}
	}
}

void	check_map_valid(t_game *game)
{
	check_char(game);
	check_one_player(game);
	map_height_valid(game);
	check_enclosure_border(game);
	check_enclosure_side(game);
}
