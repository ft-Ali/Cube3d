/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:56:34 by jules             #+#    #+#             */
/*   Updated: 2024/11/12 20:02:51 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

void    init_mlx(t_game *game)
{
    game->mlx = mlx_init();
    if (!game->mlx)
        handle_error(game, ERR_MLX_INIT);
    game->win = mlx_new_window(game->mlx, SCREEN_W, SCREEN_H, "Cub3D");
    if (!game->win)
        handle_error(game, ERR_MLX_WIN);
}

void    init_textures(t_game *game) //fonction qui  initialise les textures dans le game->img
{
    
}