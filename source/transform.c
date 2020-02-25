/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 15:32:59 by rsticks           #+#    #+#             */
/*   Updated: 2020/02/18 14:14:00 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_cl_object			*transform_obj_data(t_rt *rt)
{
	t_cl_object		*cl_obj;
	int i;

	if (!(cl_obj = (t_cl_object*)malloc(sizeof(t_cl_object) * rt->scene.obj_c)))
		kill_all("ERROR: Can't allocate memory for cl_obj <transform_obj_data>");
	i = 0;
	while (i < rt->scene.obj_c)
	{
		cl_obj[i].pos = (cl_float3){{rt->obj_mas[i].pos.x, rt->obj_mas[i].pos.y, rt->obj_mas[i].pos.z}};
		cl_obj[i].rot = (cl_float3){{rt->obj_mas[i].dir.x, rt->obj_mas[i].dir.y, rt->obj_mas[i].dir.z}};
		cl_obj[i].col = (cl_float3){{rt->obj_mas[i].rgb.r, rt->obj_mas[i].rgb.g, rt->obj_mas[i].rgb.b}};
		cl_obj[i].r = rt->obj_mas[i].radius;
		cl_obj[i].name = rt->obj_mas[i].type;
		cl_obj[i].specular = rt->obj_mas[i].spec;
		cl_obj[i].coef_refl = rt->obj_mas[i].coef_refl;
		cl_obj[i].limit = rt->obj_mas[i].limit;

		cl_obj[i].reflect = rt->obj_mas[i].reflect;
		cl_obj[i].coef_refl = rt->obj_mas[i].coef_refl;

		cl_obj[i].refr = rt->obj_mas[i].refr;
		cl_obj[i].ind_refr = rt->obj_mas[i].ind_refr;
		cl_obj[i].coef_refr = rt->obj_mas[i].coef_refr;

        cl_obj[i].torus_r = rt->obj_mas[i].torus_r;

		/*printf("Not Kernel - type = %d\npos = (%g, %g, %g)\nrot = (%g, %g, %g)\n"
		 "col = (%g, %g, %g)\nradius = %g\nreflect = %d coef = %g\n"
         "cl_obj[i].refr = %d, rt->obj_mas[i].ind_refr = %g, rt->obj_mas[i].coef_refr = %g\n\n",
			   cl_obj[i].name,
			   cl_obj[i].pos.x, cl_obj[i].pos.y, cl_obj[i].pos.z,
			   cl_obj[i].rot.x, cl_obj[i].rot.y, cl_obj[i].rot.z,
			   cl_obj[i].col.x, cl_obj[i].col.y, cl_obj[i].col.z,
			   cl_obj[i].r,
			   cl_obj[i].reflect, cl_obj[i].coef_refl,
			   cl_obj[i].refr, cl_obj[i].ind_refr, cl_obj[i].coef_refr);*/
		i++;
	}
	
	return (cl_obj);
}

t_cl_light			*transform_light_data(t_rt *rt)
{
	t_cl_light		*cl_light;
	int i;


	if(!(cl_light = (t_cl_light*)malloc(sizeof(t_cl_light) * rt->scene.lgh_c)))
		kill_all("ERROR: Can't allocate memory for cl_light <transform_light_data>");
	i = 0;
	while (i < rt->scene.lgh_c)
	{
		cl_light[i].pos =(cl_float3){{rt->lgh_mas[i].pos.x, rt->lgh_mas[i].pos.y, rt->lgh_mas[i].pos.z}};
		cl_light[i].col =(cl_float3){{rt->lgh_mas[i].rgb.r, rt->lgh_mas[i].rgb.g, rt->lgh_mas[i].rgb.b}};
		cl_light[i].inten = 20;

		/*printf("Not Kernel - Light pos = (%g, %g, %g)\ncolor = (%g, %g, %g)\n\n",
			   cl_light[i].pos.x, cl_light[i].pos.y, cl_light[i].pos.z,
			   cl_light[i].col.x, cl_light[i].col.y, cl_light[i].col.z);*/
		i++;
	}
	return (cl_light);
}
