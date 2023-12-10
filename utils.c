/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 14:33:48 by lferro            #+#    #+#             */
/*   Updated: 2023/12/10 18:21:10 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Count the number of tiles corresponding to the c parameter.
 *
 * @param map
 * @param c
 * @return int
 */
int	count_tiles(t_map map, char c)
{
	int	x;
	int	y;
	int	count;

	x = -1;
	y = -1;
	count = 0;
	while (++x < map.x)
	{
		while (++y < map.y)
		{
			if (map.map[x][y] == c)
				count++;
		}
		y = 0;
	}
	return (count);
}

/**
 * @brief Get the position of the tile corresponding to the tile as parameter.
 *
 * @param map map to search in
 * @param tile tile to find
 * @return int*
 */
int	*get_pos(t_map map, char tile)
{
	int	*pos;

	pos = (int []){-1, -1};
	while (++pos[0] < map.x)
	{
		while (++pos[1] < map.y)
		{
			if (map.map[pos[0]][pos[1]] == tile)
				return (pos);
		}
		pos[1] = 0;
	}
	return (pos);
}

/**
 * @brief exit the program when an exit hook is called
 * (cross on the window or esc key)
 *
 * @param keycode key code
 * @param param game instance
 * @return int
 */
int	close_window(int keycode, void *param)
{
	(void)param;
	(void)keycode;
	exit(0);
}

/**
 * @brief Destroy all images (free) and destroy the window.
 *
 * @param game
 */
void	terminator(t_game *game)
{
	mlx_destroy_image(game->mlx, game->assets.bg);
	mlx_destroy_image(game->mlx, game->assets.col);
	mlx_destroy_image(game->mlx, game->assets.p_w);
	mlx_destroy_image(game->mlx, game->assets.p_a);
	mlx_destroy_image(game->mlx, game->assets.p_s);
	mlx_destroy_image(game->mlx, game->assets.p_d);
	mlx_destroy_image(game->mlx, game->assets.door);
	mlx_destroy_image(game->mlx, game->assets.exit);
	mlx_destroy_image(game->mlx, game->assets.enemy);
	mlx_destroy_image(game->mlx, game->assets.text_bg);
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
}

/**
 * @brief Get the id of the wall to render according to surronding walls
 *
 * @param game game instance
 * @param x map x position
 * @param y map y position
 * @return int wall id to render
 */
int	get_wall_mask(t_game *game, int x, int y)
{
	int	mask;

	mask = (game->map.map[x][y + 1] == '1') * DOWN | (game->map.map[x][y
			- 1] == '1') * UP | (game->map.map[x + 1][y] == '1')
		* RIGHT | (game->map.map[x - 1][y] == '1') * LEFT;
	return (mask);
}
