/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:57:31 by alsiavos          #+#    #+#             */
/*   Updated: 2024/10/23 11:35:00 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

void	free_all(t_game *game)
{
	int	i;

	i = 0;
	// MAP
	if (game->map.grid)
	{
		while (i < game->map.height)
		{
			if (game->map.grid[i])
				free(game->map.grid[i]);
			i++;
		}
		free(game->map.grid);
	}
	// TEXTURES
	if (game->map.north_path)
		free(game->map.north_path);
	if (game->map.south_path)
		free(game->map.south_path);
	if (game->map.east_path)
		free(game->map.east_path);
	if (game->map.west_path)
		free(game->map.west_path);
	// if (game->map.f_color)
	// 	free(game->map.f_color);
	// if (game->map.c_color)
	// 	free(game->map.c_color);
	// MLX
	if (game->img.mlx_img)
		mlx_destroy_image(game->mlx_ptr, game->img.mlx_img);
	if (game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->mlx_ptr)
		mlx_destroy_display(game->mlx_ptr);
	free(game->mlx_ptr);
}

void	handle_error(t_game *game, char *msg)
{
	ft_printf(RED BOLD "❌ Error ❌\n" RESET);
	ft_printf(RED "⚠️  %s ⚠️ \n" RESET, msg);
	free_all(game);
	exit(0);
}