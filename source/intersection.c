/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 15:00:42 by rsticks           #+#    #+#             */
/*   Updated: 2020/02/11 13:15:09 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static double	get_cone_intersection(t_vector *ray_dir, t_vector *cam_pos,
		int i, t_rt *rt)
{
	double		b;
	double		c;
	double		a;
	double		discriminant;
	t_vector	oc;

	oc = vec_sub(cam_pos, &rt->obj_mas[i].pos);
	rt->obj_mas[i].dir = vec_norm(&rt->obj_mas[i].dir);
	a = vec_dot(ray_dir, ray_dir) - (1 + pow(tan(rt->obj_mas[i].radius), 2)) *
			pow(vec_dot(ray_dir, &rt->obj_mas[i].dir), 2);
	b = 2 * (vec_dot(ray_dir, &oc) - (1 + pow(tan(rt->obj_mas[i].radius), 2)) *
			vec_dot(ray_dir, &rt->obj_mas[i].dir) * vec_dot(&oc, &rt->obj_mas[i].dir));
	c = vec_dot(&oc, &oc) - (1 + pow(tan(rt->obj_mas[i].radius), 2)) *
			pow(vec_dot(&oc, &rt->obj_mas[i].dir), 2);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1);
	return (get_quadratic_solution(a, b, discriminant));
}

static double	get_plane_intersection(t_vector *ray_dir, t_vector *cam_pos,
		int i, t_rt *rt)
{
	float		dist;

	dist = ((vec_dot(&rt->obj_mas[i].dir, &rt->obj_mas[i].pos) - vec_dot(&rt->obj_mas[i].dir, cam_pos)) /
			vec_dot(&rt->obj_mas[i].dir, ray_dir));
	if (dist < EPS)
		return (-1);
	return (dist);
}

static double	get_sphere_intersection(t_vector *ray_dir, t_vector *cam_pos,
		int i, t_rt *rt)
{
	double		b;
	double		c;
	double		a;
	double		discriminant;
	t_vector	oc;

	oc = vec_sub(cam_pos, &rt->obj_mas[i].pos);
	a = vec_dot(ray_dir, ray_dir);
	b = 2 * vec_dot(ray_dir, &oc);
	c = vec_dot(&oc, &oc) - pow(rt->obj_mas[i].radius, 2);
	discriminant = pow(b, 2) - 4 * a * c;
	if (discriminant < 0)
		return (-1);
	return (get_quadratic_solution(a, b, discriminant));
}

static double	get_cylinder_intersection(t_vector *ray_dir, t_vector *cam_pos,
		int i, t_rt *rt)
{
	double		b;
	double		c;
	double		a;
	double		discriminant;
	t_vector	oc;

	oc = vec_sub(cam_pos, &rt->obj_mas[i].pos);
	rt->obj_mas[i].dir = vec_norm(&rt->obj_mas[i].dir);
	a = vec_dot(ray_dir, ray_dir) - pow(vec_dot(ray_dir, &rt->obj_mas[i].dir), 2);
	b = 2 * (vec_dot(ray_dir, &oc) - (vec_dot(ray_dir, &rt->obj_mas[i].dir) *
			vec_dot(&oc, &rt->obj_mas[i].dir)));
	c = vec_dot(&oc, &oc) - pow(vec_dot(&oc, &rt->obj_mas[i].dir), 2) - pow(rt->obj_mas[i].radius, 2);
	discriminant = pow(b, 2) - 4 * a * c;
	if (discriminant < 0)
		return (-1);
	return (get_quadratic_solution(a, b, discriminant));
}

float get_paraboloid_intersection(t_vector *ray_dir, t_vector *cam_pos,
								  int i, t_rt *rt)
{
	float b;
	float c;
	float a;
	float discriminant;
	t_vector	oc;

	oc = vec_sub(cam_pos, &rt->obj_mas[i].pos);
	a = vec_dot(ray_dir, ray_dir) - pow(vec_dot(ray_dir, &rt->obj_mas[i].dir), 2);
	b = 2 * (vec_dot(ray_dir, &oc) - vec_dot(ray_dir, &rt->obj_mas[i].dir) * (vec_dot(&oc, &rt->obj_mas[i].dir) + 2 * rt->obj_mas[i].radius));
	c = vec_dot(&oc, &oc) - vec_dot(&oc, &rt->obj_mas[i].dir) * (vec_dot(&oc, &rt->obj_mas[i].dir) + 4 * rt->obj_mas[i].radius);
	discriminant = pow(b, 2) - 4 * a * c;
	if (discriminant < 0)
		return (-1);
	return (get_quadratic_solution(a, b , discriminant));
}

float get_disk_intersection(t_vector *ray_dir, t_vector *cam_pos,
							int i, t_rt *rt)
{
	float dist;
	t_vector new_ray;
	t_vector cam_ray;
	t_vector radius_ray;

	dist = ((vec_dot(&rt->obj_mas[i].dir, &rt->obj_mas[i].pos) - vec_dot(&rt->obj_mas[i].dir, cam_pos)) / vec_dot(&rt->obj_mas[i].dir, ray_dir));
	new_ray = vec_scale(ray_dir, dist);
	cam_ray = vec_sum(cam_pos, &new_ray);
	radius_ray = vec_sub(&cam_ray, &rt->obj_mas[i].pos);
	if (dist > EPS  && vec_len(&radius_ray) <= rt->obj_mas[i].radius)
		return dist;
	else
		return (-1);
}

int		intersection(t_rt *rt, t_vector *ray_dir, t_vector *cam_pos)
{
	int			obj;
	float		dist;
	float		t;
	int			i;

	obj = -1;
	t = 90000.0;
	i = 0;
	while (i < rt->scene.obj_c)
	{
		if (rt->obj_mas[i].type == SPHERE_ID)
			dist = get_sphere_intersection(ray_dir, cam_pos, i, rt);
		else if (rt->obj_mas[i].type == CYLINDER_ID)
			dist = get_cylinder_intersection(ray_dir, cam_pos, i, rt);
		else if (rt->obj_mas[i].type == CONE_ID)
			dist = get_cone_intersection(ray_dir, cam_pos, i, rt);
		else if (rt->obj_mas[i].type == PLANE_ID)
			dist = get_plane_intersection(ray_dir, cam_pos, i, rt);
		else if (rt->obj_mas[i].type == PARABOLOID_ID)
			dist = get_paraboloid_intersection(ray_dir, cam_pos, i, rt);
		else if (rt->obj_mas[i].type == DISK_ID)
			dist = get_disk_intersection(ray_dir, cam_pos, i, rt);
		//printf("dist = %g\n", dist);
		if (dist > EPS && dist < t && (t = dist) > -1)
			obj = i;
		i++;
	}
	return (obj);
}
