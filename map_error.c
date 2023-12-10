/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 14:32:18 by lferro            #+#    #+#             */
/*   Updated: 2023/12/10 18:25:25 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Print the error message corresponding to the error code.
 *
 * @param error error code
 */
void	print_error(int error)
{
	char	*msgs[NB_ERRORS + 1];

	msgs[ERR_NOMAP] = "Error\nExactly 1 map must be provided.\n";
	msgs[ERR_PATH] = "Error\nMap path is not valid\n";
	msgs[ERR_BORDER] = "Error\nMap must be surronded by walls\n";
	msgs[ERR_RECT] = "Error\nMap must be rectangular.\n";
	msgs[ERR_COLL] = "Error\nMap must have at least 1 collectible.\n";
	msgs[ERR_EXIT] = "Error\nMap must have exactly 1 exit.\n";
	msgs[ERR_PLAYER] = "Error\nMap must have exactly 1 spawn.\n";
	msgs[ERR_CELL] = "Error\nMap contains invalid characters.\n";
	msgs[ERR_NOTEXIST] = "Error\nMap file does not exist.\n";
	ft_printf("%s", msgs[error]);
}

/**
 * @brief If something in the map is not valid, return error
 *
 * @param game game struct
 * @param mapfile mapfile path
 * @return int
 */
int	is_map_valid(t_game *game, char *mapfile)
{
	int	is_error;

	is_error = false;
	if (are_cells_valid(game) == false)
		is_error = ERR_CELL;
	if (is_path_valid(game) == false)
		is_error = ERR_PATH;
	if (is_map_walled(game) == false)
		is_error = ERR_BORDER;
	if (is_map_rect(mapfile) == false)
		is_error = ERR_RECT;
	else if (count_tiles(game->map, 'C') < 1)
		is_error = ERR_COLL;
	else if (count_tiles(game->map, 'E') != 1)
		is_error = ERR_EXIT;
	else if (count_tiles(game->map, 'P') != 1)
		is_error = ERR_PLAYER;
	return (is_error);
}
