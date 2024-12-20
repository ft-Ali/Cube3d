/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:57:31 by alsiavos          #+#    #+#             */
/*   Updated: 2024/11/30 20:14:05 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	free_map(t_game *game, int i)
{
	if (game->map->grid)
	{
		while (i < game->map->height)
		{
			if (game->map->grid[i])
				free(game->map->grid[i]);
			i++;
		}
		free(game->map->grid);
	}
	if (game->map->north_path)
		free(game->map->north_path);
	if (game->map->south_path)
		free(game->map->south_path);
	if (game->map->east_path)
		free(game->map->east_path);
	if (game->map->west_path)
		free(game->map->west_path);
	if (game->map->f_color)
		free(game->map->f_color);
	if (game->map->c_color)
		free(game->map->c_color);
	free(game->map);
}

void	free_tex(t_game *game)
{
	free(game->tex[0]);
	free(game->tex[1]);
	free(game->tex[2]);
	free(game->tex[3]);
	free(game->tex);
}

void	free_game(t_game *game)
{
	if (game->map)
		free_map(game, 0);
	if (game->ray)
		free(game->ray);
	if (game->tex)
		free_tex(game);
	if (game->img)
	{
		if (game->img->mlx_img)
			mlx_destroy_image(game->mlx, game->img->mlx_img);
		free(game->img);
	}
	if (game->order)
		free(game->order);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}

void	handle_error(t_game *game, char *msg)
{
	ft_printf(RED BOLD "❌ Error ❌\n" RESET);
	ft_printf(RED "⚠️  %s ⚠️ \n" RESET, msg);
	if (game)
		if (game->fd)
			close(game->fd);
	free_game(game);
	exit(0);
}
