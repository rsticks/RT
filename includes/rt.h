/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 16:20:37 by daron             #+#    #+#             */
/*   Updated: 2020/01/26 16:04:49 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <OpenCL/opencl.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include "ftvector.h"
# include "libft.h"
# include <SDL2/SDL.h>

# define CMRW			CL_MEM_READ_WRITE
# define CDTG			CL_DEVICE_TYPE_GPU

/*
** Size configuration
*/

# define W_WIDTH 		1400
# define W_HEIGHT 		1400
# define FOV			2.0

/*
** Object ID
*/

# define SPHERE_ID		1
# define PLANE_ID		2
# define CYLINDER_ID	3
# define CONE_ID		4
# define OBJ_FILE_ID	5

/*
** Static parametrs
*/

# define EPS			0.0001
# define ALPHA			0.05
# define DELTA			10.0

# define SEKKS			sdl->event.key.keysym.sym
# define SSO			sdl->select_obj
# define SC				sdl->cam

/*
** ------------------------------Structures-------------------------------------
** -------------------------Structures Fot Cernel-------------------------------
*/

typedef struct			s_cl_object
{
	cl_float3			pos;
	cl_float3			rot;
	cl_float3			col;
	cl_float			r;
	cl_int				name;
	cl_float			specular;
	cl_float			coef_refl;
	cl_float			limit;
}						t_cl_object;

typedef	struct			s_cl_light
{
	cl_float3			pos;
	cl_float			inten;
	cl_float3			col;
}						t_cl_light;

typedef struct			s_cl
{
	cl_context			ct;
	cl_command_queue	q;
	cl_platform_id		*p_id;
	cl_device_id		*dev_id;
	cl_uint				n_plat;
	cl_uint				n_dev;
	cl_kernel			kernel;
	cl_program			prog;
	cl_mem				obj_mem;
	cl_mem				light_mem;
	cl_mem				img;
	cl_mem				d_m;
	cl_mem				i_m;
	t_cl_object			*cl_obj;
	t_cl_light			*cl_light;
	int					*data;
	int					o_c;
	int					l_c;
	int					fd;
	int					i;
	size_t				k_l;
	char				*k_s;
	int					err;
}						t_cl;
/*
** ------------------Structures Fot main program--------------------------------
*/
typedef struct			s_rgb2
{
	int					r;
	int					g;
	int					b;
}						t_rgb2;

typedef	struct		s_read
{
	char			**buff; //Буффер для считывания файла
	int				str_c; // количество считанных стрк
}					t_read;

typedef	struct			s_cam
{
	t_vector			pos;
	t_vector			dir;
	int					check[2];
}						t_cam;

/*
** inten - Intensity
*/
typedef	struct			s_light
{
	t_vector			pos;
	t_rgb2				rgb;
	int					check[2];
	struct s_light		*next;
}						t_light;

/*
** r - Radius
** specular - Reflection level
** name - Object ID
*/
typedef struct			s_obj
{
	char 				*obj_name;
	int					type;

	t_vector			pos;
	t_vector			dir;
	t_rgb2				rgb;

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

	struct s_object		*next;
}						t_obj;

typedef struct			s_move
{
	t_vector			i;
	t_vector			j;
	t_vector			k;
}						t_move;

typedef	struct		s_win
{
	char			*windname;
	char			*effecr_name;
	int				effect_on;
	int				size[2];
	int 			anti_alias;

	SDL_Window			*window;
	SDL_Renderer		*render;
	SDL_Event			event;
	SDL_Texture			*textur;

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

	t_obj			*select_obj;
	t_cl				*cl;

}		t_rt;

/*
** ambient - Ambient light scene
** line_count - Count of line in scene file
** dital - Scene ditalization level
*/
typedef struct			s_sdl
{
	SDL_Window			*window;
	SDL_Renderer		*render;
	SDL_Event			event;
	SDL_Texture			*textur;
	t_cam				cam;
	t_obj			*obj;
	t_light				*light;
	float				ambient;
	int					line_count;
	char				**scene;
	int					dital;
	int					gloss_activ;
	int					reflect_count;
	int					pref;
	t_obj				*select_obj;
	t_cl				*cl;
}						t_sdl;

/*
** ------------------Function Prototype--------------------------------
*/
void			ft_init_cl(t_cl *cl, t_rt *rt);
void					start_kernel(t_cl *cl, t_rt *rt);
void			init_cl(t_cl *cl, t_rt *rt);
t_cl_object			*transform_obj_data(t_rt *rt);
t_cl_light			*transform_light_data(t_rt *rt);

int						kill_all(char *message);
void					sdl_initialize(t_rt *rt);
double					get_quadratic_solution(double a, double b,
												double discriminant);
void					scene_mas(t_sdl *sdl);
void					my_free(t_sdl *sdl);
float					ft_clamp(float value, float min, float max);

int						ft_atoi_n(char *str, int *k);

void					events(t_sdl *sdl);
void					mouse_down(t_sdl *sdl);
void					key_down(t_sdl *sdl, t_move *move);
void					key_down_for_object(t_sdl *sdl, t_move *move);
void					detail_key(t_sdl *sdl);
void					swithc_gloss(t_sdl *sdl);
void					reflection_key(t_sdl *sdl);
void					swithc_pref(t_sdl *sdl);

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



#endif
