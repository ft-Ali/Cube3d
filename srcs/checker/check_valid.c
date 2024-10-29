/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:01:56 by alsiavos          #+#    #+#             */
/*   Updated: 2024/10/29 14:36:35 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

static bool	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

void	check_enclosure(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	printf("game->map.width = %d\n", game->map.width);
	while (j < game->map.width)
	{
		if (game->map.grid[0][j] != '1')
		{
			printf("Erreur à la bordure supérieure: %s\n", game->map.grid[0]);
			handle_error(game, "Bord supérieur non fermé");
		}
		j++;
	}
	size_t t = 0;
	while (t < ft_strlen(game->map.grid[game->map.height - 1]))
	{
		if (game->map.grid[game->map.height - 1][t] != '1')
		{
			 printf("Char a la position [hauteur - 1][%zu]: '%c'\n", t, game->map.grid[game->map.height - 1][t]);
			printf("Erreur a la bordure inferieure: %s\n", game->map.grid[game->map.height - 1]);
			handle_error(game, "Bord inferieur non ferme");
		}
		t++;
	}
	size_t s = 1;
	while (s < ft_strlen(game->map.grid[game->map.height - 1]))
	{
		if (game->map.grid[s][0] != '1')
		{
			printf("Erreur a la bordure gauche a la ligne %zu: %s\n", s, game->map.grid[s]);
			handle_error(game, "Bord gauche non ferme");
		}
		printf("char = %c\n", game->map.grid[i][game->map.width - 1]);
		if (game->map.grid[s][game->map.width - 1] != '1')
		{
			printf("Erreur a la bordure droite a la ligne %zu: %s\n", s,	game->map.grid[s]);
			handle_error(game, "Bord droit non ferme");
		}
		i++;
	}
}

void	map_replace(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (game->map.grid[i])
	{
		j = 0;
		while (game->map.grid[i][j])
		{
			if (is_space(game->map.grid[i][j]))
				game->map.grid[i][j] = '1';
			j++;
		}
		if (game->map.grid[i][j] == '\0')
			game->map.grid[i][j] = '\0';
		i++;
	}
}

// check si la map est entourée de murs
void	check_map_valid(t_game *game)
{
	int i = 0;
	map_replace(game);
	while (game->map.grid[i])
	{
		printf("%s\n", game->map.grid[i]);
		i++;
	}
	check_enclosure(game);
}