/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:56:29 by jules             #+#    #+#             */
/*   Updated: 2024/11/19 15:53:26 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

static void	init_plane(t_ray *ray, char c)
{
	if (c == 'S')
	{
		ray->plane[0] = -0.66;
		ray->plane[1] = 0;
	}
	else if (c == 'N')
	{
		ray->plane[0] = 0.66;
		ray->plane[1] = 0;
	}
	else if (c == 'E')
	{
		ray->plane[0] = 0;
		ray->plane[1] = 0.66;
	}
	else if (c == 'W')
	{
		ray->plane[0] = 0;
		ray->plane[1] = -0.66;
	}
}

static void	init_player(int y, int x, char c, t_ray *ray)
{
	ray->pos[0] = (double)x + 0.5;
	ray->pos[1] = (double)y + 0.5;
	if (c == 'S')
	{
		ray->dir[0] = 0;
		ray->dir[1] = 1;
	}
	else if (c == 'N')
	{
		ray->dir[0] = 0;
		ray->dir[1] = -1;
	}
	else if (c == 'E')
	{
		ray->dir[0] = 1;
		ray->dir[1] = 0;
	}
	else if (c == 'W')
	{
		ray->dir[0] = -1;
		ray->dir[1] = 0;
	}
	init_plane(ray, c);
}

void	init_vectors(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	game->ray = calloc(1, sizeof(t_ray));
	if (!game->ray)
		handle_error(game, ERR_MALLOC);
	while (game->map.grid[++i])
	{
		j = -1;
		while (game->map.grid[i][++j])
		{
			if (game->map.grid[i][j] == 'N' || game->map.grid[i][j] == 'S'
				|| game->map.grid[i][j] == 'E' || game->map.grid[i][j] == 'W')
				init_player(i, j, game->map.grid[i][j], game->ray);
		}
	}
}