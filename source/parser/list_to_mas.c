/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_mas.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 16:42:56 by daron             #+#    #+#             */
/*   Updated: 2020/03/02 15:17:38 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		delete_light_list(t_rt *rt)
{
	t_light	*light;
	t_light	*next_light;

	light = rt->lgh_head;
	while (light->next)
	{
		next_light = light->next;
		free(light);
		light = next_light;
	}
	free(light);
}

void		copy_light(t_rt *rt)
{
	int		i;
	t_light	*light;

	light = rt->lgh_head;
	i = 0;
	while (i < rt->scene.lgh_c)
	{
		rt->lgh_mas[i].pos = (t_vector){light->pos.x, light->pos.y,
								light->pos.z};
		rt->lgh_mas[i].rgb = (t_rgb2){light->rgb.r, light->rgb.g,
								light->rgb.b};
		light = light->next;
		i++;
	}
}

void		delete_obj_list(t_rt *rt)
{
	t_obj	*obj;
	t_obj	*next_obj;

	obj = rt->obj_head;
	while (obj->next)
	{
		next_obj = obj->next;
		free(obj);
		obj = next_obj;
	}
	free(obj);
}

static void	data_transfer(t_obj *obj_mas, t_obj *obj)
{
	obj_mas->pos = (t_vector){obj->pos.x, obj->pos.y, obj->pos.z};
	obj_mas->rgb = (t_rgb2){obj->rgb.r, obj->rgb.g, obj->rgb.b};
	obj_mas->dir = (t_vector){obj->dir.x, obj->dir.y, obj->dir.z};
	obj_mas->obj_name = obj->obj_name;
	obj_mas->type = obj->type;
	obj_mas->reflect = obj->reflect;
	obj_mas->coef_refl = obj->coef_refl;
	obj_mas->spec = obj->spec;
	obj_mas->radius = obj->radius;
	obj_mas->torus_r = obj->torus_r;
	obj_mas->limit = obj->limit;
	obj_mas->refr = obj->refr;
	obj_mas->ind_refr = obj->ind_refr;
	obj_mas->coef_refr = obj->coef_refr;
	obj_mas->text_on = obj->text_on;
	obj_mas->texture = obj->texture;
	obj_mas->obj_on = obj->obj_on;
	obj_mas->file_name = obj->file_name;
	obj_mas->contruction_id = obj->contruction_id;
}

void		copy_obj(t_rt *rt)
{
	int		i;
	t_obj	*obj;

	obj = rt->obj_head;
	i = 0;
	while (i < rt->scene.obj_c)
	{
		data_transfer(&rt->obj_mas[i], obj);
		obj = obj->next;
		i++;
	}
}
