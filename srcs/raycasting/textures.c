/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:56:34 by jules             #+#    #+#             */
/*   Updated: 2024/11/18 19:58:20 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

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

void	load_xpm(t_game *game, t_img *img, char *tex)
{
	init_img(img);
	img->mlx_img = mlx_xpm_file_to_image(game->mlx, tex, &img->img_width,
			&img->img_height);
	if (!img->mlx_img)
		handle_error(game, "gros caca");
	printf(GREEN "img->mlx_img\n" RESET);
	img->addr = (int *)mlx_get_data_addr(img->mlx_img, &img->bpp,
			&img->line_len, &img->endian);
}

int	*get_tex(t_game *game, char *tex)
{
	t_img	tmp;
	int		*array;
	int		x;
	int		y;

	load_xpm(game, &tmp, tex);
	printf(GREEN "load_xpm\n" RESET);
	array = ft_calloc(1, sizeof(int) * (IMG_SIZE * IMG_SIZE));
	if (!array)
		handle_error(game, ERR_MALLOC);
	printf(GREEN "array\n" RESET);
	y = -1;
	while (++y < IMG_SIZE)
	{
		x = -1;
		while (++x < IMG_SIZE)
			array[y * IMG_SIZE + x] = tmp.addr[y * IMG_SIZE + x];
	}
	mlx_destroy_image(game->mlx, tmp.mlx_img);
	return (array);
}

void    init_textures(t_game *game) //fonction qui  initialise les textures dans le game->img
{
    game->tex = ft_calloc(5, sizeof(int *));
	if (!game->tex)
		handle_error(game, ERR_MALLOC);
	game->tex[NO] = get_tex(game, game->map.north_path);
	game->tex[SO] = get_tex(game, game->map.south_path);
	game->tex[WE] = get_tex(game, game->map.west_path);
	game->tex[EA] = get_tex(game, game->map.east_path);
}
