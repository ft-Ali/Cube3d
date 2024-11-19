CUBE_NAME	=	cub3D

CC			=	cc
FLAG		=	-Wall -Wextra -Werror -g3

LIBFT_PATH	=	.libft
LIBFT_FILE	=	libft.a
LIBFT_LIB	=	$(LIBFT_PATH)/$(LIBFT_FILE)

MLX_PATH	=	.minilibx-linux
MLX_FLAGS   =   -lX11 -lXext -fPIE
MLX_FILE	=	libmlx.a
MLX_LIB		=	$(MLX_PATH)/$(MLX_FILE)
MLX_EX      =   $(MLX_LIB) $(MLX_FLAGS)


CUBE_SRC	=	srcs/main.c srcs/checker/check_map.c srcs/checker/check_texture.c srcs/checker/check_color.c srcs/utils/free_error.c \
				srcs/checker/check_valid.c srcs/graphics/textures.c srcs/graphics/vectors.c srcs/utils/inits.c
 
CUBE_OBJ	=	$(CUBE_SRC:.c=.o)


.c.o:
	@printf "\r\033[K[cub3D] \033[0;32mBuilding : $<\033[0m\n"
	@$(CC) $(FLAG) -c $< -o $@

all:	$(CUBE_NAME)

# bonus:

$(LIBFT_LIB):
	@make -C $(LIBFT_PATH)

$(MLX_LIB):
	@printf "\r\033[K[mlx] \033[0;32mLinking...\033[0m"
	@make -sC $(MLX_PATH)

$(CUBE_NAME): $(LIBFT_LIB) $(MLX_LIB) $(CUBE_OBJ)
	@printf "\r\033[K[cub3D] \033[0;32mLinking...\033[0m"
	@$(CC) $(CUBE_OBJ) $(LIBFT_LIB) $(MLX_EX) -o $(CUBE_NAME) -lm 
	@printf "\r\033[K[cub3D] \033[0;32mDone!\033[0m\n"

clean:
	@make clean -sC $(LIBFT_PATH)
	@make clean -sC $(MLX_PATH)
	@rm -f $(CUBE_OBJ)
	@printf "[cub3D] \033[1;31mCleaned .o!\033[0m\n"

fclean: clean
	@rm -f $(CUBE_NAME)
	@make fclean -C $(LIBFT_PATH)
	@printf "[cub3D] \033[1;31mCleaned all!\033[0m\n"

re: fclean all

.PHONY: all clean fclean re