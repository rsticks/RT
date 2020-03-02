/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_mas.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 16:42:56 by daron             #+#    #+#             */
/*   Updated: 2020/03/02 14:55:12 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void delete_light_list(t_rt *rt)
{
	t_light *light;
	t_light *next_light;

	light = rt->lgh_head;
	while (light->next)
	{
		next_light = light->next;
		free(light);
		light = next_light;
	}
	free(light);
}

void copy_light(t_rt *rt)
{
	int i;
	t_light *light;

	light = rt->lgh_head;
	i = 0;
	while (i < rt->scene.lgh_c)
	{
		rt->lgh_mas[i].pos = (t_vector){light->pos.x, light->pos.y, light->pos.z};
		rt->lgh_mas[i].rgb = (t_rgb2){light->rgb.r, light->rgb.g, light->rgb.b};
		light = light->next;
		i++;
	}
}

void delete_obj_list(t_rt *rt)
{
	t_obj *obj;
	t_obj *next_obj;

	obj = rt->obj_head;
	while (obj->next)
	{
		next_obj = obj->next;
		free(obj);
		obj = next_obj;
	}
	free(obj);
}

void copy_obj(t_rt *rt)
{
	int i;
	t_obj *obj;

	obj = rt->obj_head;
	i = 0;
	while (i < rt->scene.obj_c)
	{
		rt->obj_mas[i].pos = (t_vector){obj->pos.x, obj->pos.y, obj->pos.z};
		rt->obj_mas[i].rgb = (t_rgb2){obj->rgb.r, obj->rgb.g, obj->rgb.b};
		rt->obj_mas[i].dir = (t_vector){obj->dir.x, obj->dir.y, obj->dir.z};
		rt->obj_mas[i].obj_name = obj->obj_name;
		rt->obj_mas[i].type = obj->type;
		rt->obj_mas[i].reflect = obj->reflect;
		rt->obj_mas[i].coef_refl = obj->coef_refl;
		rt->obj_mas[i].spec = obj->spec;
		rt->obj_mas[i].radius = obj->radius;
        rt->obj_mas[i].torus_r = obj->torus_r;
		rt->obj_mas[i].limit = obj->limit;
		rt->obj_mas[i].refr = obj->refr;
		rt->obj_mas[i].ind_refr = obj->ind_refr;
		rt->obj_mas[i].coef_refr = obj->coef_refr;
		rt->obj_mas[i].text_on = obj->text_on;
		rt->obj_mas[i].texture = obj->texture;
		rt->obj_mas[i].obj_on = obj->obj_on;
		rt->obj_mas[i].file_name = obj->file_name;
        rt->obj_mas[i].contruction_id = obj->contruction_id;
		obj = obj->next;
		i++;
	}

}

void list_to_mas(t_rt *rt)
{
	if (!(rt->obj_mas = (t_obj*)malloc(sizeof(t_obj) * rt->scene.obj_c)))
		kill_all("ERROR: malloc error <list_to_mas>");
	copy_obj(rt);
	delete_obj_list(rt);
	if (rt->scene.lgh_c > 0)
	{
		if (!(rt->lgh_mas = (t_light*)malloc(sizeof(t_light) * rt->scene.lgh_c)))
			kill_all("ERROR: malloc error <list_to_mas>");
		copy_light(rt);
		delete_light_list(rt);
	}
}