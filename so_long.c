/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:25:06 by lferro            #+#    #+#             */
/*   Updated: 2023/12/10 18:28:19 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Check if the map file exists and is valid
 *
 * @param mapname map file name
 */
int	does_map_exist(char *mapname)
{
	int		fd;
	char	*buff;
	int		bread;

	buff = malloc(sizeof(char) * 2);
	fd = open(mapname, O_RDONLY);
	if (fd < 0)
	{
		free(buff);
		close(fd);
		return (false);
	}
	bread = read(fd, buff, 1);
	if (bread <= 0)
	{
		free(buff);
		close(fd);
		return (false);
	}
	free(buff);
	return (true);
}

/**
 * @brief Parse map .ber file into an int matrix
 *
 * @param mapname
 * @return t_map parsed map as t_map struct
 */
t_map	map_parser(char *mapname)
{
	t_fread	f_read;
	char	*mapline;
	t_map	map;

	f_read.fd = open(mapname, O_RDONLY);
	map.x = 0;
	map.y = 0;
	while (1 || map.y)
	{
		mapline = get_next_line(f_read.fd);
		if (!mapline)
			break ;
		f_read.linelength = ft_strlen(mapline);
		while (mapline[map.x] && mapline[map.x] != '\n')
		{
			map.map[map.x][map.y] = mapline[map.x];
			map.x++;
		}
		map.y++;
		map.x = 0;
		free(mapline);
	}
	map.x = f_read.linelength;
	close(f_read.fd);
	return (map);
}

/**
 * @brief Set the assets object
 *
 * @param g game instance
 */
void	set_assets(t_game *g)
{
	int	s;

	s = g->ts;
	g->assets.p_w = mlx_xpm_file_to_image(g->mlx, "img/sheep_w.xpm", &s, &s);
	g->assets.p_a = mlx_xpm_file_to_image(g->mlx, "img/sheep_a.xpm", &s, &s);
	g->assets.p_s = mlx_xpm_file_to_image(g->mlx, "img/sheep_s.xpm", &s, &s);
	g->assets.p_d = mlx_xpm_file_to_image(g->mlx, "img/sheep_d.xpm", &s, &s);
	g->assets.bg = mlx_xpm_file_to_image(g->mlx, "img/bg.xpm", &s, &s);
	g->assets.col = mlx_xpm_file_to_image(g->mlx, "img/coin0.xpm", &s, &s);
	g->assets.exit = mlx_xpm_file_to_image(g->mlx, "img/bg.xpm", &s, &s);
	g->assets.door = mlx_xpm_file_to_image(g->mlx, "img/door.xpm", &s, &s);
	g->assets.enemy = mlx_xpm_file_to_image(g->mlx, "img/taupe0.xpm", &s, &s);
	g->assets.text_bg = mlx_xpm_file_to_image(g->mlx, "img/text_bg.xpm",
			&(g->tstext), &(g->tstext));
}

// /**
//  * @brief Set the walls object
//  *
//  * @param g game instance
//  */
// void	set_walls(t_game *g)
// {
// 	int	s;

// 	s = g->ts;
// 	g->assets.w_0000 = mlx_xpm_file_to_image(g->mlx, "img/w0000.xpm", &s, &s);
// 	g->assets.w_0001 = mlx_xpm_file_to_image(g->mlx, "img/w0001.xpm", &s, &s);
// 	g->assets.w_0010 = mlx_xpm_file_to_image(g->mlx, "img/w0010.xpm", &s, &s);
// 	g->assets.w_0100 = mlx_xpm_file_to_image(g->mlx, "img/w0100.xpm", &s, &s);
// 	g->assets.w_1000 = mlx_xpm_file_to_image(g->mlx, "img/w1000.xpm", &s, &s);
// 	g->assets.w_0011 = mlx_xpm_file_to_image(g->mlx, "img/w0011.xpm", &s, &s);
// 	g->assets.w_0101 = mlx_xpm_file_to_image(g->mlx, "img/w0101.xpm", &s, &s);
// 	g->assets.w_0110 = mlx_xpm_file_to_image(g->mlx, "img/w0110.xpm", &s, &s);
// 	g->assets.w_1001 = mlx_xpm_file_to_image(g->mlx, "img/w1001.xpm", &s, &s);
// 	g->assets.w_1010 = mlx_xpm_file_to_image(g->mlx, "img/w1010.xpm", &s, &s);
// 	g->assets.w_1100 = mlx_xpm_file_to_image(g->mlx, "img/w1100.xpm", &s, &s);
// 	g->assets.w_0111 = mlx_xpm_file_to_image(g->mlx, "img/w0111.xpm", &s, &s);
// 	g->assets.w_1011 = mlx_xpm_file_to_image(g->mlx, "img/w1011.xpm", &s, &s);
// 	g->assets.w_1101 = mlx_xpm_file_to_image(g->mlx, "img/w1101.xpm", &s, &s);
// 	g->assets.w_1110 = mlx_xpm_file_to_image(g->mlx, "img/w1110.xpm", &s, &s);
// 	g->assets.w_1111 = mlx_xpm_file_to_image(g->mlx, "img/w1111.xpm", &s, &s);
// }

/**
 * @brief Set the game state object
 *
 * @param game game instance
 * @param argv map file name
 * @param mapfile map file path
 * @return int
 */
void	set_game_state(t_game *game, char const **argv, char **mapfile)
{
	int	map_error;

	game->ts = TILE_SIZE;
	if (is_map_berfile(argv[1]) == false)
		exit(0);
	game->mlx = mlx_init();
	set_assets(game);
	*mapfile = ft_strjoin("maps/", argv[1]);
	if (does_map_exist(*mapfile) == false)
	{
		print_error(ERR_NOTEXIST);
		exit(0);
	}
	game->map = map_parser(*mapfile);
	game->mapcpy = map_parser(*mapfile);
	game->player = get_player_pos(game->map);
	game->count_coin = count_tiles(game->map, 'C');
	map_error = is_map_valid(game, *mapfile);
	free(*mapfile);
	if (map_error > 0)
	{
		print_error(map_error);
		exit(0);
	}
}
