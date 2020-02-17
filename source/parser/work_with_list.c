/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 18:22:13 by daron             #+#    #+#             */
/*   Updated: 2020/02/11 13:15:09 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void create_light_list(t_rt *rt)
{
	t_light *ptr;
	t_light *new;

	if (!(new = (t_light*)malloc(sizeof(t_light))))
		kill_all("ERROR: Can't create list for light <create_light_list>");
	ft_memset(new->check, 0, 2);
	new->next = NULL;
	if (rt->lgh_head == NULL)
		rt->lgh_head = new;
	else
	{
		ptr = rt->lgh_head;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;

	}
	rt->scene.lgh_c++;
	rt->lgh_cur = new;
}

static void initialize_object(t_obj *obj)
{
	obj->type = 0;

	obj->pos = (t_vector){0.0, 0.0, 0.0};
	obj->dir = (t_vector){0.0, 0.0, 0.0};
	obj->rgb = (t_rgb2){0, 0, 0};

	obj->reflect = 0;
	obj->coef_refl = 0.0;
	obj->spec = 0;
	obj->limit = 0;
	obj->refr = 0;
	obj->ind_refr = 0.0;
	obj->coef_refr = 0.0;

	obj->radius = 0;

	obj->obj_on = 0;
	obj->obj_name = NULL;

	obj->text_on = 0;
	obj->texture = NULL;

	obj->obj_on = 0;
	obj->file_name = NULL;

	ft_memset(obj->check, 0, 10);

}

static void create_obj_list(t_rt *rt)
{
	t_obj *ptr;
	t_obj *new;

	if (!(new = (t_obj*)malloc(sizeof(t_obj))))
		kill_all("ERROR: Can't create list for object <create_light_list>");
	initialize_object(new);
	new->next = NULL;
	if (rt->obj_head == NULL)
		rt->obj_head = new;
	else
	{
		ptr = rt->obj_head;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;

	}
	rt->scene.obj_c++;
	rt->obj_cur = new;
}

void create_list(t_rt *rt, char *type)
{
	if (ft_strequ(type, "light") == 1)
		create_light_list(rt);
	else if (ft_strequ(type, "object") == 1)
		create_obj_list(rt);
}