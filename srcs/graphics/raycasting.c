/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:36:19 by jules             #+#    #+#             */
/*   Updated: 2024/11/25 18:42:48 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/cub3d.h"

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

void	side_dist(t_ray *ray)
{
	if (ray->raydir[X] < 0)
	{
		ray->step[X] = -1;
		ray->sidedist[X] = ((ray->pos[X] - ray->map[X]) * ray->deltadist[X]);
	}
	else
	{
		ray->step[X] = 1;
		ray->sidedist[X] = ((ray->map[X] + 1.0 - ray->pos[X]) * ray->deltadist[X]);
	}
	if (ray->raydir[Y] < 0)
	{
		ray->step[Y] = -1;
		ray->sidedist[Y] = ((ray->pos[Y] - ray->map[Y]) * ray->deltadist[Y]);
	}
	else
	{
		ray->step[Y] = 1;
		ray->sidedist[Y] = ((ray->map[Y] + 1.0 - ray->pos[Y]) * ray->deltadist[Y]);
	}
}
void	dda_algo(t_game *game, t_ray *ray)
{
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->sidedist[X] < ray->sidedist[Y])
		{
			ray->sidedist[X] += ray->deltadist[X];
			ray->map[X] += ray->step[X];
			ray->side = 0;
		}
		else
		{
			ray->sidedist[Y] += ray->deltadist[Y];
			ray->map[Y] += ray->step[Y];
			ray->side = 1;
		}
		if (ray->map[Y] < 0.25 || ray->map[X] < 0.25
			|| ray->map[Y] > game->map->height - 0.25 || ray->map[X] > game->map->width
			- 1.25)
			break ;
		if (game->map->grid[ray->map[Y]][ray->map[X]] == '1')
			ray->hit = 1;
	}
}

void	draw_pixels(t_game *game, t_ray *ray, int x, int **buffer)
{
	if (ray->side == 0)
		ray->wallx = ray->pos[Y] + ray->perpwalldist * ray->raydir[Y];
	else
		ray->wallx = ray->pos[X] + ray->perpwalldist * ray->raydir[X];
	ray->wallx -= floor(ray->wallx);
	ray->tex[X] = (int)(ray->wallx * (double)IMG_SIZE);
	if (ray->side == 0 && ray->raydir[X] > 0)
		ray->tex[X] = IMG_SIZE - ray->tex[X] - 1;
	if (ray->side == 1 && ray->raydir[Y] < 0)
		ray->tex[X] = IMG_SIZE - ray->tex[X] - 1;
	ray->texstep = 1.0 * IMG_SIZE / ray->lineh;
	ray->texpos = (ray->drawstart - WIN_H / 2 + ray->lineh / 2)
		* ray->texstep;
	ray->y = ray->drawstart - 1;
	while (++ray->y < ray->drawend)
	{
		ray->tex[Y] = (int)ray->texpos & (IMG_SIZE - 1);
		ray->texpos += ray->texstep;
		ray->color = game->tex[ray->texnum][IMG_SIZE * ray->tex[Y]
			+ ray->tex[X]];
		buffer[ray->y][x] = ray->color;
	}
}

void	start_draw(t_ray *ray)
{
	if (ray->side == 0)
		ray->perpwalldist = ray->sidedist[X] - ray->deltadist[X];
	else
		ray->perpwalldist = ray->sidedist[Y] - ray->deltadist[Y];
	ray->lineh = (int)(WIN_H / ray->perpwalldist);
	ray->drawstart = -(ray->lineh) / 2 + WIN_H / 2;
	if (ray->drawstart < 0)
		ray->drawstart = 0;
	ray->drawend = ray->lineh / 2 + WIN_H / 2;
	if (ray->drawend >= WIN_H)
		ray->drawend = WIN_H - 1;
	if (ray->side == 0)
	{
		if (ray->raydir[X] < 0)
			ray->texnum = WE;
		else
			ray->texnum = EA;
	}
	else
	{
		if (ray->raydir[Y] > 0)
			ray->texnum = SO;
		else
			ray->texnum = NO;
	}
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

static void ray_loop(t_game *game, t_ray *ray, int **buf)
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

void    raycasting(t_game *game)
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
}
