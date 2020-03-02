/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 15:32:59 by rsticks           #+#    #+#             */
/*   Updated: 2020/03/02 17:00:37 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		data_transfer(t_obj *obj_mas, t_cl_object *cl_obj)
{
	cl_obj->pos = (cl_float3){{obj_mas->pos.x, obj_mas->pos.y, obj_mas->pos.z}};
	cl_obj->rot = (cl_float3){{obj_mas->dir.x, obj_mas->dir.y, obj_mas->dir.z}};
	cl_obj->col = (cl_float3){{obj_mas->rgb.r, obj_mas->rgb.g, obj_mas->rgb.b}};
	cl_obj->r = obj_mas->radius;
	cl_obj->name = obj_mas->type;
	cl_obj->specular = obj_mas->spec;
	cl_obj->coef_refl = obj_mas->coef_refl;
	cl_obj->limit = obj_mas->limit;
	cl_obj->reflect = obj_mas->reflect;
	cl_obj->coef_refl = obj_mas->coef_refl;
	cl_obj->refr = obj_mas->refr;
	cl_obj->ind_refr = obj_mas->ind_refr;
	cl_obj->coef_refr = obj_mas->coef_refr;
	cl_obj->torus_r = obj_mas->torus_r;
	cl_obj->torus_r = obj_mas->torus_r;
}

t_cl_object		*transform_obj_data(t_rt *rt)
{
	t_cl_object	*cl_obj;
	int			i;

	if (!(cl_obj = (t_cl_object*)malloc(sizeof(t_cl_object)
			* rt->scene.obj_c)))
		kill_all("ERROR:Can't allocate memory for cl_obj <transform_obj_data>");
	i = 0;
	while (i < rt->scene.obj_c)
	{
		data_transfer(&rt->obj_mas[i], &cl_obj[i]);
		i++;
	}
	return (cl_obj);
}

t_cl_light		*transform_light_data(t_rt *rt)
{
	t_cl_light	*cl_light;
	int			i;

	if (!(cl_light = (t_cl_light*)malloc(sizeof(t_cl_light) * rt->scene.lgh_c)))
		kill_all("ERROR: Can't allocate memory for <transform_light_data>");
	i = 0;
	while (i < rt->scene.lgh_c)
	{
		cl_light[i].pos = (cl_float3){{rt->lgh_mas[i].pos.x,
								rt->lgh_mas[i].pos.y, rt->lgh_mas[i].pos.z}};
		cl_light[i].col = (cl_float3){{rt->lgh_mas[i].rgb.r,
								rt->lgh_mas[i].rgb.g, rt->lgh_mas[i].rgb.b}};
		cl_light[i].inten = 20;
		i++;
	}
	return (cl_light);
}
