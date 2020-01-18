/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 15:00:42 by rsticks           #+#    #+#             */
/*   Updated: 2019/11/28 16:27:56 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static double	get_cone_intersection(t_vector *ray_dir, t_vector *cam_pos,
		t_object *obj)
{
	double		b;
	double		c;
	double		a;
	double		discriminant;
	t_vector	oc;

	oc = vec_sub(cam_pos, &obj->pos);
	obj->rot = vec_norm(&obj->rot);
	a = vec_dot(ray_dir, ray_dir) - (1 + pow(tan(obj->r), 2)) *
			pow(vec_dot(ray_dir, &obj->rot), 2);
	b = 2 * (vec_dot(ray_dir, &oc) - (1 + pow(tan(obj->r), 2)) *
			vec_dot(ray_dir, &obj->rot) * vec_dot(&oc, &obj->rot));
	c = vec_dot(&oc, &oc) - (1 + pow(tan(obj->r), 2)) *
			pow(vec_dot(&oc, &obj->rot), 2);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1);
	return (get_quadratic_solution(a, b, discriminant));
}

static double	get_plane_intersection(t_vector *ray_dir, t_vector *cam_pos,
		t_object *obj)
{
	float		dist;

	dist = ((vec_dot(&obj->rot, &obj->pos) - vec_dot(&obj->rot, cam_pos)) /
			vec_dot(&obj->rot, ray_dir));
	if (dist < EPS)
		return (-1);
	return (dist);
}

static double	get_sphere_intersection(t_vector *ray_dir, t_vector *cam_pos,
		t_object *obj)
{
	double		b;
	double		c;
	double		a;
	double		discriminant;
	t_vector	oc;

	oc = vec_sub(cam_pos, &obj->pos);
	a = vec_dot(ray_dir, ray_dir);
	b = 2 * vec_dot(ray_dir, &oc);
	c = vec_dot(&oc, &oc) - pow(obj->r, 2);
	discriminant = pow(b, 2) - 4 * a * c;
	if (discriminant < 0)
		return (-1);
	return (get_quadratic_solution(a, b, discriminant));
}

static double	get_cylinder_intersection(t_vector *ray_dir, t_vector *cam_pos,
		t_object *obj)
{
	double		b;
	double		c;
	double		a;
	double		discriminant;
	t_vector	oc;

	oc = vec_sub(cam_pos, &obj->pos);
	obj->rot = vec_norm(&obj->rot);
	a = vec_dot(ray_dir, ray_dir) - pow(vec_dot(ray_dir, &obj->rot), 2);
	b = 2 * (vec_dot(ray_dir, &oc) - (vec_dot(ray_dir, &obj->rot) *
			vec_dot(&oc, &obj->rot)));
	c = vec_dot(&oc, &oc) - pow(vec_dot(&oc, &obj->rot), 2) - pow(obj->r, 2);
	discriminant = pow(b, 2) - 4 * a * c;
	if (discriminant < 0)
		return (-1);
	return (get_quadratic_solution(a, b, discriminant));
}

t_object		*intersection(t_sdl *sdl, t_vector *ray_dir, t_vector *cam_pos)
{
	t_object	*obj;
	float		dist;
	t_object	*head;
	float		t;

	obj = NULL;
	head = sdl->obj;
	t = 90000.0;
	while (head != NULL)
	{
		if (head->name == SPHERE_ID)
			dist = get_sphere_intersection(ray_dir, cam_pos, head);
		else if (head->name == CYLINDER_ID)
			dist = get_cylinder_intersection(ray_dir, cam_pos, head);
		else if (head->name == CONE_ID)
			dist = get_cone_intersection(ray_dir, cam_pos, head);
		else if (head->name == PLANE_ID)
			dist = get_plane_intersection(ray_dir, cam_pos, head);
		if (dist > EPS && dist < t && (t = dist) > -1)
			obj = head;
		head = head->next;
	}
	return (obj);
}
