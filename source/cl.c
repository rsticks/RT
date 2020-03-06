/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:16:48 by rsticks           #+#    #+#             */
/*   Updated: 2020/03/06 15:16:03 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			free_o_l(t_cl *cl)
{
	free(cl->cl_obj);
	free(cl->cl_light);
}

void			ft_init_cl_2(t_cl *cl, t_rt *rt)
{
	int			w;

	w = rt->window.size[0] * rt->window.size[1];
	cl->obj_mem = clCreateBuffer(cl->ct, CMRW,
	sizeof(t_cl_object) * rt->scene.obj_c, NULL, &cl->err);
	cl->light_mem = clCreateBuffer(cl->ct, CMRW,
	sizeof(t_cl_light) * rt->scene.lgh_c, NULL, &cl->err);
	cl->txt_rgb_mem = clCreateBuffer(cl->ct, CMRW,
	sizeof(t_rgb) * rt->txt_gpu.total_size, NULL, &cl->err);
	cl->txt_data_mem = clCreateBuffer(cl->ct, CMRW,
	sizeof(t_txdata) * rt->txt_gpu.tx_count, NULL, &cl->err);
	cl->img = clCreateBuffer(cl->ct, CMRW, sizeof(int) * w, NULL, &cl->err);
	cl->i_m = clCreateBuffer(cl->ct, CMRW, sizeof(int) * 7, NULL, &cl->err);
	cl->d_m = clCreateBuffer(cl->ct, CMRW, sizeof(float) * 7, NULL, &cl->err);
	cl->obj = clCreateBuffer(cl->ct, CMRW,
	sizeof(t_cl_data_obj) * rt->data_obj->max_c, NULL, &cl->err);
}

void			ft_init_cl(t_cl *cl, t_rt *rt)
{
	cl->prog = clCreateProgramWithSource(cl->ct, 1,
	(const char**)&cl->k_s, &cl->k_l, &cl->err);
	cl->err = clBuildProgram(cl->prog, 1, cl->dev_id, NULL, NULL, NULL);
	cl->kernel = clCreateKernel(cl->prog, "start", &cl->err);
	ft_init_cl_2(cl, rt);
	cl->err = clSetKernelArg(cl->kernel, 0, sizeof(cl_mem), &cl->obj_mem);
	cl->err = clSetKernelArg(cl->kernel, 1, sizeof(cl_mem), &cl->light_mem);
	cl->err = clSetKernelArg(cl->kernel, 2, sizeof(cl_mem), &cl->img);
	cl->err = clSetKernelArg(cl->kernel, 3, sizeof(cl_mem), &cl->i_m);
	cl->err = clSetKernelArg(cl->kernel, 4, sizeof(cl_mem), &cl->d_m);
	cl->err = clSetKernelArg(cl->kernel, 5, sizeof(cl_mem), &cl->txt_rgb_mem);
	cl->err = clSetKernelArg(cl->kernel, 6, sizeof(cl_mem), &cl->txt_data_mem);
	cl->err = clSetKernelArg(cl->kernel, 7, sizeof(cl_mem), &cl->obj);
}

void			init_cl(t_cl *cl, t_rt *rt)
{
	cl->err = clGetPlatformIDs(0, NULL, &cl->n_plat);
	cl->p_id = (cl_platform_id *)malloc(sizeof(cl_platform_id) * cl->n_plat);
	cl->err = clGetPlatformIDs(cl->n_plat, cl->p_id, NULL);
	cl->err = clGetDeviceIDs(cl->p_id[0], CDTG, 0, NULL, &cl->n_dev);
	cl->dev_id = (cl_device_id *)malloc(sizeof(cl_device_id) * cl->n_dev);
	cl->err = clGetDeviceIDs(cl->p_id[0], CDTG,
	cl->n_dev, cl->dev_id, NULL);
	cl->ct = clCreateContext(NULL, 1, cl->dev_id, NULL, NULL, &cl->err);
	cl->q = clCreateCommandQueue(cl->ct, cl->dev_id[0], 0, &cl->err);
	cl->fd = open("kernel.cl", O_RDONLY);
	cl->k_s = (char*)malloc(sizeof(char) * 40000);
	cl->i = read(cl->fd, cl->k_s, 40000);
	cl->k_s[cl->i] = '\0';
	cl->k_l = ft_strlen(cl->k_s);
	ft_init_cl(cl, rt);
}
