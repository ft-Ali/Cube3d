/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_valid2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:52:27 by alsiavos          #+#    #+#             */
/*   Updated: 2024/11/29 11:53:21 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

bool	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

int	isstartorground(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	ft_sstrlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

void	check_char(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map->grid[i])
	{
		j = 0;
		while (game->map->grid[i][j])
		{
			if (game->map->grid[i][j] != '1' && game->map->grid[i][j] != '0'
				&& game->map->grid[i][j] != ' ' && game->map->grid[i][j] != 'N'
				&& game->map->grid[i][j] != 'S' && game->map->grid[i][j] != 'E'
				&& game->map->grid[i][j] != 'W')
			{
				printf("Error: %c\n", game->map->grid[i][j]);
				handle_error(game, ERR_INV_LETTER);
			}
			j++;
		}
		i++;
	}
}
