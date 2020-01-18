/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 15:32:59 by rsticks           #+#    #+#             */
/*   Updated: 2019/11/28 16:28:25 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_cl_object			*transform_obj_data(t_object *obj, int *count)
{
	t_cl_object		*cl_obj;
	t_object		*past_obj;

	past_obj = obj;
	*count = 0;
	while (obj)
	{
		(*count)++;
		obj = obj->next;
	}
	cl_obj = (t_cl_object*)malloc(sizeof(t_cl_object) * *count);
	*count = 0;
	obj = past_obj;
	while (obj)
	{
		cl_obj[*count].pos = (cl_float3){{obj->pos.x, obj->pos.y, obj->pos.z}};
		cl_obj[*count].rot = (cl_float3){{obj->rot.x, obj->rot.y, obj->rot.z}};
		cl_obj[*count].col = (cl_float3){{obj->col.r, obj->col.g, obj->col.b}};
		cl_obj[*count].r = obj->r;
		cl_obj[*count].name = obj->name;
		cl_obj[*count].specular = obj->specular;
		(*count)++;
		obj = obj->next;
	}
	return (cl_obj);
}

t_cl_light			*transform_light_data(t_light *light, int *count)
{
	t_cl_light		*cl_light;
	t_light			*p_light;

	p_light = light;
	*count = 0;
	while (light)
	{
		(*count)++;
		light = light->next;
	}
	cl_light = (t_cl_light*)malloc(sizeof(t_cl_light) * *count);
	*count = 0;
	while (p_light)
	{
		cl_light[*count].pos =
		(cl_float3){{p_light->pos.x, p_light->pos.y, p_light->pos.z}};
		cl_light[*count].inten = p_light->inten;
		cl_light[*count].col =
		(cl_float3){{p_light->col.r, p_light->col.g, p_light->col.b}};
		(*count)++;
		p_light = p_light->next;
	}
	return (cl_light);
}
