/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 17:04:27 by daron             #+#    #+#             */
/*   Updated: 2020/03/06 13:46:26 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	print_light_info(t_rt *rt)
{
	int		i;

	i = 0;
	while (i < rt->scene.lgh_c)
	{
		printf("Light pos = {x%g, y%g, z%g}\nLight rgb = {%g, %g, %g}\n",
			rt->lgh_mas[i].pos.x, rt->lgh_mas[i].pos.y, rt->lgh_mas[i].pos.z,
			rt->lgh_mas[i].rgb.r, rt->lgh_mas[i].rgb.g, rt->lgh_mas[i].rgb.b);
		i++;
		printf("\n");
	}
}

static void	obj_print_1(t_obj *obj_mas)
{
	printf("Name = %s type = %d\nObject reflection = %d refl_coeff = %g\n"
		"Refract on/off= %d ind_refr = %g coef_refr = %g\n"
		"Dir = {x%g, y%g, z%g}\n"
		"Pos = {x%g, y%g, z%g}\n"
		"RGB = {%g, %g, %g}\n"
		"Radius = %g\n",
		obj_mas->obj_name, obj_mas->type,
		obj_mas->reflect, obj_mas->coef_refl,
		obj_mas->refr, obj_mas->ind_refr, obj_mas->coef_refr,
		obj_mas->dir.x, obj_mas->dir.y, obj_mas->dir.z,
		obj_mas->pos.x, obj_mas->pos.y, obj_mas->pos.z,
		obj_mas->rgb.r, obj_mas->rgb.g, obj_mas->rgb.b,
		obj_mas->radius);
}

static void	obj_print_2(t_obj *obj_mas)
{
	printf("Torus_r = %g\n"
		"Spec = %d\n"
		"Limit = %g\n"
		"Texture_on = %d texture_name = %s\n"
		"Obj_on = %d file_name = %s\n"
		"contruction_id = %d\n",
		obj_mas->torus_r,
		obj_mas->spec,
		obj_mas->limit,
		obj_mas->text_on, obj_mas->texture,
		obj_mas->obj_on, obj_mas->file_name,
		obj_mas->contruction_id);
}

static void	print_object_info(t_rt *rt)
{
	int		i;

	i = 0;
	while (i < rt->scene.obj_c)
	{
		obj_print_1(&rt->obj_mas[i]);
		obj_print_2(&rt->obj_mas[i]);
		i++;
		printf("\n");
	}
}

void		printf_scene_data(t_rt *rt)
{
	printf("---------------------------------------------------------------\n");
	printf("Window name = %s\nWindow size = {%d, %d}\n maxref = %d \n"
		"antialias = %d\n ambient = %g\n effect = %s\n skybox_id = %d",
		rt->window.windname, rt->window.size[0], rt->window.size[1],
		rt->scene.maxref, rt->window.anti_alias, rt->scene.ambient,
		rt->window.effecr_name, rt->scene.skybox_id);
	printf("\n");
	printf("Camera pos = {x%g, y%g, z%g}\n Camera dir = {x%g, y%g, z%g}\n",
			rt->cam.pos.x, rt->cam.pos.y, rt->cam.pos.z,
			rt->cam.dir.x, rt->cam.dir.y, rt->cam.dir.z);
	printf("\n");
	print_light_info(rt);
	print_object_info(rt);
	printf("---------------------------------------------------------------\n");
}
