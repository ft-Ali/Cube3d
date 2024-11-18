/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:56:29 by jules             #+#    #+#             */
/*   Updated: 2024/11/18 20:01:14 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/cube3d.h"

void    init_vectors(t_game *game)
{
    game->player.pos_x = 0.0;
    game->player.pos_y = 0.0;
    game->player.dir_x = -1.0; // Par défaut, direction vers le nord
    game->player.dir_y = 0.0;
    game->player.plane_x = 0.0;
    game->player.plane_y = 0.66; // Champ de vision pour la caméra

    // Init raycasting
    game->ray.dir_x = 0;
    game->ray.dir_y = 0;
    game->ray.hit = 0;
    game->ray.side = 0;
    game->ray.perp_wall_dist = 0.0;
}