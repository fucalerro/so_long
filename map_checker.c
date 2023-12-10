/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:27:47 by lferro            #+#    #+#             */
/*   Updated: 2023/12/10 18:19:55 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Check that the map file is a .ber file
/**
 * @brief Check that the map file is a .ber file
 *
 * @param filename map file name
 * @return int true if the map file is a .ber file, false otherwise
 */
int	is_map_berfile(char const *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (false);
	if (filename[len - 4] == '.' && filename[len - 3] == 'b'
		&& filename[len - 2] == 'e' && filename[len - 1] == 'r')
		return (true);
	return (false);
}

// Verfiy that the map is surrounded by walls
int	is_map_walled(t_game *game)
{
	int	x;
	int	y;
	int	iserror;

	x = -1;
	y = -1;
	iserror = true;
	while (++x < game->map.x - 1)
		if (game->map.map[x][0] != '1')
			iserror = false;
	while (++y < game->map.y - 1)
		if (game->map.map[x - 1][y] != '1')
			iserror = false;
	while (--x >= 0)
		if (game->map.map[x][y] != '1')
			iserror = false;
	while (y-- > 0)
		if (game->map.map[0][y] != '1')
			iserror = false;
	return (iserror);
}

/**
 * @brief Check that all lines in the map are of the same length
 *
 * @param fd map file descriptor
 * @return int true if all lines are of the same length, false otherwise
 */
int	is_line_length_consistent(int fd)
{
	char	*mapline;
	int		current_length;
	int		linelength;
	int		i;

	linelength = -1;
	i = 0;
	while (1)
	{
		mapline = get_next_line(fd);
		if (mapline == NULL)
			break ;
		current_length = ft_strlen(mapline);
		if (linelength == -1)
			linelength = current_length;
		else if (current_length != linelength)
		{
			free(mapline);
			return (0);
		}
		free(mapline);
	}
	return (1);
}

/**
 * @brief Check that the map is rectangular
 *
 * @param mapname map file name
 * @return int true if the map is rectangular, false otherwise
 */
int	is_map_rect(char *mapname)
{
	int	fd;
	int	linelength;

	linelength = -1;
	fd = open(mapname, O_RDONLY);
	if (fd == -1)
		return (-1);
	if (!is_line_length_consistent(fd))
	{
		close(fd);
		return (false);
	}
	close(fd);
	return (true);
}

// void	print_map(t_map map)
// {
// 	int	x;
// 	int	y;

// 	x = 0;
// 	y = 0;
// 	while (x < map.y)
// 	{
// 		while (y < map.x)
// 		{
// 			ft_printf("%c", map.map[y][x]);
// 			y++;
// 		}
// 		ft_printf("\n");
// 		y = 0;
// 		x++;
// 	}
// 	ft_printf("\n");
// }

/**
 * @brief Check that the map contains only valid characters
 *
 * @param game game instance
 * @return int true if all cells are valid, false otherwise
 */
int	are_cells_valid(t_game *game)
{
	int	x;
	int	y;

	x = -1;
	y = -1;
	while (++x < game->map.x - 1)
	{
		while (++y < game->map.y - 1)
			if (game->map.map[x][y] != 'C' && game->map.map[x][y] != 'E'
				&& game->map.map[x][y] != 'P' && game->map.map[x][y] != 'X'
				&& game->map.map[x][y] != '1' && game->map.map[x][y] != '0')
				return (false);
		y = 0;
	}
	return (true);
}
