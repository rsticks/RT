/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 18:06:40 by daron             #+#    #+#             */
/*   Updated: 2020/03/06 13:46:27 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float			get_paraboloid_intersection(t_vector *ray_dir,
		t_vector *cam_pos, int i, t_rt *rt)
{
	float		b;
	float		c;
	float		a;
	float		discriminant;
	t_vector	oc;

	oc = vec_sub(cam_pos, &rt->obj_mas[i].pos);
	a = vec_dot(ray_dir, ray_dir)
		- pow(vec_dot(ray_dir, &rt->obj_mas[i].dir), 2);
	b = 2 * (vec_dot(ray_dir, &oc) - vec_dot(ray_dir, &rt->obj_mas[i].dir)
			* (vec_dot(&oc, &rt->obj_mas[i].dir) + 2 * rt->obj_mas[i].radius));
	c = vec_dot(&oc, &oc) - vec_dot(&oc, &rt->obj_mas[i].dir)
			* (vec_dot(&oc, &rt->obj_mas[i].dir) + 4 * rt->obj_mas[i].radius);
	discriminant = pow(b, 2) - 4 * a * c;
	if (discriminant < 0)
		return (-1);
	return (get_quadratic_solution(a, b, discriminant));
}

float			get_disk_intersection(t_vector *ray_dir, t_vector *cam_pos,
		int i, t_rt *rt)
{
	float		dist;
	t_vector	vec;
	t_vector	vec1;

	dist = ((vec_dot(&rt->obj_mas[i].dir, &rt->obj_mas[i].pos) -
			vec_dot(&rt->obj_mas[i].dir, cam_pos))
			/ vec_dot(&rt->obj_mas[i].dir, ray_dir));
	if (dist > EPS)
	{
		vec = vec_scale(ray_dir, dist);
		vec1 = vec_sum(cam_pos, &vec);
		vec = vec_sub(&vec1, &rt->obj_mas[i].pos);
		if (vec_len(&vec) <= rt->obj_mas[i].radius)
			return (dist);
	}
	return (-1);
}

float			get_cylinder_intersection(t_vector *ray_dir, t_vector *cam_pos,
									int i, t_rt *rt)
{
	double		b;
	double		c;
	double		a;
	double		discriminant;
	t_vector	oc;

	oc = vec_sub(cam_pos, &rt->obj_mas[i].pos);
	rt->obj_mas[i].dir = vec_norm(&rt->obj_mas[i].dir);
	a = vec_dot(ray_dir, ray_dir)
		- pow(vec_dot(ray_dir, &rt->obj_mas[i].dir), 2);
	b = 2 * (vec_dot(ray_dir, &oc) - (vec_dot(ray_dir, &rt->obj_mas[i].dir) *
			vec_dot(&oc, &rt->obj_mas[i].dir)));
	c = vec_dot(&oc, &oc) - pow(vec_dot(&oc, &rt->obj_mas[i].dir), 2)
		- pow(rt->obj_mas[i].radius, 2);
	discriminant = pow(b, 2) - 4 * a * c;
	if (discriminant < 0)
		return (-1);
	return (get_quadratic_solution(a, b, discriminant));
}
