/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/10/21 10:36:40 by alsiavos          #+#    #+#             */
/*   Updated: 2024/10/21 10:36:40 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

// libraries

#include "../.libft/gnl/get_next_line.h"
#include "../.libft/libft.h"
#include "../.libft/printf/ft_printf.h"
#include "../minilibx-linux/mlx.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <fcntl.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

#define RESET "\e[0m"
#define DEBUG 0

#define BOLD "\e[1m"
#define DIM "\e[2m" // moins opacity
#define ITAL "\e[3m"
#define ULINE "\e[4m" // trait en bas du text

#define BLACK "\e[30m"
#define RED "\e[31m"
#define GREEN "\e[32m"
#define MAGENTA "\033[35m"
#define YELLOW "\e[33m"
#define BLUE "\e[34m"
#define PURPLE "\e[35m"
#define CYAN "\e[36m"
#define WHITE "\e[37m"

#define WIN_W 1280
#define WIN_H 720
#define SIZE_IMG 64

#define PLAYEROTATE_SPEED 0.03
#define ROTATE_SPEED 0.04
#define WALL 1
#define FLOOR 0
#define PLAYER_N 'N'
#define PLAYER_S 'S'
#define PLAYER_E 'E'
#define PLAYER_W 'W'
#define NO 0
#define SO 1
#define WE 2
#define EA 3
#define X 0
#define Y 1
#define IMG_SIZE 64

// ERROR MESSAGES
#define ERR_USAGE "usage: ./cub3d <path/to/map.cub>"
#define RGB_SIZE 3
#define ERR_FILE_NOT_CUB "Not a .cub file"
#define ERR_FILE_NOT_XPM "Not an .xpm file"
#define ERR_FILE_IS_DIR "Is a directory"
#define ERR_FLOOR_CEILING "Invalid floor/ceiling RGB color(s)"
#define ERR_COLOR_FLOOR "Invalid floor RGB color"
#define ERR_COLOR_CEILING "Invalid ceiling RGB color"
#define ERR_INVALID_MAP "Map description is either wrong or incomplete"
#define ERR_INV_LETTER "Invalid character in map"
#define ERR_NUM_PLAYER "Map has more than one player"
#define ERR_TEX_RGB_VAL "Invalid RGB value (min: 0, max: 255)"
#define ERR_TEX_MISSING "Missing texture(s)"
#define ERR_TEX_INVALID "Invalid texture(s)"
#define ERR_COLOR_MISSING "Missing color(s)"
#define ERR_MAP_MISSING "Missing map"
#define ERR_EMPTY "Missing data"
#define ERR_MAP_TOO_SMALL "Map is not at least 3 lines high"
#define ERR_MAP_NO_WALLS "Map is not surrounded by walls"
#define ERR_MAP_LAST "Map is not the last element in file"
#define ERR_PLAYER_POS "Invalid player position"
#define ERR_PLAYER_DIR "Map has no player position (expected N, S, E or W)"
#define ERR_MALLOC "Could not allocate memory"
#define ERR_MLX_START "Could not start mlx"
#define ERR_MLX_INIT "Could not initialize mlx"
#define ERR_MLX_WIN "Could not create mlx window"
#define ERR_MLX_IMG "Could not create mlx image"

typedef struct s_map
{
	char **grid;	  // Tableau 2D pour la carte
	int width;		  // Largeur de la carte
	int height;		  // Hauteur de la carte
	int player_x;	  // Position X du joueur
	int player_y;	  // Position Y du joueur
	char *north_path; // Chemin vers la texture du mur nord
	char *south_path; // Chemin vers la texture du mur sud
	char *east_path;  // Chemin vers la texture du mur est
	char *west_path;  // Chemin vers la texture du mur ouest
	char *f_color;	  // Couleur du sol (au format "R,G,B")
	char *c_color;	  // Couleur du plafond (au format "R,G,B")
	int fcolor_i;	  // Couleur du sol (au format int)
	int ccolor_i;	  // Couleur du plafond (au format int)
	int f_tab[RGB_SIZE];
	int c_tab[RGB_SIZE];
} t_map;

typedef struct s_img
{
	void *mlx_img;
	int *addr;
	int bpp;
	int line_len;
	int endian;
	int img_width;
	int img_height;
} t_img;

typedef struct s_ray
{
	double pos[2];
	double dir[2];
	double plane[2];
	double camera[2];
	double raydir[2];
	double sidedist[2];
	double deltadist[2];
	int map[2];
	int step[2];
	int tex[2];
	int move[2];
	int rotate;
	int moved;
	int lineh;
	int drawstart;
	int drawend;
	bool hit;
	int side;
	double perpwalldist;
	int texnum;
	double wallx;
	double texstep;
	double texpos;
	int color;
	int y;
} t_ray;

typedef struct s_game
{
	t_map *map; // Carte et informations associées
	t_img *img; // Image et textures
	t_ray *ray; // Raycasting
	int fd;		// File descriptor du fichier map
	bool f_NO;
	bool f_SO;
	bool f_WE;
	bool f_EA;
	bool f_F;
	bool f_C;
	int **tex;	// Tableau de textures
	void *mlx;	// Pointeur vers l'instance MLX
	void *win;	// Pointeur vers la fenêtre
} t_game;

/************************** PARSING ******************************/

int check_and_open_file(t_game *game, char *file);
void parse_map_config(t_game *game, int map_fd);
void parse_init(t_game *game, char *path);
void parse_color(t_game *game, char *rgb, char who);
void process_line(char *line, t_game *game, char **tmp_map);
void append_map_line(char **tmp_map, char *line);
void parse_color_value(char *line, char **color, const char *identifier);
void parse_texture_path(char *line, char **texture_path,
						const char *identifier);
int check_map_height(char **map);
void check_textures(t_game *game);
void check_enclosure_border(t_game *game);
void check_enclosure_side(t_game *game);
void check_map_valid(t_game *game);
int map_width(t_game *game);
void map_replace(t_game *game);
void init_img(t_img *img);
void init_game(t_game *game);
void init_mlx(t_game *game);
void init_map(t_map *map);

/************************** ERROR HANDLING ******************************/

void handle_error(t_game *game, char *msg);
void free_game(t_game *game);

/*****************************GRAPHICS*********************************/

void init_mlx(t_game *game);
void init_textures(t_game *game);
void init_vectors(t_game *game);
void raycasting(t_game *game);
int handle_key_press(int keycode, t_game *game);
int handle_key_release(int keycode, t_game *game);
int movedisplay(t_game *game);
int on_destroy(t_game *game);

/************************** UTILS ******************************/
void print_data(t_game *game);

#endif