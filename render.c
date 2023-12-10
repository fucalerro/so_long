/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 10:58:51 by lferro            #+#    #+#             */
/*   Updated: 2023/12/10 18:25:21 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Convert number to binary string
 *
 * @param num number to convert
 * @return char*
 */
char	*to_binary(int num)
{
	char	*bin_str;
	int		i;

	bin_str = malloc(5 * sizeof(char));
	i = 4;
	while (--i >= 0)
		bin_str[3 - i] = ((num >> i) & 1) + '0';
	bin_str[4] = '\0';
	return (bin_str);
}

/**
 * @brief Get the wall mask according to the surrounding walls
 *
 * @param game game instance
 * @param x map x position
 * @param y map y position
 */
void	render_wall(t_game *game, int x, int y)
{
	int		wall;
	char	*str_wall;
	char	*name;
	char	*name1;
	void	*img;

	if (game->map.map[x][y] != '1')
		return ;
	wall = get_wall_mask(game, x, y);
	str_wall = to_binary(wall);
	name = ft_strjoin("img/wall/", str_wall);
	name1 = ft_strjoin(name, ".xpm");
	img = mlx_xpm_file_to_image(game->mlx, name1, &game->ts, &game->ts);
	mlx_put_image_to_window(game->mlx, game->win, game->assets.bg, game->ts * x,
		game->ts * y);
	mlx_put_image_to_window(game->mlx, game->win, img, game->ts * x, game->ts
		* y);
	mlx_destroy_image(game->mlx, img);
	free(name);
	free(name1);
	free(str_wall);
}

/**
 * @brief Render asset map according to the map matrix
 *
 * @param game game instance
 * @param x map x position
 * @param y map y position
 */
void	render_asset(t_game *game, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win, game->assets.bg, game->ts * x,
		game->ts * y);
	if (game->map.map[x][y] == '0')
		mlx_put_image_to_window(game->mlx, game->win, game->assets.bg, game->ts
			* x, game->ts * y);
	else if (game->map.map[x][y] == 'P')
		mlx_put_image_to_window(game->mlx, game->win, game->assets.p_s, game->ts
			* x, game->ts * y);
	else if (game->map.map[x][y] == 'E')
		mlx_put_image_to_window(game->mlx, game->win, game->assets.exit,
			game->ts * x, game->ts * y);
	else if (game->map.map[x][y] == 'C')
		mlx_put_image_to_window(game->mlx, game->win, game->assets.col, game->ts
			* x, game->ts * y);
	else if (game->map.map[x][y] == 'X')
		mlx_put_image_to_window(game->mlx, game->win, game->assets.enemy,
			game->ts * x, game->ts * y);
}

/**
 * @brief Render the map in the window
 *
 * @param mlx mlx instance
 * @param win window instance
 * @param map map to render
 * @param ass game visual assets
 */
void	render_map(t_game *game)
{
	int	x;
	int	y;

	x = -1;
	y = -1;
	while (++x < game->map.x)
	{
		while (++y < game->map.y)
		{
			render_asset(game, x, y);
			render_wall(game, x, y);
		}
		y = -1;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->assets.text_bg, 0, 0);
	mlx_string_put(game->mlx, game->win, 150, 30, 0xFFFFFF, "0");
	mlx_string_put(game->mlx, game->win, 35, 30, 0xFFFFFF, "moves:");
}

/**
 * @brief Render the player asset according the previous move
 *
 * @param g game instance
 * @param keycode keyboard keycode
 */
void	render_player_pos(t_game *g, int keycode)
{
	mlx_put_image_to_window(g->mlx, g->win, g->assets.bg, g->ts
		* g->player.new_x, g->ts * g->player.new_y);
	if (keycode == KEY_W)
		mlx_put_image_to_window(g->mlx, g->win, g->assets.p_w, g->ts
			* g->player.new_x, g->ts * g->player.new_y);
	if (keycode == KEY_A)
		mlx_put_image_to_window(g->mlx, g->win, g->assets.p_a, g->ts
			* g->player.new_x, g->ts * g->player.new_y);
	if (keycode == KEY_S)
		mlx_put_image_to_window(g->mlx, g->win, g->assets.p_s, g->ts
			* g->player.new_x, g->ts * g->player.new_y);
	if (keycode == KEY_D)
		mlx_put_image_to_window(g->mlx, g->win, g->assets.p_d, g->ts
			* g->player.new_x, g->ts * g->player.new_y);
	if (g->player.new_x != g->player.x || g->player.new_y != g->player.y)
	{
		mlx_put_image_to_window(g->mlx, g->win, g->assets.bg, g->ts
			* g->player.x, g->ts * g->player.y);
	}
}
