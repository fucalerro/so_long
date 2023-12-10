OS 				:=	$(shell uname)

NAME			=	so_long
CC				=	cc
AR				=	ar -rc
SRC				=	$(wildcard *.c)
OBJ				=	$(SRC:.c=.o)
LIBFTPATH		=	libft
LIBFT			=	$(LIBFTPATH)/libft.a
CFLAGS			=	-Wall -Werror -Wextra

# Conditional variables based on OS
ifeq ($(OS),Darwin)
	MLXPATH		=	mlx
	MLX			=	$(MLXPATH)/libmlx.a
	# MLXFLAGS	=	-lmlx -framework OpenGL -framework AppKit
	MLXFLAGS	=	-lmlx -framework OpenGL -framework AppKit

else
	MLXPATH		=	mlx_linux
	MLX			=	$(MLXPATH)/libmlx.a
	MLXLINFLAGS	=	-Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
endif

# Generic rule for .o files
%.o: %.c
ifeq ($(OS),Darwin)
					$(CC) $(CFLAGS) -g -c $< -o $@
else
					$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@
endif

all: $(NAME)

$(LIBFT):
					make -C $(LIBFTPATH) all

# Conditional rules for MLX and NAME targets
ifeq ($(OS),Darwin)
$(MLX):
					make -C $(MLXPATH) all
$(NAME): 			$(MLX) $(LIBFT) $(OBJ)
					$(CC) $(SRC) $(LIBFT) -g -Lmlx $(MLXFLAGS) -o $(NAME)
else
$(MLX):
					make -C $(MLXLINPATH) all

$(NAME):			 $(MLX) $(LIBFT) $(OBJ)
					$(CC) $(SRC) $(LIBFT) $(MLXLINFLAGS) -o $(NAME)
endif

clean:
					make -C $(MLXPATH) clean
					make -C $(LIBFTPATH) clean
					rm -f $(OBJ)

fclean: clean
					rm -f $(NAME)
					rm -rf *.dSYM

re: fclean all
