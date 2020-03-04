/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 16:20:37 by daron             #+#    #+#             */
/*   Updated: 2020/03/04 16:49:20 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <OpenCL/opencl.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
#include  <math.h>
# include "ftvector.h"
# include "libft.h"
# include <SDL2/SDL.h>

# define CMRW			CL_MEM_READ_WRITE
# define CDTG			CL_DEVICE_TYPE_GPU

/*
** Size configuration
*/

# define     EQN_EPS     1e-9
# define FOV			2.0

/*
** Object ID
*/

# define SPHERE_ID		1
# define PLANE_ID		2
# define CYLINDER_ID	3
# define CONE_ID		4
# define OBJ_FILE_ID	5
# define PARABOLOID_ID	6
# define DISK_ID		7
# define TORUS_ID		8


/*
** Texture ID
*/

# define WAVES_ID		1
# define CHECH_BEARD_ID 2

/*
** SkyBox ID
*/

# define SB_BRICK_ID	1
# define SB_HERNIA_1_ID 2

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
    cl_float            torus_r;
	cl_int				name;
	cl_int				specular;
    cl_int              contruction_id;
	cl_int				reflect;
	cl_int				texture_id;
	cl_float			coef_refl;
	cl_int				refr; //если == 1 то этот объект будет преломлять свет
	cl_float			ind_refr; // Коэффициент преломления
	cl_float			coef_refr;
	cl_float			limit;
}						t_cl_object;

typedef	struct			s_cl_light
{
	cl_float3			pos;
	cl_float			inten;
	cl_float3			col;
}						t_cl_light;

typedef struct		s_cl_txdata
{
	cl_uint			width;
	cl_uint			height;
	cl_uint			start;
}					t_cl_txdata;
typedef union		s_cl_txt_rgb
{
	cl_uint			c;
	cl_uchar		bgra[4];
}					t_cl_txt_rgb;

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
	cl_mem				txt_data_mem;
	cl_mem				txt_rgb_mem;
	cl_mem				light_mem;
	cl_mem				img;
	cl_mem				d_m;
	cl_mem				i_m;
	cl_mem				obj;
	t_cl_object			*cl_obj;
	t_cl_light			*cl_light;
	t_cl_txdata			*cl_txdata;
	t_cl_txt_rgb		*cl_txt_rgb;
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

typedef union		u_rgb
{
	cl_int			c;
}					t_rgb;

typedef struct		s_txdata
{
	cl_uint			width;
	cl_uint			height;
	cl_uint			start;
}					t_txdata;

typedef struct		s_txgpu
{
	t_txdata		*txdata;
	int				*tx;
	int				tx_count;
	int				total_size;
}					t_txgpu;

typedef struct			s_rgb2
{
	float				r;
	float				g;
	float				b;
}						t_rgb2;

typedef	struct			s_read
{
	char				**buff; //Буффер для считывания файла
	int					str_c; // количество считанных стрк
}						t_read;

typedef	struct			s_cam
{
	t_vector			pos;
	t_vector			dir;
	int					check[2];
}						t_cam;

typedef	struct			s_light
{
	t_vector			pos;
	t_rgb2				rgb;
	int					check[2];
	struct s_light		*next;
}						t_light;

typedef struct			s_obj
{
	char 				*obj_name; //Храним имя объекта строкаой
	int					type; // Идентификатор типа SPHERE_ID
	t_vector			pos;
	t_vector			dir;
	t_rgb2				rgb;
	int					reflect;//если == 1 то этот объект будет отражающим
	float				coef_refl; // коэффициент отражения
	int					spec; // блестящесть
	float				radius;
    float               torus_r;
	float				limit; // ограничение объекта
	int					refr; //если == 1 то этот объект будет преломлять свет
	float				ind_refr; // Коэффициент преломления
	float				coef_refr;
	int					text_on; //есль == 1 говорит что текстуры включены
	char				*texture;//иня файла где храниться текстура
	int					obj_on;//есль == 1 говорит это будет obj фаил
	int                 texture_id;
	char				*file_name; // имя obj файла
	int                 contruction_id;
	int					check[13];
	struct s_obj		*next;
}						t_obj;

typedef struct			s_move
{
	t_vector			i;
	t_vector			j;
	t_vector			k;
}						t_move;

typedef	struct		s_win
{
	char				*windname;
	char				*effecr_name; // имя эффекта
	int					effect_on;
	int					size[2];
	int 				anti_alias;//Уровень антиалиасинга
	SDL_Window			*window;
	SDL_Renderer		*render;
	SDL_Event			event;
	SDL_Texture			*textur;
	int					check[6];
}						t_win;

typedef	struct			s_scene
{
	float				spec; // Уровень блестящести
	int					obj_c; // Количество считанных объектов
	int					lgh_c; // Количество источников света
	int					maxref;
	float				ambient;
	int					skybox_id;
	int					check[5];
} 						t_scene;

typedef struct			s_rt
{
	t_read				read_b;
	t_scene 			scene;
	t_win 				window;
	t_cam 				cam;
	t_obj 				*obj_head; // голова списка
	t_light 			*lgh_head; // голова списка
	t_obj 				*obj_cur; // Текущий объект с которым работаем
	t_light 			*lgh_cur; // Текущий объект с которым работаем
	t_obj 				*obj_mas; // Текущий объект с которым работаем
	t_light 			*lgh_mas; // Текущий объект с которым работаем
	t_txgpu				txt_gpu;
	int					select_obj;
	t_cl				*cl;
	t_parse_obj			*data_obj;
}						t_rt;
/*
** ------------------Function Prototype--------------------------------
*/
void					check_objs(t_rt *rt);
void					ft_init_cl(t_cl *cl, t_rt *rt);
void					start_kernel(t_cl *cl, t_rt *rt);
void					init_cl(t_cl *cl, t_rt *rt);
t_cl_object				*transform_obj_data(t_rt *rt);
t_cl_light				*transform_light_data(t_rt *rt);
void					kill_error(char *message, int string_number);
int						kill_all(char *message);
void					sdl_initialize(t_rt *rt);
double					get_quadratic_solution(double a, double b, double discriminant);
void					my_free(t_rt *rt);
float					ft_clamp(float value, float min, float max);
void					events(t_rt *rt);
void					mouse_down(t_rt *rt);
void					key_down(t_rt *rt, t_move *move);
void					key_down_for_object(t_rt *rt, t_move *move);
void					detail_key(t_rt *rt);
void					swithc_gloss(t_rt *rt);
void					reflection_key(t_rt *rt);
void					printf_scene_data(t_rt *rt);
int						intersection(t_rt *rt, t_vector *ray_dir, t_vector *cam_pos);
float					get_paraboloid_intersection(t_vector *ray_dir, t_vector *cam_pos, int i, t_rt *rt);
float					get_disk_intersection(t_vector *ray_dir, t_vector *cam_pos, int i, t_rt *rt);
float					get_cylinder_intersection(t_vector *ray_dir, t_vector *cam_pos, int i, t_rt *rt);
/*
** ------------------Function Parser--------------------------------
*/
void					printf_scene_data(t_rt *rt);
void					init_rt(t_rt *rt, char *filename, int str_c);
void					parse_line(t_rt *rt, char *line, int str_c);
void					init_struct(t_rt *rt);
void					check_tag(t_rt *rt, char *line, int str_c);
void					create_list(t_rt *rt, char *type);
void					scene_parser(t_rt *rt, char *line, int str_c);
void					check_inti_alias(int anti_alias, int str_c);
void					check_inti_maxref(int maxref, int str_c);
void					check_inti_ambiant(float ambiant, int str_c);
void					check_inti_effect(t_rt *rt, int str_c);
void					check_inti_res(t_rt *rt, int str_c);
void					test_scene(t_rt *rt, int str_c);
void					camera_parser(t_rt *rt, char *line, int str_c);
void					test_camera(t_rt *rt, int str_c);
void					light_parser(t_rt *rt, char *line, int str_c);
void					test_light(t_rt *rt, int str_c);
void					check_inti_rgb(t_rt *rt, int str_c);
void					object_parser(t_rt *rt, char *line, int str_c);
void					test_object(t_rt *rt, int str_c);
void					check_inti_obj_type(t_rt *rt, int str_c);
void					check_inti_reflection(t_rt *rt, int str_c);
void					check_inti_refraction(t_rt *rt, int str_c);
void					check_inti_radius(t_rt *rt, int str_c);
void					check_inti_dir_obj(t_rt *rt, int str_c);
void					check_inti_obj_rgb(t_rt *rt, int str_c);
void					list_to_mas(t_rt *rt);
void					copy_obj(t_rt *rt);
void					delete_obj_list(t_rt *rt);
void					copy_light(t_rt *rt);
void					delete_light_list(t_rt *rt);
char					*take_int(char *line, int *put_s, int str_c);
char					*take_skybox(char *line, int *skybox_id, int str_c);
char					*take_double(char *line, float *put_s, int str_c);
char					*take_word(char *line, char **put_s, int str_c);
char					*take_res(char *line, int *put_s, int str_c);
char                    *take_construction(char *line, int *construction_id, int str_c);
double					cheak_double(char *line, int str_c);
char					*take_vector(char *line, t_vector *put_s, int str_c);
char					*take_rgb(char *line, t_rgb2 *put_s, int str_c);
char					*take_refl(char *line, t_obj *obj, int str_c);
float					take_coef(char *line, int str_c, char let);
char					*take_refraction(char *line, t_obj *obj, int str_c);
char					*take_on_off(char *line, int *put_s, int str_c);
char					*take_texture(char *line, t_obj *obj, char *type,int str_c);
void					cheak_camera(t_rt *rt);
void					cheak_light(t_rt *rt);
void					cheak_scene(t_rt *rt);
void					cheak_object(t_rt *rt);
void					cheak_part(t_rt *rt);
void 					texture_init(t_rt *rt);
#endif
