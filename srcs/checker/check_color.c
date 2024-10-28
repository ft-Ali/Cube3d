/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:03:09 by alsiavos          #+#    #+#             */
/*   Updated: 2024/10/28 15:04:31 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

static int	check_value(char *str)
{
	int	i;
	int	digit_count;

	i = 0;
	digit_count = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			digit_count++;
		else if (str[i] == '\n')
		{
			i++;
			continue ;
		}
		else
			return (1);
		i++;
	}
	if (ft_atol(str) > 255 || digit_count == 0)
		return (1);
	return (0);
}

void	parse_color(t_game *game, char *rgb, char who)
{
	char	**tab;
	int		i;

	if (!rgb)
		handle_error(game, ERR_COLOR_MISSING);
	tab = ft_split(rgb, ',');
	if (!tab)
		handle_error(game, ERR_MALLOC);
	i = 0;
	while (i < 3)
	{
		if (!tab[i] || check_value(tab[i]) != 0)
		{
			ft_free_split(tab);
			handle_error(game, ERR_TEX_RGB_VAL);
		}
		// printf("tab[%d]: %s\n", i, tab[i]);
		if (who == 'F')
			game->map.f_tab[i] = ft_atoi(tab[i]);
		else if (who == 'C')
			game->map.c_tab[i] = ft_atoi(tab[i]);
		i++;
	}
	ft_free_split(tab);
}