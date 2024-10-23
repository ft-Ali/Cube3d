/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
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

#ifndef CUBE3D_H
# define CUBE3D_H

// libraries

# include "../.libft/gnl/get_next_line.h"
# include "../.libft/libft.h"
# include "../.libft/printf/ft_printf.h"
# include "../.minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define RESET "\e[0m"
# define DEBUG 0

# define BOLD "\e[1m"
# define DIM "\e[2m" // moins opacity
# define ITAL "\e[3m"
# define ULINE "\e[4m" // trait en bas du text

# define BLACK "\e[30m"
# define RED "\e[31m"
# define GREEN "\e[32m"
# define YELLOW "\e[33m"
# define BLUE "\e[34m"
# define PURPLE "\e[35m"
# define CYAN "\e[36m"
# define WHITE "\e[37m"

// ERROR MESSAGES
# define ERR_USAGE "usage: ./cub3d <path/to/map.cub>"

# define ERR_FILE_NOT_CUB "Not a .cub file"
# define ERR_FILE_NOT_XPM "Not an .xpm file"
# define ERR_FILE_IS_DIR "Is a directory"
# define ERR_FLOOR_CEILING "Invalid floor/ceiling RGB color(s)"
# define ERR_COLOR_FLOOR "Invalid floor RGB color"
# define ERR_COLOR_CEILING "Invalid ceiling RGB color"
# define ERR_INVALID_MAP "Map description is either wrong or incomplete"
# define ERR_INV_LETTER "Invalid character in map"
# define ERR_NUM_PLAYER "Map has more than one player"
# define ERR_TEX_RGB_VAL "Invalid RGB value (min: 0, max: 255)"
# define ERR_TEX_MISSING "Missing texture(s)"
# define ERR_TEX_INVALID "Invalid texture(s)"
# define ERR_COLOR_MISSING "Missing color(s)"
# define ERR_MAP_MISSING "Missing map"
# define ERR_MAP_TOO_SMALL "Map is not at least 3 lines high"
# define ERR_MAP_NO_WALLS "Map is not surrounded by walls"
# define ERR_MAP_LAST "Map is not the last element in file"
# define ERR_PLAYER_POS "Invalid player position"
# define ERR_PLAYER_DIR "Map has no player position (expected N, S, E or W)"
# define ERR_MALLOC "Could not allocate memory"
# define ERR_MLX_START "Could not start mlx"
# define ERR_MLX_WIN "Could not create mlx window"
# define ERR_MLX_IMG "Could not create mlx image"

typedef struct s_map
{
	char **grid;      // Tableau 2D pour la carte
	int width;        // Largeur de la carte
	int height;       // Hauteur de la carte
	int start_line;   // Première ligne du fichier qui commence la carte
	char *north_path; // Chemin vers la texture du mur nord
	char *south_path; // Chemin vers la texture du mur sud
	char *east_path;  // Chemin vers la texture du mur est
	char *west_path;  // Chemin vers la texture du mur ouest
	char *f_color;    // Couleur du sol (au format "R,G,B")
	char  *c_color;    // Couleur du plafond (au format "R,G,B")
} t_map;

typedef struct s_texture
{
	int width;  // Largeur de la texture
	int height; // Hauteur de la texture
	int *data;  // Tableau de pixels de la texture
} t_texture;

typedef struct s_img
{
	void *mlx_img;       // Pointeur vers l'image dans MLX
	int *addr_ptr;       // Pointeur vers les données de l'image
	int pixel_bits;      // Bits par pixel
	int line_len;        // Longueur d'une ligne en octets
	int endian;          // Endianess (ordre des octets)
	t_texture north_tex; // Texture pour le mur nord
	t_texture south_tex; // Texture pour le mur sud
	t_texture east_tex;  // Texture pour le mur est
	t_texture west_tex;  // Texture pour le mur ouest
} t_img;

typedef struct s_player
{
	double pos_x;   // Position X du joueur
	double pos_y;   // Position Y du joueur
	double dir_x;   // Direction X du joueur
	double dir_y;   // Direction Y du joueur
	double plane_x; // Composante X du plan de la caméra
	double plane_y; // Composante Y du plan de la caméra
} t_player;

typedef struct s_ray
{
	double dir_x; // Direction X du rayon
	double dir_y; // Direction Y du rayon
	double side_dist_x; // Distance à parcourir pour franchir la première ligne verticale
	double side_dist_y; // Distance à parcourir pour franchir la première ligne horizontale
	double delta_dist_x; // Distance à parcourir entre chaque ligne verticale
	double delta_dist_y; // Distance à parcourir entre chaque ligne horizontale
	int step_x; // Direction de progression du rayon en X
	int step_y; // Direction de progression du rayon en Y
	int hit;    // Indicateur de collision avec un mur
	int side; // Indique si le mur touché est vertical ou horizontal
	double perp_wall_dist; // Distance projetée au mur
	int tex_num;           // Numéro de la texture (selon le mur touché)
	double wall_x;         // Position exacte du point d'impact sur le mur
	int tex_x;             // Coordonnée X dans la texture
	double tex_step;       // Pas pour le balayage de la texture
	double tex_pos;        // Position actuelle dans la texture
} t_ray;

typedef struct s_game
{
	t_map map;       // Carte et informations associées
	t_img img;       // Image et textures
	t_player player; // Joueur et sa position
	t_ray ray;       // Raycasting
	void *mlx_ptr;   // Pointeur vers l'instance MLX
	void *win_ptr;   // Pointeur vers la fenêtre
} t_game;

/************************** PARSING ******************************/

void check_file_extension(char *path);
int	check_and_open_file(t_game *game, char *file);
void parse_init(t_game *game, char *path);

/************************** ERROR HANDLING ******************************/


void handle_error(t_game *game, char *msg);


#endif