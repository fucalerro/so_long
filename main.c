/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 18:19:53 by lferro            #+#    #+#             */
/*   Updated: 2023/12/10 18:26:31 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief animate element according to element param
 *
 * @param game game instance
 * @param anim animation instance
 * @param i animation frame index
 * @param elem element to animate
 */
void	anim_elem(t_game *game, t_anim anim, int i, char *elem)
{
	anim.frame_index = ft_itoa(i);
	anim.dir_name = ft_strjoin("img/", elem);
	anim.name = ft_strjoin(anim.dir_name, anim.frame_index);
	anim.f_name = ft_strjoin(anim.name, ".xpm");
	anim.img = mlx_xpm_file_to_image(game->mlx, anim.f_name, &game->ts,
			&game->ts);
	mlx_put_image_to_window(game->mlx, game->win, game->assets.bg, game->ts
		* anim.x, game->ts * anim.y);
	mlx_put_image_to_window(game->mlx, game->win, anim.img, game->ts * anim.x,
		game->ts * anim.y);
	mlx_destroy_image(game->mlx, anim.img);
	free(anim.dir_name);
	free(anim.name);
	free(anim.f_name);
	free(anim.frame_index);
}

/**
 * @brief animate all elements of the map
 *
 * @param game game instance
 * @return int
 */
int	animations(t_game *game)
{
	static int	framerate;
	static int	i;
	t_anim		anim;

	if (framerate++ % SPEED == 0)
	{
		anim.x = -1;
		anim.y = -1;
		while (++anim.x < game->map.x)
		{
			while (++anim.y < game->map.y)
			{
				if (game->map.map[anim.x][anim.y] == 'C')
					anim_elem(game, anim, i, "coin");
				if (game->map.map[anim.x][anim.y] == 'X')
					anim_elem(game, anim, i, "taupe");
			}
			anim.y = 0;
		}
		i++;
		if (i == 5)
			i = 0;
	}
	return (0);
}

int	main(int argc, char const *argv[])
{
	char	*mapfile;
	int		window_cross;
	t_game	game;

	if (argc != 2)
	{
		print_error(ERR_NOMAP);
		exit(0);
	}
	set_game_state(&game, argv, &mapfile);
	window_cross = WINDOW_CROSS;
	game.w_x = game.ts * (game.map.x - 1);
	game.w_y = game.ts * game.map.y;
	game.win = mlx_new_window(game.mlx, game.w_x, game.w_y, "window");
	render_map(&game);
	mlx_hook(game.win, 2, 1L << 0, update_game, &game);
	mlx_hook(game.win, 17, 0, close_window, &window_cross);
	mlx_loop_hook(game.mlx, animations, &game);
	mlx_loop(game.mlx);
	terminator(&game);
	return (0);
}
