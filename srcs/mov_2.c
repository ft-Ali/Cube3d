/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mov_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:01:22 by alsiavos          #+#    #+#             */
/*   Updated: 2024/11/29 13:01:30 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	r_rotate(t_ray *ray)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = ray->dir[X];
	old_planex = ray->plane[X];
	ray->dir[X] = ray->dir[X] * cos(ROTATE_SPEED) - ray->dir[Y]
		* sin(ROTATE_SPEED);
	ray->dir[Y] = old_dirx * sin(ROTATE_SPEED) + ray->dir[Y]
		* cos(ROTATE_SPEED);
	ray->plane[X] = ray->plane[X] * cos(ROTATE_SPEED) - ray->plane[Y]
		* sin(ROTATE_SPEED);
	ray->plane[Y] = old_planex * sin(ROTATE_SPEED) + ray->plane[Y]
		* cos(ROTATE_SPEED);
	return (1);
}

int	l_rotate(t_ray *ray)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = ray->dir[X];
	old_planex = ray->plane[X];
	ray->dir[X] = ray->dir[X] * cos(-ROTATE_SPEED) - ray->dir[Y]
		* sin(-ROTATE_SPEED);
	ray->dir[Y] = old_dirx * sin(-ROTATE_SPEED) + ray->dir[Y]
		* cos(-ROTATE_SPEED);
	ray->plane[X] = ray->plane[X] * cos(-ROTATE_SPEED) - ray->plane[Y]
		* sin(-ROTATE_SPEED);
	ray->plane[Y] = old_planex * sin(-ROTATE_SPEED) + ray->plane[Y]
		* cos(-ROTATE_SPEED);
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
