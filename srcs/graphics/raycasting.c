/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:36:19 by jules             #+#    #+#             */
/*   Updated: 2024/11/29 13:05:58 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	free_pixel_tab(int **buffer)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (i < WIN_H)
		i++;
	while (++j <= i)
		free(buffer[j]);
	free(buffer);
}

static void	img_addr(t_game *game, int **buffer, int i)
{
	int		j;
	int		index;
	t_img	img;

	init_img(&img);
	img.mlx_img = mlx_new_image(game->mlx, WIN_W, WIN_H);
	img.addr = (int *)mlx_get_data_addr(img.mlx_img, &img.bpp, &img.line_len,
			&img.endian);
	while (++i < WIN_H)
	{
		j = -1;
		while (++j < WIN_W)
		{
			index = i * (img.line_len / 4) + j;
			if (buffer[i][j] > 0)
				img.addr[index] = buffer[i][j];
			else if (i < WIN_H / 2)
				img.addr[index] = game->map->ccolor_i;
			else
				img.addr[index] = game->map->fcolor_i;
		}
	}
	mlx_put_image_to_window(game->mlx, game->win, img.mlx_img, 0, 0);
	mlx_destroy_image(game->mlx, img.mlx_img);
}

static void	ray_loop(t_game *game, t_ray *ray, int **buf)
{
	int	x;

	x = 0;
	while (x < WIN_W)
	{
		ray_pos(ray, x);
		side_dist(ray);
		dda_algo(game, ray);
		start_draw(ray);
		draw_pixels(game, ray, x, buf);
		x++;
	}
	img_addr(game, buf, -1);
	free_pixel_tab(buf);
}

void	raycasting(t_game *game)
{
	int	i_buf;
	int	**buf;

	i_buf = 0;
	buf = ft_calloc(WIN_H + 1, sizeof(int *));
	if (!buf)
		handle_error(game, ERR_MALLOC);
	while (i_buf <= WIN_H)
	{
		buf[i_buf] = ft_calloc(WIN_W + 1, sizeof(int));
		if (!buf[i_buf])
		{
			while (i_buf >= 0)
			{
				free(buf[i_buf]);
				i_buf--;
			}
			free(buf);
			handle_error(game, ERR_MALLOC);
		}
		i_buf++;
	}
	ray_loop(game, game->ray, buf);
}
