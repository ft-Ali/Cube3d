/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:36:19 by jules             #+#    #+#             */
/*   Updated: 2024/11/25 15:22:59 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/cube3d.h"

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

void	ray_pos(t_ray *ray, int x)
{
	ray->camera[X] = 2 * x / (double)WIN_W - 1;
	ray->raydir[X] = ray->dir[X] + ray->plane[X] * ray->camera[X];
	ray->raydir[Y] = ray->dir[Y] + ray->plane[Y] * ray->camera[X];
	ray->map[X] = (int)ray->pos[X];
	ray->map[Y] = (int)ray->pos[Y];
	ray->deltadist[X] = fabs(1 / ray->raydir[X]);
	ray->deltadist[Y] = fabs(1 / ray->raydir[Y]);
}

static void ray_loop(t_game *game, t_ray *ray, int **buf)
{
    int	x;

    (void)game;
    (void)buf;
	x = 0;
	while (x < WIN_W)
	{
		ray_pos(ray, x);
		x++;
	}
}

void    init_pixel_tab(t_game *game)
{
    int i_buf;
    int **buf;

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
    free_pixel_tab(buf);
}
