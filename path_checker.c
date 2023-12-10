/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 11:16:06 by lferro            #+#    #+#             */
/*   Updated: 2023/12/10 18:23:55 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	flood_pogging(t_game *game, int x, int y)
{
	if (x < 0 || y < 0 || x >= game->map.x || y >= game->map.y)
		return ;
	if (game->mapcpy.map[x][y] != '0' && game->mapcpy.map[x][y] != 'C')
		return ;
	game->mapcpy.map[x][y] = 'P';
	flood_pogging(game, x + 1, y);
	flood_pogging(game, x - 1, y);
	flood_pogging(game, x, y + 1);
	flood_pogging(game, x, y - 1);
}

int	is_e_beside_p(t_game *game)
{
	int	x;
	int	y;

	x = -1;
	y = -1;
	while (++x < game->map.x)
	{
		while (++y < game->map.y)
			if (game->mapcpy.map[x][y] == 'E')
				if (game->mapcpy.map[x + 1][y] == 'P' || game->mapcpy.map[x
					- 1][y] == 'P' || game->mapcpy.map[x][y + 1] == 'P'
					|| game->mapcpy.map[x][y - 1] == 'P')
					return (true);
		y = 0;
	}
	return (false);
}

// int is_e_beside_p(t_game *game)
// {
// 	int x, y;

// 	x = -1;
// 	y = -1;
// 	while (++x < game->map.x)
// 	{
// 		while (++y < game->map.y)
// 			if (game->mapcpy.map[x][y] == 'E')
// 			{
// 				if (x+1 < game->map.x && game->mapcpy.map[x + 1][y] == 'P')
// 					return (true);
// 				if (x-1 >= 0 && game->mapcpy.map[x - 1][y] == 'P')
// 					return (true);
// 				if (y+1 < game->map.y && game->mapcpy.map[x][y + 1] == 'P')
// 					return (true);
// 				if (y-1 >= 0 && game->mapcpy.map[x][y - 1] == 'P')
// 					return (true);
// 			}
// 		y = 0;
// 	}
// 	return (false);
// }

int	is_path_valid(t_game *game)
{
	int	x;
	int	y;

	x = -1;
	y = -1;
	game->mapcpy.map[game->player.x][game->player.y] = '0';
	flood_pogging(game, game->player.x, game->player.y);
	while (++x < game->map.x)
	{
		while (++y < game->map.y)
			if (game->mapcpy.map[x][y] == 'C')
				return (false);
		y = 0;
	}
	if (is_e_beside_p(game) == false)
		return (false);
	return (true);
}
