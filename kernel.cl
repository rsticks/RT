/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel.cl                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:05:27 by rsticks           #+#    #+#             */
/*   Updated: 2019/11/06 14:05:27 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NULL ((void*)0)
/*
** Object name
*/

# define FOV			2.0

/*
** Object id
*/
# define SPHERE_ID 1
# define PLANE_ID 2
# define CYLINDER_ID 3
# define CONE_ID 4

/*
** Help
*/
# define EPS 0.0001

typedef struct		s_cl_object
{
	float3			pos;
	float3			rot;
	float3			col;
	float			r;
	int				name;
	float			specular;
}					t_cl_object;

typedef	struct		s_cl_light
{
	float3			pos;
	float			inten;
	float3			col;
}					t_cl_light;

typedef	struct		s_ray
{
	float3			orig;
	float3			dir;
}					t_ray;

typedef struct		s_point
{
	float 			x;
	float 			y;
}					t_point;

typedef	struct		s_cam
{
	float3			pos;
	float3			rot;
}					t_cam;

typedef struct				s_sdl
{
	int						W_WIDTH;
	int						W_HEIGHT;
	t_cam					cam;
	__global t_cl_object	*obj;
	__global t_cl_light		*light;
	float					ambient;
	int 					dital;
	float3					ray_dir;
	float					t;
	float3					norm;
	float					t0;
	float3 					dist;
	int						gloss_activ;
	int 					cpt;
	int						reflect_count;
	float3					refpos;
	float3					ref;
	int 					pref;
	int						o_count;
	int						l_count;
}							t_sdl;

void		ft_fzero(float *s, int n);
float		ft_clamp(float value, float min, float max);
float3		vec_sum(float3 v1, float3 v2);
float3		vec_sub(float3 v1, float3 v2);
float3		vec_scale(float3 v1, float factor);
float		vec_dot(float3 v1, float3 v2);
float		vec_len(float3 v1);
float3		vec_norm(float3 v1);
float3  	vec_cross(float3 v1, float3 v2);
float		get_quadratic_solution(float a, float b, float discriminant);
float 		get_sphere_intersection(float3 *ray_dir, float3 *cam_pos, int i, t_sdl *sdl);
float 		get_plane_intersection(float3 *ray_dir, float3 *cam_pos, int i, t_sdl *sdl);
float 		get_cone_intersection(float3 *ray_dir, float3 *cam_pos, int i, t_sdl *sdl);
float 		get_cylinder_intersection(float3 *ray_dir, float3 *cam_pos, int i, t_sdl *sdl);
int			intersection(t_sdl *sdl, float3 *ray_dir, float3 *cam_pos);
float3 		object_norm(t_sdl *sdl, int i, float3 pos);
int			shadow(t_sdl *sdl, int i_obj, int i_light, float3 pos);
void 		transfer_light(int i_obj, int i_light, float *tab, float d, t_sdl *sdl);
void 		gloss(t_sdl *sdl, int i_obj, float *tab, float3 *dist, float d);
int 		ref_inter(t_sdl *sdl, int i_cur_obj , float3 pos);
int 		ref_init(t_sdl *sdl, int i_obj, float3 *pos);
int 		reflection(t_sdl *sdl, int i_obj, float3 *pos, float *tab);
void 		calculate_light(t_sdl *sdl, int i_obj, float *tab);
void		ft_average(float *r, float *tab);
void 		create_ray(t_sdl *sdl, float x, float y);
void 		ft_tracing(float x, float y, t_sdl *sdl, __global int *data, int gid);



float   ft_clamp(float value, float min, float max)
{
	if (value < min)
		value = min;
	if (value > max)
		value = max;
	return (value);
}


float3		vec_sum(float3 v1, float3 v2)
{
	float3 v;

	v.x = v1.x + v2.x;
	v.y = v1.y + v2.y;
	v.z = v1.z + v2.z;;
	return (v);
}

float3	vec_sub(float3 v1, float3 v2)
{
	float3 v;

	v.x = v1.x - v2.x;
	v.y = v1.y - v2.y;
	v.z = v1.z - v2.z;
	return (v);
}

float3	vec_scale(float3 v1, float factor)
{
	float3 v;

	v.x = v1.x * factor;
	v.y = v1.y * factor;
	v.z = v1.z * factor;
	return (v);
}

float	vec_dot(float3 v1, float3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

float		vec_len(float3 v1)
{
	return (native_sqrt(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z));
}

float3	vec_norm(float3 v1)
{
	float	norm_k;

	norm_k = 1 / vec_len(v1);
	return (vec_scale(v1, norm_k));
}

float3   vec_cross(float3 v1, float3 v2)
{
	float3   v;

	v.x = v1.y * v2.z - v1.z * v2.y;
	v.y = v1.z * v2.x - v1.x * v2.z;
	v.z = v1.x * v2.y - v1.y * v2.x;
	return (v);
}

float				get_quadratic_solution(float a, float b, float discriminant)
{
	float 			t1;
	float 			t2;

	t1 = (-b - native_sqrt(discriminant)) / (2 * a);
	t2 = (-b + native_sqrt(discriminant)) / (2 * a);
	if ((t1 <= t2 && t1 >= 0) || (t1 >= 0 && t2 < 0))
		return (t1);
	else if ((t2 <= t1 && t2 >= 0) || (t1 < 0 && t2 >= 0))
		return (t2);
	return (-1);
}


float get_sphere_intersection(float3 *ray_dir, float3 *cam_pos, int i, t_sdl *sdl)
{
	float b;
	float c;
	float a;
	float discriminant;

	sdl->dist = vec_sub(*cam_pos, sdl->obj[i].pos);
	a = vec_dot(*ray_dir, *ray_dir);
	b = 2 * vec_dot(*ray_dir, sdl->dist);
	c = vec_dot(sdl->dist, sdl->dist) - pow(sdl->obj[i].r, 2);
	discriminant = pow(b, 2) - 4 * a * c;
	if (discriminant < 0)
		return (-1);
	return (get_quadratic_solution(a, b , discriminant));
}

float get_plane_intersection(float3 *ray_dir, float3 *cam_pos, int i, t_sdl *sdl)
{
	float dist;
	
	dist = ((vec_dot(sdl->obj[i].rot, sdl->obj[i].pos) - vec_dot(sdl->obj[i].rot, 
	*cam_pos)) / vec_dot(sdl->obj[i].rot, *ray_dir));
	if (dist < EPS)
		return (-1);
	return (dist);
}

float get_cone_intersection(float3 *ray_dir, float3 *cam_pos, int i, t_sdl *sdl)
{
	float	b;
	float	c;
	float	a;
	float discriminant;

	sdl->dist = vec_sub(*cam_pos, sdl->obj[i].pos);
	sdl->obj[i].rot = vec_norm(sdl->obj[i].rot);
	a = vec_dot(*ray_dir, *ray_dir) - (1 + pow(tan(sdl->obj[i].r), 2)) 
	* pow(vec_dot(*ray_dir, sdl->obj[i].rot), 2);
	b = 2 * (vec_dot(*ray_dir, sdl->dist) - (1 + pow(tan(sdl->obj[i].r), 2)) 
	* vec_dot(*ray_dir, sdl->obj[i].rot) * vec_dot(sdl->dist, sdl->obj[i].rot));
	c = vec_dot(sdl->dist, sdl->dist) - (1 + pow(tan(sdl->obj[i].r), 2)) 
	* pow(vec_dot(sdl->dist, sdl->obj[i].rot), 2);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1);
	return (get_quadratic_solution(a, b, discriminant));
}

float get_cylinder_intersection(float3 *ray_dir, float3 *cam_pos, int i, t_sdl *sdl)
{
	float b;
	float c;
	float a;
	float discriminant;

	sdl->dist = vec_sub(*cam_pos, sdl->obj[i].pos);
	sdl->obj[i].rot = vec_norm(sdl->obj[i].rot);
	a = vec_dot(*ray_dir, *ray_dir) - pow(vec_dot(*ray_dir, sdl->obj[i].rot), 2);
	b = 2 * (vec_dot(*ray_dir, sdl->dist) - (vec_dot(*ray_dir, sdl->obj[i].rot) 
	* vec_dot(sdl->dist, sdl->obj[i].rot)));
	c = vec_dot(sdl->dist, sdl->dist) - pow(vec_dot(sdl->dist, sdl->obj[i].rot), 2) 
	- pow(sdl->obj[i].r, 2);
	discriminant = pow(b, 2) - 4 * a * c;
	if (discriminant < 0)
		return (-1);
	return (get_quadratic_solution(a, b, discriminant));
}

int			intersection(t_sdl *sdl, float3 *ray_dir, float3 *cam_pos)
{
	float dist;
	int i;
	int f;

	i = 0;
	f = -1;
	sdl->t = 90000.0;
	dist = 0.01;
	while (i < sdl->o_count)
	{
		if (sdl->obj[i].name == SPHERE_ID)
			dist = get_sphere_intersection(ray_dir, cam_pos, i, sdl);
		else if (sdl->obj[i].name == CYLINDER_ID)
			dist = get_cylinder_intersection(ray_dir, cam_pos, i, sdl);
		else if (sdl->obj[i].name == CONE_ID)
			dist = get_cone_intersection(ray_dir, cam_pos, i, sdl);
		else if (sdl->obj[i].name == PLANE_ID)
			dist = get_plane_intersection(ray_dir, cam_pos, i, sdl);
		if (dist > EPS && dist < sdl->t)
		{
			f = i;
			sdl->t = dist;
		}
		i++;
	}
	return (f);
}


float3 object_norm(t_sdl *sdl, int i, float3 pos)
{
	float3 norm;
	float3 tmp;
	float3 tmp2;

	if (sdl->obj[i].name == CONE_ID || sdl->obj[i].name == CYLINDER_ID)
	{
		tmp = vec_scale(sdl->obj[i].rot, (vec_dot(sdl->ray_dir, sdl->obj[i].rot) * sdl->t 
		+ vec_dot(sdl->dist, sdl->obj[i].rot)));
		if (sdl->obj[i].name == CONE_ID)
			tmp = vec_scale(tmp, (1 + pow(tan(sdl->obj[i].r), 2)));
		tmp2 = vec_sub(pos, sdl->obj[i].pos);
		norm = vec_sub(tmp2, tmp);
	}
	else if (sdl->obj[i].name == PLANE_ID)
		norm = sdl->obj[i].rot;
	else if (sdl->obj[i].name == SPHERE_ID)
		norm = vec_sub(pos, sdl->obj[i].pos);
	return (vec_norm(norm));
}


void	transfer_light(int i_obj, int i_light, float *tab, float d, t_sdl *sdl)
{
	//printf("%f\n", d);
	
	tab[3] = ft_clamp(tab[3] * 4.0 * d, 0.0, 1.0);
	tab[0] += tab[3] * (sdl->obj[i_obj].col.x / 255) * (sdl->light[i_light].col.x / 255);
	tab[1] += tab[3] * (sdl->obj[i_obj].col.y / 255) * (sdl->light[i_light].col.y / 255);
	tab[2] += tab[3] * (sdl->obj[i_obj].col.z / 255) * (sdl->light[i_light].col.z / 255);
}

int		shadow(t_sdl *sdl, int i_obj, int i_light, float3 pos)
{
	float3	dist;
	float 	d;
	int 	i;

	
	i = 0;
	dist = vec_sub(sdl->light[i_light].pos, pos);
	sdl->t = native_sqrt(vec_dot(dist, dist));
	dist = vec_norm(dist);
	while (i < sdl->o_count)
	{
		if (i != i_obj)
		{
			if (sdl->obj[i].name == SPHERE_ID)
				d = get_sphere_intersection(&dist, &pos, i, sdl);
			else if (sdl->obj[i].name == CYLINDER_ID)
				d = get_cylinder_intersection(&dist, &pos, i, sdl);
			else if (sdl->obj[i].name == CONE_ID)
				d = get_cone_intersection(&dist, &pos, i, sdl);
			else if (sdl->obj[i].name == PLANE_ID)
				d = get_plane_intersection(&dist, &pos, i, sdl);
			if (d > EPS && d < sdl->t)
				return (1);
		}
		i++;
	}
	return (0);
}

void gloss(t_sdl *sdl, int i_obj, float *tab, float3 *dist, float d)
{
	float	spec;
	float	tmp;
	float3	ref;

	if (sdl->obj[i_obj].name != PLANE_ID && sdl->gloss_activ == 1)
	{
		spec = 0.0;
		ref = vec_scale(sdl->norm, (2.0 * vec_dot(sdl->norm, *dist)));
		ref = vec_sub(*dist, ref);
		tmp = vec_dot(ref, sdl->ray_dir);
		if (tmp > 0.0 && tab[3] > sdl->ambient)
		{

			spec = native_powr(tmp, (int)sdl->obj[i_obj].specular) * 4 * d;
			spec = ft_clamp(spec, 0.0, 1.0);
		}
		tab[1] += spec;
		tab[2] += spec;
		tab[3] += spec;
	}
}

int ref_inter(t_sdl *sdl, int i_cur_obj , float3 pos)
{
	double	dist;
	int i;
	char f;

	i = 0;
	f = -1;
	while (i < sdl->o_count)
	{
		if (i_cur_obj != i)
		{
			if (sdl->obj[i].name == SPHERE_ID)
				dist = get_sphere_intersection(&sdl->ref, &pos, i, sdl);
			else if (sdl->obj[i].name == CYLINDER_ID)
				dist = get_cylinder_intersection(&sdl->ref, &pos, i, sdl);
			else if (sdl->obj[i].name == CONE_ID)
				dist = get_cone_intersection(&sdl->ref, &pos, i, sdl);
			else if (sdl->obj[i].name == PLANE_ID)
				dist = get_plane_intersection(&sdl->ref, &pos, i, sdl);
			if (dist > EPS && dist < sdl->t)
			{
				f = i;
				sdl->t = dist;
			}
		}
		i++;
	}
	return (f);
}

int ref_init(t_sdl *sdl, int i_obj, float3 *pos)
{
	int	tmp2;

	sdl->t = 8000.0;
	sdl->ref = vec_scale(sdl->norm, (2 * vec_dot(sdl->refpos, sdl->norm)));
	sdl->ref = vec_sub(sdl->refpos, sdl->ref);
	sdl->ref = vec_norm(sdl->ref);
	tmp2 = ref_inter(sdl, i_obj, *pos);
	if (tmp2 == -1)
		return (-1);
	*pos = (float3){pos->x + sdl->t * sdl->ref.x,
				   pos->y + sdl->t * sdl->ref.y,
				   pos->z + sdl->t * sdl->ref.z};
	sdl->refpos = (float3){sdl->ref.x, sdl->ref.y, sdl->ref.z};
	sdl->norm = object_norm(sdl, tmp2, *pos);
	return (tmp2);
}

int reflection(t_sdl *sdl, int i_obj, float3 *pos, float *tab)
{
	int i_light;
	float3	dist;
	float	d;
	int tmp2;

	while (sdl->cpt < sdl->reflect_count && (tmp2 = ref_init(sdl, i_obj, pos)) != -1)
	{
		sdl->cpt++;
		i_light = 0;
		while (i_light < sdl->l_count)
		{
			tab[3] = sdl->ambient;
			dist = vec_sub(sdl->light[i_light].pos, *pos);
			d = ft_clamp(1.0 / native_sqrt(native_sqrt(vec_dot(dist, dist))), 0.0, 1.0);
			dist = vec_norm(dist);
			if (shadow(sdl, tmp2, i_light, *pos) == 0)
				tab[3] += ft_clamp(vec_dot(dist, sdl->norm), 0.0, 1.0);		
			transfer_light(tmp2, i_light, tab, d, sdl);
			gloss(sdl, i_obj, tab, &dist , d);
			i_light++;
		}
	}
	return (0);
}

void 	calculate_light(t_sdl *sdl, int i_obj, float *tab)
{
	float3 pos;
	float3 dist;
	float d;
	int ind;
	int	tmp;

	ind = 0;
	pos = (float3){sdl->cam.pos.x + sdl->t * sdl->ray_dir.x,
				  sdl->cam.pos.y + sdl->t * sdl->ray_dir.y,
				  sdl->cam.pos.z + sdl->t * sdl->ray_dir.z};
	sdl->norm = object_norm(sdl, i_obj, pos);

	while (ind < sdl->l_count)
	{
		tab[3] = sdl->ambient;
		dist = vec_sub(sdl->light[ind].pos, pos);
		d = ft_clamp((1.0 / native_sqrt(native_sqrt(vec_dot(dist, dist)))), 0.0, 1.0);
		dist = vec_norm(dist);
		if (shadow(sdl, i_obj, ind, pos) == 0)
			tab[3] += ft_clamp(vec_dot(dist, sdl->norm), 0.0, 1.0);
		transfer_light(i_obj, ind, tab, d, sdl);
		gloss(sdl, i_obj, tab, &dist , d);
		ind++;
	}
	sdl->refpos = (float3){sdl->ray_dir.x, sdl->ray_dir.y, sdl->ray_dir.z};
	if (sdl->reflect_count > 0)
		reflection(sdl, i_obj, &pos, tab);
}


void	ft_average(float *r, float *tab)
{
	r[0] += ft_clamp(tab[0], 0.0, 1.0);
	r[1] += ft_clamp(tab[1], 0.0, 1.0);
	r[2] += ft_clamp(tab[2], 0.0, 1.0);
}

void create_ray(t_sdl *sdl, float x, float y)
{
	float u, v;
	float3 i, j, k;

	u = (sdl->W_WIDTH - (float)x * 2.0) / sdl->W_HEIGHT;
	v = (sdl->W_HEIGHT - (float)y * 2.0) / sdl->W_WIDTH;
	k = vec_sub(sdl->cam.rot, sdl->cam.pos);
	k = vec_norm(k);
	i = vec_cross(k, (float3){0.0, 1.0, 0.0});
	i = vec_norm(i);
	j = vec_cross(i, k);
	sdl->ray_dir = (float3){u * i.x + v * j.x + FOV * k.x, u * i.y + v * j.y + 
	FOV * k.y, u * i.z + v * j.z + FOV * k.z}; 
	sdl->ray_dir = vec_norm(sdl->ray_dir);
	sdl->cpt = 0;
}

void    ft_fzero(float *s, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		s[i] = 0.0f;
		i++;
	}
}

void ft_tracing(float x, float y, t_sdl *sdl, __global int *data, int gid)
{
	float	tab[4];
	float	r[3];
	int x_next = (int)x + 1, y_next = (int)y + 1; 
	float p;
	int i;

	ft_fzero(r, 3);
	p = 0.0;
	while (y < y_next)
	{
		while (x < x_next)
		{
			p += 1;
			create_ray(sdl, x, y);
			ft_fzero(tab, 4);
			i = intersection(sdl, &sdl->ray_dir, &sdl->cam.pos);
			if(i >= 0)
				calculate_light(sdl, i, tab);
			ft_average(r, tab);
			x = x + (1.0 / sdl->dital);
		}
		y = y + (1.0 / sdl->dital);
	}
	data[gid] = (((int)(r[0] / p * 255) & 0xff) << 16) + (((int)(r[1] / p * 255) & 0xff) << 8) 
	+ (((int)(r[2] / p * 255) & 0xff));
}


__kernel void 		start(__global t_cl_object *obj,
							__global t_cl_light *light,
							__global int *out_data,
							__global int *i_mem,
							__global float *d_mem)
{
	
	int				gid;
	int				x;
	int				y;
	t_sdl			sdl;
	int				obj_ind;
	gid = get_global_id(0);

	sdl.W_WIDTH = i_mem[0];
	sdl.W_HEIGHT = i_mem[1];
	sdl.dital = i_mem[2];
	sdl.gloss_activ = i_mem[3];
	sdl.reflect_count = i_mem[4];
	sdl.o_count = i_mem[5];
	sdl.l_count = i_mem[6];
	sdl.cam.pos = (float3){d_mem[0], d_mem[1], d_mem[2]};
	sdl.ambient = d_mem[3];
	sdl.cam.rot = (float3){d_mem[4], d_mem[5], d_mem[6]};
	sdl.pref = i_mem[7];
	sdl.obj = obj;
	sdl.light = light;
	x = gid % sdl.W_WIDTH;
	y = gid / sdl.W_WIDTH;
	ft_tracing(x, y, &sdl, out_data, gid);
}