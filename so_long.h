/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:27:14 by lferro            #+#    #+#             */
/*   Updated: 2023/12/10 18:25:29 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
--------------------------- defines ---------------------------
*/

#ifndef SO_LONG_H
# define SO_LONG_H

# ifndef SO_LONG_MACROS

#  define TILE_SIZE		100

#  define WINDOW_CROSS	1

#  define COLLECTIBLE	2
#  define EXIT			3
#  define EXIT_END		4

#  define NB_ARGS		2

#  ifndef MAP_ERRORS
#   define NB_ERRORS	10
#   define ERR_NOMAP	0
#   define ERR_BORDER	1
#   define ERR_PLAYER	2
#   define ERR_COLL		3
#   define ERR_EXIT		4
#   define ERR_RECT		5
#   define ERR_PATH		6
#   define ERR_CELL		7
#   define ERR_NOTEXIST	9
#  endif

// #  define D				printf("%s %d\n",  __FILE__, __LINE__)

#  define UP			0b0001
#  define DOWN			0b0010
#  define RIGHT			0b0100
#  define LEFT			0b1000

#  ifdef __APPLE__
#   define KEY_A		0
#   define KEY_D		2
#   define KEY_W		13
#   define KEY_S		1
#   define KEY_ESC		53
#   define SPEED		750
#  endif

#  ifdef __linux__
#   define KEY_A		97
#   define KEY_D		100
#   define KEY_W		119
#   define KEY_S		115
#   define KEY_ESC		65307
#   define SPEED		7500
#  endif
# endif

/*
--------------------------- includes ---------------------------
*/

# include "libft/libft.h"
# include "mlx/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

/*
--------------------------- typedefs ---------------------------
*/

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	int			w_x;
	int			w_y;
}				t_mlx;

typedef struct s_assets
{
	void		*p_w;
	void		*p_a;
	void		*p_s;
	void		*p_d;
	void		*bg;

	void		*w_0000;
	void		*w_0001;
	void		*w_0010;
	void		*w_0100;
	void		*w_1000;
	void		*w_0011;
	void		*w_0101;
	void		*w_0110;
	void		*w_1001;
	void		*w_1010;
	void		*w_1100;
	void		*w_0111;
	void		*w_1011;
	void		*w_1101;
	void		*w_1110;
	void		*w_1111;

	void		*exit;
	void		*col;
	void		*door;
	void		*enemy;
	void		*text_bg;
}				t_assets;

typedef struct s_player
{
	int			x;
	int			y;
	int			new_x;
	int			new_y;
}				t_player;

typedef struct s_map
{
	char		map[500][500];
	int			x;
	int			y;
}				t_map;

typedef struct s_fread
{
	int			fd;
	int			bread;
	int			linelength;
}				t_fread;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	int			w_x;
	int			w_y;

	t_assets	assets;
	t_map		map;
	t_map		mapcpy;
	t_player	player;
	int			count_coin;
	int			ts;
	int			tstext;
}				t_game;

typedef struct s_anim
{
	char		*frame_index;
	int			x;
	int			y;
	char		*dir_name;
	char		*name;
	char		*f_name;
	void		*img;
}				t_anim;

/*
--------------------------- function prototypes ---------------------------
*/

// void			print_error(int error);
int				close_window(int keycode, void *param);
int				count_tiles(t_map map, char c);
int				is_map_rect(char *mapname);
void			terminator(t_game *game);
int				*get_pos(t_map map, char tile);
// int			is_path_valid(t_map *map, int x, int y, int *map_coll_count);
int				is_path_valid(t_game *game);
int				is_map_berfile(char const *filename);
void			print_error(int error);
int				is_map_walled(t_game *game);
void			render_player_pos(t_game *game, int keycode);
int				update_game(int keycode, t_game *game);
int				verify_move(t_game *game, int x, int y);
// int			verify_move(t_game *game, int new_x, int new_y);
t_player		get_player_pos(t_map map);
void			render_map(t_game *game);
void			set_assets(t_game *game);
t_map			map_parser(char *mapname);
void			set_game_state(t_game *game, char const **argv,
					char **mapfile);
int				is_map_valid(t_game *game, char *mapfile);
int				are_cells_valid(t_game *game);
void			render_wall(t_game *game, int x, int y);
int				get_wall_mask(t_game *game, int x, int y);
int				does_map_exist(char *mapname);
// void			print_map(t_map map);

#endif
