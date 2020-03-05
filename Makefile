# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kzina <kzina@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/09 16:02:42 by daron             #+#    #+#              #
#    Updated: 2020/03/05 19:44:53 by kzina            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RT
CC = gcc 
FLAGS = -Wall -Wextra -Werror -g
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

HEADERS_LIST =	rt.h
				
HEADERS_DIRECTORY = ./includes/
HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

SOURCES_DIRECTORY = ./source/
SOURCES_LIST = main.c \
                    parser/work_with_list.c \
                    parser/xml_tag.c \
                    parser/scene_parser.c \
                    parser/scene_parser_cheker.c \
                    parser/take_funtion.c \
                    parser/take_funtion_1.c \
                    parser/take_function_2.c \
                    parser/take_function_3.c \
                    parser/camera_parser.c \
                    parser/light_parser.c \
                    parser/object_parser.c \
                    parser/object_parser_1.c \
                    parser/object_parser_cheaker.c \
                    parser/cheker.c \
                    parser/cheaker_1.c \
                    parser/list_to_mas.c \
                    parser/list_to_mas_1.c \
                    parser/parser_main_f.c \
                    transform.c \
                    printf_data.c \
                    error_function.c \
                    cl.c \
                    additional_function.c \
                    additional_function_1.c \
                    events/event.c \
                    events/key_for_cam.c \
                    events/key_for_object.c \
                    events/key_for_other.c \
                    events/mouse.c \
                    intersection/intersection.c \
                    intersection/intersection_1.c \
					load_texture.c \
					parser_obj/parse_obj.c \
                    parser_obj/additional.c \
                    parser_obj/parseings.c \
                    parser_obj/f_pars.c \
					check_objs.c \
                    gui/menu.c \
					gui/menu_2.c \
					gui/auxiliary.c \
					gui/auxiliary_2.c \

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
	@mkdir -p $(OBJECTS_DIRECTORY)/parser
	@mkdir -p $(OBJECTS_DIRECTORY)/events
	@mkdir -p $(OBJECTS_DIRECTORY)/intersection
	@mkdir -p $(OBJECTS_DIRECTORY)/parser_obj
	@mkdir -p $(OBJECTS_DIRECTORY)/gui
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
