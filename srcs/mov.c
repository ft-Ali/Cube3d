/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:47:18 by jules             #+#    #+#             */
/*   Updated: 2024/11/25 19:12:58 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/cub3d.h"



int	can_move(t_game *game, t_ray *ray, double x, double y)
{
	if (x < 0.25 || x >= game->map->width - 1.25)
		return (0);
	if (ray->pos[Y] < 0.25 || ray->pos[Y] >= game->map->height - 0.25)
		return (0);
	if (ray->pos[X] < 0.25 || ray->pos[X] >= game->map->width - 1.25)
		return (0);
	if (y < 0.25 || y >= game->map->height - 0.25)
		return (0);
	if (game->map->grid[(int)(y)][(int)(x)] == '1')
		return (0);
	return (1);
}

int	y_move(t_game *game, t_ray *ray, int upordown)
{
	double	x_tmp;
	double	y_tmp;

	x_tmp = 0;
	y_tmp = 0;
	if (upordown == 0)
	{
		x_tmp = ray->pos[X] + ray->dir[X] * (PLAYEROTATE_SPEED * 1.7);
		y_tmp = ray->pos[Y] + ray->dir[Y] * (PLAYEROTATE_SPEED * 1.7);
	}
	else if (upordown == 1)
	{
		x_tmp = ray->pos[X] - ray->dir[X] * (PLAYEROTATE_SPEED * 1.7);
		y_tmp = ray->pos[Y] - ray->dir[Y] * (PLAYEROTATE_SPEED * 1.7);
	}
	if (!can_move(game, ray, x_tmp, y_tmp))
		return (0);
	else
	{
		ray->pos[X] = x_tmp;
		ray->pos[Y] = y_tmp;
	}
	return (1);
}

int	x_move(t_game *game, t_ray *ray, int leftorright)
{
	double	x_tmp;
	double	y_tmp;

	x_tmp = 0;
	y_tmp = 0;
	if (leftorright == 0)
	{
		x_tmp = ray->pos[X] + ray->dir[Y] * PLAYEROTATE_SPEED;
		y_tmp = ray->pos[Y] - ray->dir[X] * PLAYEROTATE_SPEED;
	}
	else if (leftorright == 1)
	{
		x_tmp = ray->pos[X] - ray->dir[Y] * PLAYEROTATE_SPEED;
		y_tmp = ray->pos[Y] + ray->dir[X] * PLAYEROTATE_SPEED;
	}
	if (!can_move(game, ray, x_tmp, y_tmp))
		return (0);
	else
	{
		ray->pos[X] = x_tmp;
		ray->pos[Y] = y_tmp;
	}
	return (1);
}

int	r_rotate(t_ray *ray)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = ray->dir[X];
	old_planex = ray->plane[X];
	ray->dir[X] = ray->dir[X] * cos(ROTATE_SPEED) - ray->dir[Y] * sin(ROTATE_SPEED);
	ray->dir[Y] = old_dirx * sin(ROTATE_SPEED) + ray->dir[Y] * cos(ROTATE_SPEED);
	ray->plane[X] = ray->plane[X] * cos(ROTATE_SPEED) - ray->plane[Y] * sin(ROTATE_SPEED);
	ray->plane[Y] = old_planex * sin(ROTATE_SPEED) + ray->plane[Y] * cos(ROTATE_SPEED);
	return (1);
}

int	l_rotate(t_ray *ray)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = ray->dir[X];
	old_planex = ray->plane[X];
	ray->dir[X] = ray->dir[X] * cos(-ROTATE_SPEED) - ray->dir[Y] * sin(-ROTATE_SPEED);
	ray->dir[Y] = old_dirx * sin(-ROTATE_SPEED) + ray->dir[Y] * cos(-ROTATE_SPEED);
	ray->plane[X] = ray->plane[X] * cos(-ROTATE_SPEED) - ray->plane[Y]
		* sin(-ROTATE_SPEED);
	ray->plane[Y] = old_planex * sin(-ROTATE_SPEED) + ray->plane[Y] * cos(-ROTATE_SPEED);
	return (1);
}

int	moving(t_game *game, t_ray *ray)
{
	int	move;

	move = 0;
	if (ray->move[Y] == 1)
		move += y_move(game, ray, 0);
	if (ray->move[Y] == -1)
		move += y_move(game, ray, 1);
	if (ray->move[X] == -1)
		move += x_move(game, ray, 0);
	if (ray->move[X] == 1)
		move += x_move(game, ray, 1);
	if (ray->rotate < 0)
		move += l_rotate(ray);
	if (ray->rotate > 0)
		move += r_rotate(ray);
	return (move);
}

int movedisplay(t_game *game)
{
    game->ray->moved += moving(game, game->ray);
    if (game->ray->moved == 0)
        return (1);
    raycasting(game);
    return (0);
}
