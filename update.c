/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 16:22:41 by lferro            #+#    #+#             */
/*   Updated: 2023/12/10 15:44:46 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Verify if the move is valid and return the next case
 * the move leads to
 *
 * @param game game instance
 * @param x x position
 * @param y y position
 * @return int 0 if move is invalid, 1 if move is valid, 2 if move is a
 * collectible, 3 if move is the exit
 */
int	verify_move(t_game *game, int x, int y)
{
	int	move_validity;

	move_validity = 1;
	if (game->map.map[game->player.x + x][game->player.y + y] == '1')
		move_validity = 0;
	if (game->map.map[game->player.x + x][game->player.y + y] == '0')
		move_validity = 1;
	if (game->map.map[game->player.x + x][game->player.y + y] == 'C')
		move_validity = COLLECTIBLE;
	if (game->map.map[game->player.x + x][game->player.y + y] == 'X')
	{
		ft_printf("You lost, game over!\n");
		terminator(game);
	}
	if (game->map.map[game->player.x + x][game->player.y + y] == 'E')
	{
		if (game->count_coin == 0)
			move_validity = EXIT_END;
		else
			move_validity = 0;
	}
	return (move_validity);
}

/**
 * @brief Update the player position according to the move and update the
 * visual game state accordingly (move counter, collectibles, etc.)
 *
 * @param game game instance
 * @param x x position
 * @param y y position
 */
void	update_player(t_game *game, int x, int y)
{
	int			verifed_move;
	static int	move_nbr;
	char		*move_str;

	verifed_move = verify_move(game, x, y);
	if (verifed_move <= 0)
		return ;
	if (verifed_move == COLLECTIBLE)
	{
		game->count_coin--;
		game->map.map[game->player.x + x][game->player.y + y] = '0';
	}
	else if (verifed_move == EXIT_END)
		exit(0);
	mlx_put_image_to_window(game->mlx, game->win, game->assets.text_bg, 0, 0);
	move_str = ft_itoa(++move_nbr);
	mlx_string_put(game->mlx, game->win, 150, 30, 0xFFFFFF, move_str);
	mlx_string_put(game->mlx, game->win, 35, 30, 0xFFFFFF, "moves:");
	free(move_str);
	game->player.new_x = game->player.x + x;
	game->player.new_y = game->player.y + y;
}

/**
 * @brief Update the visual game state when a valid key is pressed
 *
 * @param keycode
 * @param game
 */
int	update_game(int keycode, t_game *game)
{
	game->player.new_x = game->player.x;
	game->player.new_y = game->player.y;
	if (keycode == KEY_A)
		update_player(game, -1, 0);
	if (keycode == KEY_D)
		update_player(game, 1, 0);
	if (keycode == KEY_W)
		update_player(game, 0, -1);
	if (keycode == KEY_S)
		update_player(game, 0, 1);
	if (keycode == KEY_ESC)
		close_window(keycode, NULL);
	render_player_pos(game, keycode);
	game->player.x = game->player.new_x;
	game->player.y = game->player.new_y;
	if (game->count_coin == 0)
		mlx_put_image_to_window(game->mlx, game->win, game->assets.door,
			TILE_SIZE * get_pos(game->map, 'E')[0], TILE_SIZE
			* get_pos(game->map, 'E')[1]);
	if (verify_move(game, 0, 0) == EXIT_END)
		exit(0);
	return (0);
}

/**
 * @brief Get the player position on the map
 *
 * @param map map to search in
 * @return t_player
 */
t_player	get_player_pos(t_map map)
{
	t_player	player;

	player.x = -1;
	player.y = -1;
	while (++player.x < map.x)
	{
		while (++player.y < map.y)
			if (map.map[player.x][player.y] == 'P')
				return (player);
		player.y = 0;
	}
	player.new_x = player.x;
	player.new_y = player.y;
	return (player);
}
