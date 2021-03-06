#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vchaus <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/26 19:26:29 by vchaus            #+#    #+#              #
#    Updated: 2018/02/12 14:08:08 by vchaus           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = RTv1
CC = gcc
FLAGS = -Wall -Wextra -Werror
SRC = main.c \
	errors.c \
	base_struct.c \
	scene_get_scene.c \
	scene_str_lst_functions.c \
	scene_parse.c \
	scene_count_and_validation.c \
	scene_obj_memory.c \
	scene_parse_elements.c \
	scene_parse_glare_shadow.c \
	scene_parse_camera.c \
	scene_parse_point_other.c \
	scene_parse_color.c \
	scene_parse_light.c \
	scene_parse_object.c \
	scene_parse_sphere.c \
	scene_parse_cylinder_cone.c \
	matrix_transformation_create.c \
	matrix_inverse.c \
	matrix_inverse_part.c \
	matrix_transformation_functions.c \
	graphic_window.c \
	graphic_window_frame.c \
	graphic_draw_line.c \
	graphic_hook_functions.c \
	graphic_hook_rotation.c \
	tracer_throw_rays.c \
	tracer_intersections.c \
	tracer_color.c \
	tracer_light_intensivity.c \
	tracer_normals.c \
	vector_funcs.c \
	vector_funcss.c
OBJ = $(SRC:.c=.o)
HEADER = rtv.h

LIBFT_NAME = libft.a
LIBMLX_NAME = libmlx.a
LIBFT_PATH = ./libft/
LIBFT_H_PATH = includes/
LIBMLX_PATH = ./libmlx/
LIBFT = $(LIBFT_PATH)$(LIBFT_NAME)
LIBMLX = $(LIBMLX_PATH)$(LIBMLX_NAME)

USE_LIBFT = -L $(LIBFT_PATH) -lft
LIBFT_H = -I $(LIBFT_PATH)$(LIBFT_H_PATH)
USE_LIBMLX = -L $(LIBMLX_PATH) -lmlx
LIBMLX_H = -I $(LIBMLX_PATH)
MLX_FRAMEWORKS = -framework OpenGL -framework AppKit
USE_MATH = -lm

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIBFT) $(LIBMLX) $(OBJ)
	$(CC) $(FLAGS) -o $(NAME) $(USE_LIBFT) $(USE_LIBMLX) $(USE_MATH) \
	$(MLX_FRAMEWORKS) $(OBJ)

#$(NAME): $(LIBFT) $(OBJ)
#	$(CC) $(FLAGS) -o $(NAME) $(USE_LIBFT) -L /usr/local/lib/ -lmlx \
	$(MLX_FRAMEWORKS) $(OBJ)

$(LIBFT):
	make -C $(LIBFT_PATH)

$(LIBMLX):
	make -C $(LIBMLX_PATH)

%.o: %.c $(HEADER)
	$(CC) -c $(FLAGS) $(LIBFT_H) $(LIBMLX_H) $<
#	$(CC) -c $(FLAGS) $(LIBFT_H) $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_PATH) fclean
	make -C $(LIBMLX_PATH) clean

re: fclean all

#===============================================================================

norm:
	norminette $(SRC) $(HEADER)
