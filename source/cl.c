/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:16:48 by rsticks           #+#    #+#             */
/*   Updated: 2019/11/28 16:27:50 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		free_o_l(t_cl *cl)
{
	free(cl->cl_obj);
	free(cl->cl_light);
}

void			ft_init_cl(t_cl *cl)
{
	int			w;

	w = W_HEIGHT * W_WIDTH;
	cl->prog = clCreateProgramWithSource(cl->ct, 1,
	(const char**)&cl->k_s, &cl->k_l, &cl->err);
	cl->err = clBuildProgram(cl->prog, 1, cl->dev_id, NULL, NULL, NULL);
	cl->kernel = clCreateKernel(cl->prog, "start", &cl->err);
	cl->obj_mem = clCreateBuffer(cl->ct, CMRW,
	sizeof(t_cl_object) * cl->o_c, NULL, &cl->err);
	cl->light_mem = clCreateBuffer(cl->ct, CMRW,
	sizeof(t_cl_light) * cl->l_c, NULL, &cl->err);
	cl->img = clCreateBuffer(cl->ct, CMRW, sizeof(int) * w, NULL, &cl->err);
	cl->i_m = clCreateBuffer(cl->ct, CMRW, sizeof(int) * 8, NULL, &cl->err);
	cl->d_m = clCreateBuffer(cl->ct, CMRW, sizeof(float) * 7, NULL, &cl->err);
	cl->err = clSetKernelArg(cl->kernel, 0, sizeof(cl_mem), &cl->obj_mem);
	cl->err = clSetKernelArg(cl->kernel, 1, sizeof(cl_mem), &cl->light_mem);
	cl->err = clSetKernelArg(cl->kernel, 2, sizeof(cl_mem), &cl->img);
	cl->err = clSetKernelArg(cl->kernel, 3, sizeof(cl_mem), &cl->i_m);
	cl->err = clSetKernelArg(cl->kernel, 4, sizeof(cl_mem), &cl->d_m);
}

void			mem_to_kernel(t_sdl *sdl, float *d_m, int *i_m, t_cl *cl)
{
	d_m[0] = sdl->cam.pos.x;
	d_m[1] = sdl->cam.pos.y;
	d_m[2] = sdl->cam.pos.z;
	d_m[3] = sdl->ambient;
	d_m[4] = sdl->cam.rot.x;
	d_m[5] = sdl->cam.rot.y;
	d_m[6] = sdl->cam.rot.z;
	i_m[0] = W_WIDTH;
	i_m[1] = W_HEIGHT;
	i_m[2] = sdl->dital;
	i_m[3] = sdl->gloss_activ;
	i_m[4] = sdl->reflect_count;
	i_m[5] = cl->o_c;
	i_m[6] = cl->l_c;
	i_m[7] = sdl->pref;
}

void			init_cl(t_cl *cl)
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
	cl->k_s = (char*)malloc(sizeof(char) * 17000);
	cl->i = read(cl->fd, cl->k_s, 17000);
	cl->k_s[cl->i] = '\0';
	cl->k_l = ft_strlen(cl->k_s);
	ft_init_cl(cl);
	free_o_l(cl);
}

void			start_kernel(t_cl *cl, t_sdl *sdl)
{
	size_t		gws;
	int			i_m[8];
	float		d_m[7];

	cl->cl_obj = transform_obj_data(sdl->obj, &cl->o_c);
	cl->cl_light = transform_light_data(sdl->light, &cl->l_c);
	mem_to_kernel(sdl, d_m, i_m, cl);
	gws = W_WIDTH * W_HEIGHT;
	cl->err = clEnqueueWriteBuffer(cl->q, cl->i_m, CL_TRUE, 0,
	sizeof(int) * 8, i_m, 0, NULL, NULL);
	cl->err = clEnqueueWriteBuffer(cl->q, cl->d_m, CL_TRUE, 0,
	sizeof(float) * 7, d_m, 0, NULL, NULL);
	cl->err = clEnqueueWriteBuffer(cl->q, cl->obj_mem, CL_TRUE, 0,
	sizeof(t_cl_object) * cl->o_c, cl->cl_obj, 0, NULL, NULL);
	cl->err = clEnqueueWriteBuffer(cl->q, cl->light_mem, CL_TRUE, 0,
	sizeof(t_cl_light) * cl->l_c, cl->cl_light, 0, NULL, NULL);
	cl->err = clEnqueueNDRangeKernel(cl->q, cl->kernel, 1, NULL,
	&gws, NULL, 0, NULL, NULL);
	cl->err = clEnqueueReadBuffer(cl->q, cl->img,
	CL_TRUE, 0, sizeof(int) * gws, cl->data, 0, NULL, NULL);
	SDL_RenderClear(sdl->render);
	SDL_UpdateTexture(sdl->textur, NULL, cl->data, W_WIDTH * sizeof(int));
	SDL_RenderCopy(sdl->render, sdl->textur, NULL, NULL);
	SDL_RenderPresent(sdl->render);
	free_o_l(cl);
}
