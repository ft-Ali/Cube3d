/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:53:15 by alsiavos          #+#    #+#             */
/*   Updated: 2024/11/29 11:56:24 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	true_order(t_order *order, const char *token)
{
	if (ft_strncmp(token, "NO", 2) == 0)
		order->no = true;
	else if (ft_strncmp(token, "SO", 2) == 0)
		order->so = true;
	else if (ft_strncmp(token, "WE", 2) == 0)
		order->we = true;
	else if (ft_strncmp(token, "EA", 2) == 0)
		order->ea = true;
	else if (ft_strncmp(token, "F", 1) == 0)
		order->f = true;
	else if (ft_strncmp(token, "C", 1) == 0)
		order->c = true;
}

bool	check_order_valid(t_order *order)
{
	if (order->no == false || order->so == false
		|| order->we == false || order->ea == false
		|| order->f == false || order->c == false)
		return (false);
	return (true);
}

void	parse_tex(char *line, char **tex_path, const char *id, t_game *game)
{
	char	*trimmed_line;

	if (*tex_path)
		free(*tex_path);
	true_order(game->order, id);
	trimmed_line = ft_strtrim(&line[ft_strlen(id)], " \n");
	*tex_path = ft_strdup(trimmed_line);
	free(trimmed_line);
}

void	parse_rgb(char *line, char **color, const char *id, t_game *game)
{
	char	*trimmed_line;

	if (*color)
		free(*color);
	true_order(game->order, id);
	trimmed_line = ft_strtrim(&line[ft_strlen(id)], " \n");
	*color = ft_strdup(trimmed_line);
	free(trimmed_line);
}
