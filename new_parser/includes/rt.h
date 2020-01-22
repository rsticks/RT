/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 17:06:56 by daron             #+#    #+#             */
/*   Updated: 2020/01/21 16:33:16 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef RT_H
# define RT_H

# include <OpenCL/opencl.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include "ftvector.h"
# include "libft.h"
# include <errno.h>

/*
** ------------------------------Structures-------------------------------------
** -------------------------Structures Fot Cernel-------------------------------
*/

typedef	struct		s_rgb2
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}					t_rgb2;

typedef	struct		s_read
{
	char			**buff; //Буффер для считывания файла
	int				str_c; // количество считанных стрк
}					t_read;

typedef	struct		s_light
{
	t_vector			pos;
	t_vector			dir;
	t_rgb2			rgb;
	int				check[2];
	struct s_light	*next;
}					t_light;

typedef	struct		s_obj
{
	int				type;
	t_vector			pos;
	t_vector			dir;

	t_rgb2			rgb;

	int				reflect;
	double			coef_refl;

	int				spec;

	double			limit; // ограничение объекта

	double			ind_refr;
	double			coef_refr;
	int				text_on;
	char			*texture;
	int				check[10];

	struct s_obj	*next;
}					t_obj;

typedef	struct		s_cam
{
	t_vector			pos;
	t_vector			dir;
	int				check[2];
}					t_cam;

typedef	struct		s_win
{
	char			*windname;
	int				size[2];
	int 			anti_alias;
	int				check[6];
}					t_win;


typedef	struct		s_scene
{
	float	spec; // Уровень блестящести
	int 	reflection_c; //Количество отражений
	int		obj_c; // Количество считанных объектов
	int		lgh_c; // Количество источников света

	int		maxref;
	float	ambient;
	char	check[4];
} t_scene;

typedef struct	s_rt
{
	t_read	read_b;

	t_scene scene;
	t_win window;
	t_cam cam;

	t_obj *obj_head; // голова списка
	t_light *lgh_head; // голова списка
	t_obj *obj_cur; // Текущий объект с которым работаем
	t_light *lgh_cur; // Текущий объект с которым работаем

}		t_rt;

/*
** ------------------------------Functions----------------------------------------
*/

int main();
int				kill_all(char *message);
void check_tag(t_rt *rt, char *line, int str_c);
void create_list(t_rt *rt, char *type);
void scene_parser(t_rt *rt, char *line, int str_c);

char *take_int(char *line, int *put_s, int str_c);
char *take_double(char *line, float *put_s, int str_c);

void kill_error(char *message, int string_number);

#endif