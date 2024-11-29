/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:55:23 by jules             #+#    #+#             */
/*   Updated: 2024/11/29 11:01:49 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	init_map(t_map *map)
{
	map->grid = NULL;
	map->height = 0;
	map->width = 0;
	map->north_path = NULL;
	map->south_path = NULL;
	map->west_path = NULL;
	map->east_path = NULL;
	map->f_color = NULL;
	map->c_color = NULL;
	map->f_tab[0] = -1;
	map->f_tab[1] = -1;
	map->f_tab[2] = -1;
	map->c_tab[0] = -1;
	map->c_tab[1] = -1;
	map->c_tab[2] = -1;
}

void	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		handle_error(game, ERR_MLX_INIT);
	game->win = mlx_new_window(game->mlx, WIN_W, WIN_H, "cub3d");
	if (!game->win)
		handle_error(game, ERR_MLX_WIN);
}

void	init_order(t_order *order)
{
	order->no = false;
	order->so = false;
	order->we = false;
	order->ea = false;
	order->f = false;
	order->c = false;
}

void	init_img(t_img *img)
{
	img->mlx_img = NULL;
	img->addr = NULL;
	img->bpp = 0;
	img->line_len = 0;
	img->endian = 0;
	img->img_width = 0;
	img->img_height = 0;
}

void	init_game(t_game *game, t_ray *ray, t_map *map, t_img *img)
{
	t_order	*order;

	game->mlx = NULL;
	game->win = NULL;
	game->tex = NULL;
	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		handle_error(game, ERR_MALLOC);
	init_map(map);
	game->map = map;
	ray = ft_calloc(1, sizeof(t_ray));
	if (!ray)
		handle_error(game, ERR_MALLOC);
	game->ray = ray;
	img = ft_calloc(1, sizeof(t_img));
	if (!img)
		handle_error(game, ERR_MALLOC);
	init_img(img);
	game->img = img;
	order = ft_calloc(1, sizeof(t_order));
	if (!order)
		handle_error(game, ERR_MALLOC);
	game->order = order;
}
