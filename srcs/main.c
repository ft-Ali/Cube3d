/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/10/21 10:43:39 by alsiavos          #+#    #+#             */
/*   Updated: 2024/10/21 10:43:39 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube3d.h"


void print_data(t_game *game)
{
    int i = 0;

    // Afficher les textures
    ft_printf(BOLD "🖼️ Textures:\n" RESET);
    ft_printf(GREEN "  North: %s\n" RESET, game->map.north_path);
    ft_printf(GREEN "  South: %s\n" RESET, game->map.south_path);
    ft_printf(GREEN "  West: %s\n" RESET, game->map.west_path);
    ft_printf(GREEN "  East: %s\n" RESET, game->map.east_path);

    // Afficher les couleurs
    ft_printf(BOLD "🎨 Colors:\n" RESET);
    ft_printf(CYAN "  Floor: %s\n" RESET, game->map.f_color);
    ft_printf(CYAN "  Ceiling: %s\n" RESET, game->map.c_color);

    // Afficher la carte
    ft_printf(BOLD "🗺️ Map:\n" RESET);
	if(game->map.grid == NULL)
	    return ;
    while (game->map.grid[i])
    {
        ft_printf(YELLOW "  %s\n" RESET, game->map.grid[i]);
        i++;
    }
    ft_printf(MAGENTA "  Height: %d\n" RESET, game->map.height);
}

void	init_struct(t_game *game)
{
	// Utiliser memset pour mettre tous les champs à zéro
	ft_memset(game, 0, sizeof(t_game));

	// Initialiser les pointeurs de la map
	game->map.grid = NULL;
	game->map.north_path = NULL;
	game->map.south_path = NULL;
	game->map.east_path = NULL;
	game->map.west_path = NULL;
	game->map.f_color = NULL;
	game->map.c_color = NULL;

	// Initialiser les images
	game->img.mlx_img = NULL;
	game->img.addr_ptr = NULL;

	// Initialiser les textures dans l'image
	game->img.north_tex.data = NULL;
	game->img.south_tex.data = NULL;
	game->img.east_tex.data = NULL;
	game->img.west_tex.data = NULL;

	// Initialiser les variables du joueur
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

	// Initialiser les pointeurs MLX
	game->mlx_ptr = NULL;
	game->win_ptr = NULL;
}

int	main(int c, char **v)
{
	t_game game;

	if (c != 2)
	{
		ft_printf(RED BOLD ERR_USAGE RESET "\n");
		return (0);
	}
	init_struct(&game);
	parse_init(&game, v[1]);
	handle_error(&game, "free");
}