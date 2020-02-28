/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cheker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 15:47:14 by daron             #+#    #+#             */
/*   Updated: 2020/02/28 12:50:39 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void cheak_camera(t_rt *rt)
{
	if (rt->cam.check[0] == 0)
		kill_all("ERROR: You must set the camera position");
	else if (rt->cam.check[1] == 0)
		kill_all("ERROR: You must set the camera direction");
}

void cheak_light(t_rt *rt)
{
	t_light *light;

	light = rt->lgh_head;
	while (light)
	{
		if (light->check[0] == 0)
			kill_all("ERROR: You must set the light position");
		light = light->next;
	}
}

void cheak_scene(t_rt *rt)
{
	if (rt->window.check[1] == 0)
		kill_all("ERROR: You must set the size of the program window");
	else if (rt->window.check[4] == 0)
		kill_all("ERROR: You must set the ambient level");
	else if (rt->window.check[0] == 0)
        kill_all("ERROR: You must set the scene name");
}

void cheak_object(t_rt *rt)
{
	t_obj *obj;

	obj = rt->obj_head;
	printf("obj->check[1] = %d, obj->type = %d\n", obj->check[1], obj->type);
	while (obj)
	{
		if (obj->check[0] == 0)
			kill_all("ERROR: You must set the object type");
		else if (obj->check[1] == 0)
			kill_all("ERROR: You must set the object position");
		else if (obj->check[2] == 0 && obj->type != SPHERE_ID)
			kill_all("ERROR: You must set the object direction");
		else if (obj->check[5] == 0)
			kill_all("ERROR: You must set the reflection level");
		else if (obj->check[6] == 0)
			kill_all("ERROR: You must set the rafraction level");
		else if (obj->check[3] == 0)
			kill_all("ERROR: You must set the object color");
		else if (obj->check[4] == 0 && (obj->type == DISK_ID || obj->type == SPHERE_ID || obj->type == TORUS_ID || obj->type == PARABOLOID_ID))
			kill_all("ERROR: You must set the sphere radius");
        else if (obj->check[11] == 0 && obj->type == TORUS_ID)
            kill_all("ERROR: You must set the torus main radius");
		obj = obj->next;
	}
}

void cheak_part(t_rt *rt)
{
	if (rt->scene.check[0] == 0)
		kill_all("ERROR: You must create camera");
	else if (rt->scene.check[2] == 0)
		kill_all("ERROR: You must create scene");
	else if (rt->scene.check[2] == 0)
		kill_all("ERROR: You must create at least one object");
}