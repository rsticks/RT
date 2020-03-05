/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cheker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 15:47:14 by daron             #+#    #+#             */
/*   Updated: 2020/03/05 17:06:48 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		cheak_camera(t_rt *rt)
{
	if (rt->cam.check[0] == 0)
		kill_all("ERROR: You must set the camera position");
	else if (rt->cam.check[1] == 0)
		kill_all("ERROR: You must set the camera direction");
}

void		cheak_light(t_rt *rt)
{
	t_light	*light;

	light = rt->lgh_head;
	while (light)
	{
		if (light->check[0] == 0)
			kill_all("ERROR: You must set the light position");
		light = light->next;
	}
}

void		cheak_scene(t_rt *rt)
{
	if (rt->window.check[1] == 0)
		kill_all("ERROR: You must set the size of the program window");
	else if (rt->window.check[4] == 0)
		kill_all("ERROR: You must set the ambient level");
	else if (rt->window.check[0] == 0)
		kill_all("ERROR: You must set the scene name");
}

static void	cheak_object_1(t_obj *obj)
{
	if (obj->check[0] == 0)
		kill_all("ERROR: You must set the object type");
	else if (obj->check[1] == 0 && obj->type != OBJ_FILE_ID)
		kill_all("ERROR: You must set the object position");
	else if (obj->check[2] == 0 && obj->type != SPHERE_ID
			&& obj->type != OBJ_FILE_ID)
		kill_all("ERROR: You must set the object direction");
	else if (obj->check[5] == 0 && obj->type != OBJ_FILE_ID)
		kill_all("ERROR: You must set the reflection level");
	else if (obj->check[6] == 0 && obj->type != OBJ_FILE_ID)
		kill_all("ERROR: You must set the rafraction level");
	else if (obj->check[3] == 0 && obj->type != OBJ_FILE_ID)
		kill_all("ERROR: You must set the object color");
	else if (obj->check[4] == 0 && (obj->type == DISK_ID ||
		obj->type == SPHERE_ID || obj->type == TORUS_ID ||
		obj->type == PARABOLOID_ID) && obj->type != OBJ_FILE_ID)
		kill_all("ERROR: You must set the sphere radius");
	else if (obj->check[11] == 0 && obj->type == TORUS_ID
			&& obj->type != OBJ_FILE_ID)
		kill_all("ERROR: You must set the torus main radius");
}

void		cheak_object(t_rt *rt)
{
	t_obj	*obj;

	obj = rt->obj_head;
	while (obj)
	{
		cheak_object_1(obj);
		obj = obj->next;
	}
}
