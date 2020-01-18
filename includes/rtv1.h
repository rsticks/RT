/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 16:20:37 by daron             #+#    #+#             */
/*   Updated: 2019/12/05 16:43:35 by rsticks          ###   ########.fr       */
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
typedef struct			s_color
{
	int					r;
	int					g;
	int					b;
}						t_color;

typedef	struct			s_cam
{
	t_vector			pos;
	t_vector			rot;
}						t_cam;

/*
** inten - Intensity
*/
typedef	struct			s_light
{
	t_vector			pos;
	t_color				col;
	float				inten;
	struct s_light		*next;
}						t_light;

/*
** r - Radius
** specular - Reflection level
** name - Object ID
*/
typedef struct			s_object
{
	t_vector			pos;
	t_vector			rot;
	t_color				col;
	float				r;
	int					name;
	float				specular;
	struct s_object		*next;
}						t_object;

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
	t_object			*obj;
	t_light				*light;
	float				ambient;
	int					line_count;
	char				**scene;
	int					dital;
	int					gloss_activ;
	int					reflect_count;
	int					pref;
	t_object			*select_obj;
	t_cl				*cl;
}						t_sdl;

typedef struct			s_move
{
	t_vector			i;
	t_vector			j;
	t_vector			k;
}						t_move;

/*
** ------------------Function Prototype--------------------------------
*/
void					ft_init_cl(t_cl *cl);
void					start_kernel(t_cl *cl, t_sdl *sdl);
void					init_cl(t_cl *cl);
t_cl_object				*transform_obj_data(t_object *obj, int *count);
t_cl_light				*transform_light_data(t_light *light, int *count);
void					scene_parser(t_sdl *sdl, char *scene_name);
int						kill_all(char *message);
void					sdl_initialize(t_sdl *sdl);
double					get_quadratic_solution(double a, double b,
												double discriminant);
void					scene_mas(t_sdl *sdl);
void					my_free(t_sdl *sdl);
float					ft_clamp(float value, float min, float max);
void					object_parser(t_sdl *sdl, char **param);
void					scene_parser(t_sdl *sdl, char *scene_name);
void					string_parser(t_sdl *sdl);
int						ft_atoi_n(char *str, int *k);
t_light					*ft_add_light_link(t_sdl *sdl, t_light *link);
t_object				*ft_add_object_link(t_sdl *sdl, t_object *link);
t_object				*intersection(t_sdl *sdl,
									t_vector *ray_dir, t_vector *cam_pos);
void					ft_add_light(t_sdl *sdl, int *k, int ind);
void					ft_add_cyl_cone(t_sdl *sdl, int *k, int name, int ind);
void					ft_add_plane(t_sdl *sdl, int *k, int i);
void					ft_add_sphere(t_sdl *sdl, int *k, int i);
void					check_object(t_sdl *sdl);
void					ft_col_n_pos(t_sdl *sdl, t_object *link, int k);
void					events(t_sdl *sdl);
void					mouse_down(t_sdl *sdl);
void					key_down(t_sdl *sdl, t_move *move);
void					key_down_for_object(t_sdl *sdl, t_move *move);
void					detail_key(t_sdl *sdl);
void					swithc_gloss(t_sdl *sdl);
void					reflection_key(t_sdl *sdl);
void					swithc_pref(t_sdl *sdl);

#endif
