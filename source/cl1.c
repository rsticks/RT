/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 15:04:17 by rsticks           #+#    #+#             */
/*   Updated: 2020/03/06 15:15:56 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			mem_to_kernel(t_rt *rt, float *d_m, int *i_m)
{
	d_m[0] = rt->cam.pos.x;
	d_m[1] = rt->cam.pos.y;
	d_m[2] = rt->cam.pos.z;
	d_m[3] = rt->scene.ambient;
	d_m[4] = rt->cam.dir.x;
	d_m[5] = rt->cam.dir.y;
	d_m[6] = rt->cam.dir.z;
	i_m[0] = rt->window.size[0];
	i_m[1] = rt->window.size[1];
	i_m[2] = rt->window.anti_alias;
	i_m[3] = rt->scene.obj_c;
	i_m[4] = rt->scene.lgh_c;
	i_m[5] = rt->scene.maxref;
	i_m[6] = rt->data_obj->count_f;
}

static void		start_kernel_2(t_cl *cl, t_rt *rt, int *i_m, float *d_m)
{
	cl->err = clEnqueueWriteBuffer(cl->q, cl->i_m, CL_TRUE, 0,
	sizeof(int) * 7, i_m, 0, NULL, NULL);
	cl->err = clEnqueueWriteBuffer(cl->q, cl->d_m, CL_TRUE, 0,
	sizeof(float) * 7, d_m, 0, NULL, NULL);
	cl->err = clEnqueueWriteBuffer(cl->q, cl->obj_mem, CL_TRUE, 0,
	sizeof(t_cl_object) * rt->scene.obj_c, cl->cl_obj, 0, NULL, NULL);
	cl->err = clEnqueueWriteBuffer(cl->q, cl->light_mem, CL_TRUE, 0,
	sizeof(t_cl_light) * rt->scene.lgh_c, cl->cl_light, 0, NULL, NULL);
	cl->err = clEnqueueWriteBuffer(cl->q, cl->txt_rgb_mem, CL_TRUE,
	0, sizeof(t_rgb) * rt->txt_gpu.total_size, rt->txt_gpu.tx, 0, NULL, NULL);
	cl->err = clEnqueueWriteBuffer(cl->q, cl->txt_data_mem, CL_TRUE,
	0, sizeof(t_txdata) * rt->txt_gpu.tx_count, rt->txt_gpu.txdata, 0,
	NULL, NULL);
}

void			start_kernel(t_cl *cl, t_rt *rt)
{
	size_t		gws;
	int			i_m[7];
	float		d_m[7];

	cl->cl_obj = transform_obj_data(rt);
	cl->cl_light = transform_light_data(rt);
	mem_to_kernel(rt, d_m, i_m);
	gws = rt->window.size[0] * rt->window.size[1];
	start_kernel_2(cl, rt, i_m, d_m);
	cl->err = clEnqueueWriteBuffer(cl->q, cl->obj, CL_TRUE, 0,
	sizeof(t_cl_data_obj) * rt->data_obj->max_c, rt->data_obj->d_obj, 0, NULL,
	NULL);
	cl->err = clEnqueueNDRangeKernel(cl->q, cl->kernel, 1, NULL,
	&gws, NULL, 0, NULL, NULL);
	cl->err = clEnqueueReadBuffer(cl->q, cl->img, CL_TRUE, 0,
	sizeof(int) * gws, cl->data, 0, NULL, NULL);
	refresh_menu(rt);
	sdl_refresh(rt, cl);
}
