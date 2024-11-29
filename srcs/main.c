/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/11/19 17:05:59 by jules             #+#    #+#             */
/*   Updated: 2024/11/19 17:05:59 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// void print_data(t_game *game)
// {
// 	int i;

// 	i = 0;
// 	ft_printf(BOLD "🖼️ Textures:\n" RESET);
// 	ft_printf(GREEN "  North: %s\n" RESET, game->map->north_path);
// 	ft_printf(GREEN "  South: %s\n" RESET, game->map->south_path);
// 	ft_printf(GREEN "  West: %s\n" RESET, game->map->west_path);
// 	ft_printf(GREEN "  East: %s\n" RESET, game->map->east_path);

// 	ft_printf(BOLD "🎨 Colors:\n" RESET);
// 	ft_printf(CYAN "  Floor: %s\n" RESET, game->map->f_color);
// 	ft_printf(CYAN "  Ceiling: %s\n" RESET, game->map->c_color);

// 	ft_printf(BOLD "🗺️ Map:\n" RESET);
// 	if (game->map->grid == NULL)
// 		return ;
// 	while (game->map->grid[i])
// 	{
// 		ft_printf(YELLOW "  %s\n" RESET, game->map->grid[i]);
// 		i++;
// 	}
// 	ft_printf(MAGENTA "  Height: %d\n" RESET, game->map->height);
// }

int	handle_key_press(int keycode, t_game *game)
{
	if (keycode == XK_Escape)
		on_destroy(game);
	if (keycode == XK_w)
		game->ray->move[Y] = 1;
	if (keycode == XK_s)
		game->ray->move[Y] = -1;
	if (keycode == XK_a)
		game->ray->move[X] = -1;
	if (keycode == XK_d)
		game->ray->move[X] = 1;
	if (keycode == XK_Left)
		game->ray->rotate = -1;
	if (keycode == XK_Right)
		game->ray->rotate = 1;
	return (0);
}

int	handle_key_release(int keycode, t_game *game)
{
	if (keycode == XK_w)
		game->ray->move[Y] = 0;
	if (keycode == XK_s)
		game->ray->move[Y] = 0;
	if (keycode == XK_a)
		game->ray->move[X] = 0;
	if (keycode == XK_d)
		game->ray->move[X] = 0;
	if (keycode == XK_Left)
		game->ray->rotate = 0;
	if (keycode == XK_Right)
		game->ray->rotate = 0;
	return (0);
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
	t_game	game;

	if (c != 2)
	{
		ft_printf(RED BOLD ERR_USAGE RESET "\n");
		return (1);
	}
	init_game(&game, NULL, NULL, NULL);
	init_bools(&game);
	parse_init(&game, v[1]);
	init_mlx(&game);
	init_textures(&game);
	init_vectors(&game);
	raycasting(&game);
	mlx_hook(game.win, KeyPress, KeyPressMask, &handle_key_press, &game);
	mlx_hook(game.win, KeyRelease, KeyReleaseMask, &handle_key_release, &game);
	mlx_hook(game.win, DestroyNotify, 0, &on_destroy, &game);
	mlx_loop_hook(game.mlx, &movedisplay, &game);
	mlx_loop(game.mlx);
	return (0);
}
