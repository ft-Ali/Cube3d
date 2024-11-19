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
    ft_printf(GREEN "  North: %s\n" RESET, game->map->north_path);
    ft_printf(GREEN "  South: %s\n" RESET, game->map->south_path);
    ft_printf(GREEN "  West: %s\n" RESET, game->map->west_path);
    ft_printf(GREEN "  East: %s\n" RESET, game->map->east_path);

    // Afficher les couleurs
    ft_printf(BOLD "🎨 Colors:\n" RESET);
    ft_printf(CYAN "  Floor: %s\n" RESET, game->map->f_color);
    ft_printf(CYAN "  Ceiling: %s\n" RESET, game->map->c_color);

    // Afficher la carte
    ft_printf(BOLD "🗺️ Map:\n" RESET);
	if(game->map->grid == NULL)
	    return ;
    while (game->map->grid[i])
    {
        ft_printf(YELLOW "  %s\n" RESET, game->map->grid[i]);
        i++;
    }
    ft_printf(MAGENTA "  Height: %d\n" RESET, game->map->height);
}

int	on_destroy(t_game *game)
{
	free_game(game);
	printf("Exit\n");
	exit(0);
	return (0);
}

int	main(int c, char **v)
{
	t_game game;

	if (c != 2)
	{
		ft_printf(RED BOLD ERR_USAGE RESET "\n");
		return (1);
	}
	init_game(&game);
	parse_init(&game, v[1]);
	print_data(&game);
	init_mlx(&game);
	printf(GREEN "mlx_init\n" RESET);
	init_textures(&game);
	printf(GREEN "init_textures\n" RESET);
	init_vectors(&game);
	printf(GREEN "init_vectors\n" RESET);
	// raycasting(&game);
	// mlx_hook(game.win_ptr, 2, 1L << 0, /*afaire*/, &game);
	// mlx_hook(game.win_ptr, 3, 1L << 1, /*afaire*/, &game);
	// mlx_hook(game.win_ptr, 17, 0, /*afaire*/ , &game);
	mlx_hook(game.win, DestroyNotify, 0, &on_destroy, &game);
	mlx_loop(game.mlx);
	printf(GREEN "FIN DE PROGRAMME\n" RESET);
	// free_game(&game);
	return (0);
}
