/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:03:09 by alsiavos          #+#    #+#             */
/*   Updated: 2024/10/25 12:05:52 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

void check_color(t_game *game, char *file)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	while (file[i])
	{
		if (file[i] == ',')
			j++;
		i++;
	}
	if (j != 2)
		handle_error(game, ERR_FLOOR_CEILING);
	i = 0;
	while (file[i])
	{
		if (ft_isdigit(file[i]) || file[i] == ',')
			i++;
		else
			handle_error(game, ERR_COLOR_FLOOR);
	}
}