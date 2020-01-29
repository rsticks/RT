# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/09 16:02:42 by daron             #+#    #+#              #
#    Updated: 2020/01/27 16:29:47 by rsticks          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1
CC = gcc
FLAGS = -Wall -Werror -Wextra -O3
LIBRARIES = -L$(LIBFT_DIRECTORY) \
            -L$(FTVECTOR_DIRECTORY) \
			-framework OpenGL \
            -framework AppKit \
			-F./frameworks \
            -rpath ./frameworks \
            -framework OpenCl \
            -framework SDL2 \
            -framework SDL2_ttf \
            -framework SDL2_image \
            -framework SDL2_mixer

INCLUDES = -I./frameworks/SDL2.framework/Versions/A/Headers \
		   -I./frameworks/SDL2_ttf.framework/Versions/A/Headers \
		   -I./frameworks/SDL2_image.framework/Versions/A/Headers \
		   -I./frameworks/SDL2_mixer.framework/Headers \
		   -F./frameworks/ \
		   -I$(HEADERS_DIRECTORY) -I$(LIBFT_HEADERS) -I$(FTVECTOR_HEADERS)

LIBFT = $(LIBFT_DIRECTORY)libft.a
LIBFT_DIRECTORY = ./libft/
LIBFT_HEADERS = $(LIBFT_DIRECTORY)includes/

FTVECTOR = $(FTVECTOR_DIRECTORY)ftvector.a
FTVECTOR_DIRECTORY = ./ftvector/
FTVECTOR_HEADERS = $(FTVECTOR_DIRECTORY)includes/

HEADERS_LIST = rtv1.h
HEADERS_DIRECTORY = ./includes/
HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

SOURCES_DIRECTORY = ./source/
SOURCES_LIST = main.c \
               	scene_parser.c \
               		string_parser.c \
               		light.c \
               		check_object.c \
               		cl.c \
               		transform.c \
               		event.c \
               		key_for_cam.c \
               		key_for_object.c \
               		key_for_other.c \
               		mouse.c \
               		object_parser.c \
               		intersection.c \
               		additional_function.c \
               		additional_function_1.c \
					parse_obj.c \
					
SOURCES = $(addprefix $(SOURCES_DIRECTORY), $(SOURCES_LIST))

OBJECTS_DIRECTORY = objects/
OBJECTS_LIST = $(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS	= $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))

# COLORS

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIBFT) $(FTVECTOR) $(OBJECTS_DIRECTORY) $(OBJECTS)
	@$(CC) $(FLAGS) $(LIBRARIES) $(INCLUDES) $(OBJECTS) $(LIBFT) $(FTVECTOR) -o $(NAME)
	@echo "\n$(NAME): $(GREEN)object files were created$(RESET)"
	@echo "$(NAME): $(GREEN)$(NAME) was created$(RESET)"

$(OBJECTS_DIRECTORY):
	@mkdir -p $(OBJECTS_DIRECTORY)
	@echo "$(NAME): $(GREEN)$(OBJECTS_DIRECTORY) was created$(RESET)"

$(OBJECTS_DIRECTORY)%.o : $(SOURCES_DIRECTORY)%.c $(HEADERS)
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(GREEN).$(RESET)\c"

$(LIBFT):
	@echo "$(NAME): $(GREEN)Creating $(LIBFT)...$(RESET)"
	@$(MAKE) -sC $(LIBFT_DIRECTORY)

$(FTVECTOR):
	@echo "$(NAME): $(GREEN)Creating $(FTVECTOR)...$(RESET)"
	@$(MAKE) -sC $(FTVECTOR_DIRECTORY)

clean:
	@$(MAKE) -sC $(LIBFT_DIRECTORY) clean
	@$(MAKE) -sC $(FTVECTOR_DIRECTORY) clean
	@rm -rf $(OBJECTS_DIRECTORY)
	@echo "$(NAME): $(RED)$(OBJECTS_DIRECTORY) was deleted$(RESET)"
	@echo "$(NAME): $(RED)object files were deleted$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"

re:
	@$(MAKE) fclean
	@$(MAKE) all
