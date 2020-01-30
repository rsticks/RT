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
# define OBJ_FILE_ID	5

/*
** Help
*/
# define EPS 0.0001

typedef struct				s_cl_object
{
	float3					pos;
	float3					rot;
	float3					col;
	float					r;
	int						name;
	int						specular;
	float					limit;
	int						reflect;
	float					coef_refl;
}							t_cl_object;

typedef	struct				s_cl_light
{
	float3					pos;
	float					inten;
	float3					col;
}							t_cl_light;

typedef	struct				s_ray
{
	float3					orig;
	float3					dir;
}							t_ray;

typedef	struct				s_cam
{
	float3					pos;
	float3					rot;
}							t_cam;

typedef	struct				s_win
{
	int						size[2];
	int 					anti_alias;
}							t_win;

typedef	struct				s_scene
{
	float					spec; // Уровень блестящести
	int						obj_c; // Количество считанных объектов
	int						lgh_c; // Количество источников света

	int						maxref;
	float					ambient;
}							t_scene;

typedef struct				s_rt
{
	t_scene					scene;
	t_win 					window;
	t_cam 					cam;

	__global t_cl_object	*obj;
	__global t_cl_light		*light;

	float3					ray_dir;
	float					t;
	float3 					dist;
	float3					norm;
	float3					refpos;
	float3					ref;
	int 					pref;
	int 					cpt;
}							t_rt;

void						ft_fzero(float *s, int n);
float						ft_clamp(float value, float min, float max);
float3						vec_sum(float3 v1, float3 v2);
float3						vec_sub(float3 v1, float3 v2);
float3						vec_scale(float3 v1, float factor);
float						vec_dot(float3 v1, float3 v2);
float						vec_len(float3 v1);
float3						vec_norm(float3 v1);
float3  					vec_cross(float3 v1, float3 v2);
float						get_quadratic_solution(float a, float b, float discriminant);
float 						get_sphere_intersection(float3 *ray_dir, float3 *cam_pos, int i, t_rt *rt);
float 						get_plane_intersection(float3 *ray_dir, float3 *cam_pos, int i, t_rt *rt);
float 						get_cone_intersection(float3 *ray_dir, float3 *cam_pos, int i, t_rt *rt);
float 						get_cylinder_intersection(float3 *ray_dir, float3 *cam_pos, int i, t_rt *rt);
int							intersection(t_rt *rt, float3 *ray_dir, float3 *cam_pos);
float3 						object_norm(t_rt *rt, int i, float3 pos);
int							shadow(t_rt *rt, int i_obj, int i_light, float3 pos);
void						transfer_light(int i_obj, int i_light, float *tab, float d, t_rt *rt);
void 						gloss(t_rt *rt, int i_obj, float *tab, float3 *dist, float d);
int 						ref_inter(t_rt *rt, int i_cur_obj , float3 pos);
int 						ref_init(t_rt *rt, int i_obj, float3 *pos);
int 						reflection(t_rt *rt, int i_obj, float3 *pos, float *tab);
void 						calculate_light(t_rt *rt, int i_obj, float *tab);
void						ft_average(float *r, float *tab);
void 						create_ray(t_rt *rt, float x, float y);
void 						ft_tracing(float x, float y, t_rt *rt, __global int *data, int gid);



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


float get_sphere_intersection(float3 *ray_dir, float3 *cam_pos, int i, t_rt *rt)
{
	float b;
	float c;
	float a;
	float discriminant;

	rt->dist = vec_sub(*cam_pos, rt->obj[i].pos);
	a = vec_dot(*ray_dir, *ray_dir);
	b = 2 * vec_dot(*ray_dir, rt->dist);
	c = vec_dot(rt->dist, rt->dist) - pow(rt->obj[i].r, 2);
	discriminant = pow(b, 2) - 4 * a * c;
	if (discriminant < 0)
		return (-1);
	return (get_quadratic_solution(a, b , discriminant));
}

float get_plane_intersection(float3 *ray_dir, float3 *cam_pos, int i, t_rt *rt)
{
	float dist;
	
	dist = ((vec_dot(rt->obj[i].rot, rt->obj[i].pos) - vec_dot(rt->obj[i].rot,
	*cam_pos)) / vec_dot(rt->obj[i].rot, *ray_dir));
	if (dist < EPS)
		return (-1);
	return (dist);
}

float get_cone_intersection(float3 *ray_dir, float3 *cam_pos, int i, t_rt *rt)
{
	float	b;
	float	c;
	float	a;
	float discriminant;

	rt->dist = vec_sub(*cam_pos, rt->obj[i].pos);
	rt->obj[i].rot = vec_norm(rt->obj[i].rot);
	a = vec_dot(*ray_dir, *ray_dir) - (1 + pow(tan(rt->obj[i].r), 2))
	* pow(vec_dot(*ray_dir, rt->obj[i].rot), 2);
	b = 2 * (vec_dot(*ray_dir, rt->dist) - (1 + pow(tan(rt->obj[i].r), 2))
	* vec_dot(*ray_dir, rt->obj[i].rot) * vec_dot(rt->dist, rt->obj[i].rot));
	c = vec_dot(rt->dist, rt->dist) - (1 + pow(tan(rt->obj[i].r), 2))
	* pow(vec_dot(rt->dist, rt->obj[i].rot), 2);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1);
	return (get_quadratic_solution(a, b, discriminant));
}

float get_cylinder_intersection(float3 *ray_dir, float3 *cam_pos, int i, t_rt *rt)
{
	float b;
	float c;
	float a;
	float discriminant;

	rt->dist = vec_sub(*cam_pos, rt->obj[i].pos);
	rt->obj[i].rot = vec_norm(rt->obj[i].rot);
	a = vec_dot(*ray_dir, *ray_dir) - pow(vec_dot(*ray_dir, rt->obj[i].rot), 2);
	b = 2 * (vec_dot(*ray_dir, rt->dist) - (vec_dot(*ray_dir, rt->obj[i].rot)
	* vec_dot(rt->dist, rt->obj[i].rot)));
	c = vec_dot(rt->dist, rt->dist) - pow(vec_dot(rt->dist, rt->obj[i].rot), 2)
	- pow(rt->obj[i].r, 2);
	discriminant = pow(b, 2) - 4 * a * c;
	if (discriminant < 0)
		return (-1);
	return (get_quadratic_solution(a, b, discriminant));
}

int			intersection(t_rt *rt, float3 *ray_dir, float3 *cam_pos)
{
	float dist;
	int i;
	int f;

	i = 0;
	f = -1;
	rt->t = 90000.0;
	dist = 0.01;
	while (i < rt->scene.obj_c)
	{
		if (rt->obj[i].name == SPHERE_ID)
			dist = get_sphere_intersection(ray_dir, cam_pos, i, rt);
		else if (rt->obj[i].name == CYLINDER_ID)
			dist = get_cylinder_intersection(ray_dir, cam_pos, i, rt);
		else if (rt->obj[i].name == CONE_ID)
			dist = get_cone_intersection(ray_dir, cam_pos, i, rt);
		else if (rt->obj[i].name == PLANE_ID)
			dist = get_plane_intersection(ray_dir, cam_pos, i, rt);
		if (dist > EPS && dist < rt->t)
		{
			f = i;
			rt->t = dist;
		}
		i++;
	}
	return (f);
}


float3 object_norm(t_rt *rt, int i, float3 pos)
{
	float3 norm;
	float3 tmp;
	float3 tmp2;

	if (rt->obj[i].name == CONE_ID || rt->obj[i].name == CYLINDER_ID)
	{
		tmp = vec_scale(rt->obj[i].rot, (vec_dot(rt->ray_dir, rt->obj[i].rot) * rt->t
		+ vec_dot(rt->dist, rt->obj[i].rot)));
		if (rt->obj[i].name == CONE_ID)
			tmp = vec_scale(tmp, (1 + pow(tan(rt->obj[i].r), 2)));
		tmp2 = vec_sub(pos, rt->obj[i].pos);
		norm = vec_sub(tmp2, tmp);
	}
	else if (rt->obj[i].name == PLANE_ID)
		norm = rt->obj[i].rot;
	else if (rt->obj[i].name == SPHERE_ID)
		norm = vec_sub(pos, rt->obj[i].pos);
	return (vec_norm(norm));
}


void	transfer_light(int i_obj, int i_light, float *tab, float d, t_rt *rt)
{
	tab[3] = ft_clamp(tab[3] * 4.0 * d, 0.0, 1.0);
	tab[0] += tab[3] * (rt->obj[i_obj].col.x / 255) * (rt->light[i_light].col.x / 255);
	tab[1] += tab[3] * (rt->obj[i_obj].col.y / 255) * (rt->light[i_light].col.y / 255);
	tab[2] += tab[3] * (rt->obj[i_obj].col.z / 255) * (rt->light[i_light].col.z / 255);
}

int		shadow(t_rt *rt, int i_obj, int i_light, float3 pos)
{
	float3	dist;
	float 	d;
	int 	i;

	
	i = 0;
	dist = vec_sub(rt->light[i_light].pos, pos);
	rt->t = native_sqrt(vec_dot(dist, dist));
	dist = vec_norm(dist);
	while (i < rt->scene.obj_c)
	{
		if (i != i_obj)
		{
			if (rt->obj[i].name == SPHERE_ID)
				d = get_sphere_intersection(&dist, &pos, i, rt);
			else if (rt->obj[i].name == CYLINDER_ID)
				d = get_cylinder_intersection(&dist, &pos, i, rt);
			else if (rt->obj[i].name == CONE_ID)
				d = get_cone_intersection(&dist, &pos, i, rt);
			else if (rt->obj[i].name == PLANE_ID)
				d = get_plane_intersection(&dist, &pos, i, rt);
			if (d > EPS && d < rt->t)
				return (1);
		}
		i++;
	}
	return (0);
}

void gloss(t_rt *rt, int i_obj, float *tab, float3 *dist, float d)
{
	float	spec;
	float	tmp;
	float3	ref;

	if (rt->obj[i_obj].name != PLANE_ID && rt->obj[i_obj].specular == 1)
	{
		spec = 0.0;
		ref = vec_scale(rt->norm, (2.0 * vec_dot(rt->norm, *dist)));
		ref = vec_sub(*dist, ref);
		tmp = vec_dot(ref, rt->ray_dir);
		if (tmp > 0.0 && tab[3] > rt->scene.ambient)
		{
			spec = native_powr(tmp, 200) * 4 * d;
			spec = ft_clamp(spec, 0.0, 1.0);
		}
		tab[1] += spec;
		tab[2] += spec;
		tab[3] += spec;
	}
}


int ref_inter(t_rt *rt, int i_cur_obj , float3 pos)
{
	double	dist;
	int i;
	char f;

	i = 0;
	f = -1;
	while (i < rt->scene.obj_c)
	{
		if (i_cur_obj != i)
		{
			if (rt->obj[i].name == SPHERE_ID)
				dist = get_sphere_intersection(&rt->ref, &pos, i, rt);
			else if (rt->obj[i].name == CYLINDER_ID)
				dist = get_cylinder_intersection(&rt->ref, &pos, i, rt);
			else if (rt->obj[i].name == CONE_ID)
				dist = get_cone_intersection(&rt->ref, &pos, i, rt);
			else if (rt->obj[i].name == PLANE_ID)
				dist = get_plane_intersection(&rt->ref, &pos, i, rt);
			if (dist > EPS && dist < rt->t)
			{
				f = i;
				rt->t = dist;
			}
		}
		i++;
	}
	return (f);
}

int ref_init(t_rt *rt, int i_obj, float3 *pos)
{
	int	tmp2;

	rt->t = 8000.0;
	rt->ref = vec_scale(rt->norm, (2 * vec_dot(rt->refpos, rt->norm)));
	rt->ref = vec_sub(rt->refpos, rt->ref);
	rt->ref = vec_norm(rt->ref);
	tmp2 = ref_inter(rt, i_obj, *pos);
	if (tmp2 == -1)
		return (-1);
	*pos = (float3){pos->x + rt->t * rt->ref.x,
				   pos->y + rt->t * rt->ref.y,
				   pos->z + rt->t * rt->ref.z};
	rt->refpos = (float3){rt->ref.x, rt->ref.y, rt->ref.z};
	rt->norm = object_norm(rt, tmp2, *pos);
	return (tmp2);
}

int reflection(t_rt *rt, int i_obj, float3 *pos, float *tab)
{
	int i_light;
	float3	dist;
	float	d;
	int tmp2;

	while (rt->obj[i_obj].reflect && rt->cpt < rt->scene.maxref && (tmp2 = ref_init(rt, i_obj, pos)) != -1)
	{
		rt->cpt++;
		i_light = 0;
		while (i_light < rt->scene.lgh_c)
		{
			tab[3] = rt->scene.ambient;
			dist = vec_sub(rt->light[i_light].pos, *pos);
			d = ft_clamp(1.0 / native_sqrt(native_sqrt(vec_dot(dist, dist))), 0.0, 1.0);
			dist = vec_norm(dist);
			if (shadow(rt, tmp2, i_light, *pos) == 0)
				tab[3] += ft_clamp(vec_dot(dist, rt->norm), 0.0, 1.0);
			transfer_light(tmp2, i_light, tab, d, rt);
			//gloss(rt, i_obj, tab, &dist , d);
			i_light++;
		}
	}
	return (0);
}


void 	calculate_light(t_rt *rt, int i_obj, float *tab)
{
	float3 pos;
	float3 dist;
	float d;
	int ind;

	ind = 0;
	pos = (float3){rt->cam.pos.x + rt->t * rt->ray_dir.x,
				  rt->cam.pos.y + rt->t * rt->ray_dir.y,
				  rt->cam.pos.z + rt->t * rt->ray_dir.z};
	rt->norm = object_norm(rt, i_obj, pos);

	//printf("pos = (%g %g %g)\n", pos.x, pos.y, pos.z);
	while (ind < rt->scene.lgh_c)
	{
		tab[3] = rt->scene.ambient;
		//printf("ambient = (%g)\n", rt->scene.ambient);
		dist = vec_sub(rt->light[ind].pos, pos);
		//printf("dist = (%g %g %g)\n", dist.x, dist.y, dist.z);
		d = ft_clamp((1.0 / native_sqrt(native_sqrt(vec_dot(dist, dist)))), 0.0, 1.0);
		//printf("d = %g\n", d);
		dist = vec_norm(dist);
		//printf("dist = (%g %g %g)\n", dist.x, dist.y, dist.z);
		if (shadow(rt, i_obj, ind, pos) == 0)
			tab[3] += ft_clamp(vec_dot(dist, rt->norm), 0.0, 1.0);
		transfer_light(i_obj, ind, tab, d, rt);
		gloss(rt, i_obj, tab, &dist , d);
		ind++;
	}
	rt->refpos = (float3){rt->ray_dir.x, rt->ray_dir.y, rt->ray_dir.z};
	reflection(rt, i_obj, &pos, tab);
}


void	ft_average(float *r, float *tab)
{
	r[0] += ft_clamp(tab[0], 0.0, 1.0);
	r[1] += ft_clamp(tab[1], 0.0, 1.0);
	r[2] += ft_clamp(tab[2], 0.0, 1.0);
}

void create_ray(t_rt *rt, float x, float y)
{
	float u, v;
	float3 i, j, k;

	u = (rt->window.size[0] - (float)x * 2.0) / rt->window.size[1];
	v = (rt->window.size[1] - (float)y * 2.0) / rt->window.size[0];
	k = vec_sub(rt->cam.rot, rt->cam.pos);
	k = vec_norm(k);
	i = vec_cross(k, (float3){0.0, 1.0, 0.0});
	i = vec_norm(i);
	j = vec_cross(i, k);
	rt->ray_dir = (float3){u * i.x + v * j.x + FOV * k.x, u * i.y + v * j.y + FOV * k.y, u * i.z + v * j.z + FOV * k.z};
	rt->ray_dir = vec_norm(rt->ray_dir);
	rt->cpt = 0;
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

void ft_tracing(float x, float y, t_rt *rt, __global int *data, int gid)
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
			create_ray(rt, x, y);
			ft_fzero(tab, 4);
			i = intersection(rt, &rt->ray_dir, &rt->cam.pos);
			//printf("x, y = %d, %d object = %d\n", (int)x, (int)y, i);
			if(i >= 0)
				calculate_light(rt, i, tab);
			ft_average(r, tab);
			x = x + (1.0 / rt->window.anti_alias);
		}
		y = y + (1.0 / rt->window.anti_alias);
	}
	//printf("%g, %g, %g\n", r[0], r[1], r[2]);
	data[gid] = (((int)(r[0] / p * 255) & 0xff) << 16) + (((int)(r[1] / p * 255) & 0xff) << 8) + (((int)(r[2] / p * 255) & 0xff));
}


__kernel void 		start(__global t_cl_object *obj,
							__global t_cl_light *light,
							__global int *out_data,
							__global int *i_mem,
							__global float *d_mem)
{
	int				gid, x, y;
	t_rt			rt;

	gid = get_global_id(0);

	rt.window.size[0] = i_mem[0];
	rt.window.size[1] = i_mem[1];
	rt.window.anti_alias = i_mem[2];
	rt.scene.obj_c = i_mem[3];
	rt.scene.lgh_c = i_mem[4];
	rt.scene.maxref = i_mem[5];

	rt.cam.pos = (float3){d_mem[0], d_mem[1], d_mem[2]};
	rt.scene.ambient = d_mem[3];
	rt.cam.rot = (float3){d_mem[4], d_mem[5], d_mem[6]};

	rt.obj = obj;
	rt.light = light;

	/*if (gid == 1)
	{
		printf("In Kernel - W_size = (%d %d) Antialias = %d obj_c = %d light_c = %d\n"
				"cam_pos = (%g, %g, %g) cam_rot = (%g, %g, %g) ambient= %g\n\n",
				rt.window.size[0], rt.window.size[1],
				rt.window.anti_alias, rt.scene.obj_c, rt.scene.lgh_c,
				rt.cam.pos.x,rt.cam.pos.y, rt.cam.pos.z,
				rt.cam.rot.x, rt.cam.rot.y, rt.cam.rot.z, rt.scene.ambient);

		int i ;
		i = -1;
		while (++i < rt.scene.obj_c)
			printf("In Kernel Object type = %d\n pos = (%g, %g, %g)\n rot = (%g, %g, %g)\n color = (%g, %g, %g)\n radius = %g\nreflect = %d coef = %g\n",
				rt.obj[i].name,
				rt.obj[i].pos.x, rt.obj[i].pos.y, rt.obj[i].pos.z,
				rt.obj[i].rot.x, rt.obj[i].rot.y, rt.obj[i].rot.z,
				rt.obj[i].col.x, rt.obj[i].col.y, rt.obj[i].col.z,
				rt.obj[i].r,
				rt.obj[i].reflect, rt.obj[i].coef_refl);
		i = -1;
		while (++i < rt.scene.lgh_c)
			printf("In Kernel Light pos = (%g, %g, %g)\n color = (%g, %g, %g)\n\n",
				rt.light[i].pos.x, rt.light[i].pos.y, rt.light[i].pos.z,
				rt.light[i].col.x, rt.light[i].col.y, rt.light[i].col.z);

	}*/
	x = gid % rt.window.size[0];
	y = gid / rt.window.size[1];
	ft_tracing(x, y, &rt, out_data, gid);
}