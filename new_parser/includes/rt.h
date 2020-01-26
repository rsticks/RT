/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 17:06:56 by daron             #+#    #+#             */
/*   Updated: 2020/01/25 14:48:48 by daron            ###   ########.fr       */
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

# define SPHERE_ID		1
# define PLANE_ID		2
# define CYLINDER_ID	3
# define CONE_ID		4
# define OBJ_FILE_ID	5


/*
** ------------------------------Structures-------------------------------------
** -------------------------Structures Fot Cernel-------------------------------
*/

typedef	struct		s_rgb2
{
	int	r;
	int	g;
	int	b;
}					t_rgb2;

typedef	struct		s_read
{
	char			**buff; //Буффер для считывания файла
	int				str_c; // количество считанных стрк
}					t_read;

typedef	struct		s_light
{
	t_vector			pos;
	t_rgb2			rgb;
	int				check[2];
	struct s_light	*next;
}					t_light;

typedef	struct		s_obj
{
	char 			*obj_name;
	int				type;
	t_vector			pos;
	t_vector			dir;

	t_rgb2			rgb;

	int				reflect;
	float			coef_refl;

	int				spec;
	float			radius;

	float			limit; // ограничение объекта

	int				refr; //
	float			ind_refr; // Коэффициент преломления
	float			coef_refr;

	int				text_on;
	char			*texture;

	int				obj_on;
	char			*file_name;

	int				check[11];

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
	char			*effecr_name;
	int				effect_on;
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
	int		check[4];
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

	t_obj *obj_mas; // Текущий объект с которым работаем
	t_light *lgh_mas; // Текущий объект с которым работаем

}		t_rt;

/*
** ------------------------------Functions----------------------------------------
*/

int main();

void check_tag(t_rt *rt, char *line, int str_c);
void create_list(t_rt *rt, char *type);

void scene_parser(t_rt *rt, char *line, int str_c);
void test_scene(t_rt *rt, int str_c);

void camera_parser(t_rt *rt, char *line, int str_c);
void test_camera(t_rt *rt, int str_c);

void light_parser(t_rt *rt, char *line, int str_c);
void test_light(t_rt *rt, int str_c);
void check_inti_rgb(t_rt *rt, int str_c);

void object_parser(t_rt *rt, char *line, int str_c);

void list_to_mas(t_rt *rt);

char *take_int(char *line, int *put_s, int str_c);
char *take_double(char *line, float *put_s, int str_c);
char *take_word(char *line, char **put_s, int str_c);
char *take_res(char *line, int *put_s, int str_c);
t_vector get_vector_value_d(char *str, int str_c);
char *take_vector(char *line, t_vector *put_s, int str_c);
t_rgb2 get_vector_value_rgb(char *str, int str_c);
char *take_rgb(char *line, t_rgb2 *put_s, int str_c);
char *take_refl(char *line, t_obj *obj, int str_c);
float take_coef(char *line, int str_c, char let);
char *take_refraction(char *line, t_obj *obj, int str_c);
char *take_on_off(char *line, int *put_s, int str_c);
char *take_texture(char *line, t_obj *obj, char *type,int str_c);

void cheak_camera(t_rt *rt);
void cheak_light(t_rt *rt);
void cheak_scene(t_rt *rt);
void cheak_object(t_rt *rt);
void cheak_part(t_rt *rt);

void	kill_error(char *message, int string_number);
int		kill_all(char *message);
#endif