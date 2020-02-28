/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 16:08:56 by daron             #+#    #+#             */
/*   Updated: 2020/02/28 17:21:10 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				kill_all(char *message)
{
	perror(message);
	exit(1);
}

void			sdl_initialize(t_rt *rt)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		kill_all("Can't initialize SDL <sdl_initialize>");
	if (!(rt->window.window = SDL_CreateWindow((const char*)rt->window.windname, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, rt->window.size[0], rt->window.size[1], SDL_WINDOW_SHOWN)))
		kill_all("Can't initialize Window <sdl_initialize>");
	if (!(rt->window.render = SDL_CreateRenderer(rt->window.window, -1, SDL_RENDERER_ACCELERATED)))
		kill_all("Can't render Window <sdl_initialize>");
}

void kill_error(char *message, int string_number)
{
	// Message: ERROR: {message}  String number {string_number}
	kill_all(ft_strjoin_del(ft_strjoin(
			ft_strjoin("ERROR: ", message),
			" String number "), ft_itoa(string_number), 'R'));
}

void printf_scene_data(t_rt *rt)
{
	printf("-------------------------------------------------------------------\n");
	printf("Window name = %s\nWindow size = {%d, %d}\n maxref = %d \n "
		   "antialias = %d\n ambient = %g\n effect = %s\n", rt->window.windname,
		   rt->window.size[0], rt->window.size[1], rt->scene.maxref,
		   rt->window.anti_alias, rt->scene.ambient, rt->window.effecr_name);
	printf("\n");
	printf("Camera pos = {%g, %g, %g}\n Camera dir = {%g, %g, %g}\n",
		   rt->cam.pos.x, rt->cam.pos.y, rt->cam.pos.z,
		   rt->cam.dir.x, rt->cam.dir.y, rt->cam.dir.z);
	printf("\n");

	int i = 0;
	while (i < rt->scene.lgh_c)
	{
		printf("Light pos = {%g, %g, %g}\nLight rgb = {%g, %g, %g}\n",
			   rt->lgh_mas[i].pos.x, rt->lgh_mas[i].pos.y, rt->lgh_mas[i].pos.z,
			   rt->lgh_mas[i].rgb.r, rt->lgh_mas[i].rgb.g, rt->lgh_mas[i].rgb.b);
		i++;
		printf("\n");
	}

	i = 0;
	while (i < rt->scene.obj_c)
	{
		printf("Name = %s type = %d\n"
			   "Object reflection = %d refl_coeff = %g\n"
			   "Refract on/off= %d ind_refr = %g coef_refr = %g\n"
			   "Dir = {%g, %g, %g}\n"
			   "Pos = {%g, %g, %g}\n"
			   "RGB = {%g, %g, %g}\n"
			   "Radius = %g\n"
			   "Spec = %d\n"
			   "Limit = %g\n"
			   "Texture_on = %d texture_name = %s\n"
			   "Obj_on = %d "
			   "file_name = %s\n",
			   rt->obj_mas[i].obj_name, rt->obj_mas[i].type,
			   rt->obj_mas[i].reflect, rt->obj_mas[i].coef_refl,
			   rt->obj_mas[i].refr, rt->obj_mas[i].ind_refr, rt->obj_mas[i].coef_refl,
			   rt->obj_mas[i].dir.x, rt->obj_mas[i].dir.y, rt->obj_mas[i].dir.z,
			   rt->obj_mas[i].pos.x, rt->obj_mas[i].pos.y, rt->obj_mas[i].pos.z,
			   rt->obj_mas[i].rgb.r, rt->obj_mas[i].rgb.g, rt->obj_mas[i].rgb.b,
			   rt->obj_mas[i].radius,
			   rt->obj_mas[i].spec,
			   rt->obj_mas[i].limit,
			   rt->obj_mas[i].text_on, rt->obj_mas[i].texture,
			   rt->obj_mas[i].obj_on, rt->obj_mas[i].file_name);
		i++;
		printf("\n");
	}
	printf("-------------------------------------------------------------------\n");
}

int				main(int argc, char **argv)
{
	t_cl		*cl;
	t_rt		rt;
	int			num_obj;

	num_obj = 0;
	if (argc != 2 || !argv[1] || !ft_strstr(argv[1], ".rt"))
		kill_all("usage: ./RTv1 scene_name");
	if (!(cl = (t_cl*)malloc(sizeof(t_cl))))
		kill_all("Can't initialize CL <main>");
	init_rt(&rt, argv[1], 1);

	
//	rt.data_obj = parsing_obj("objs/t_cube.obj", num_obj++);	
//	rt.data_obj = parsing_obj(rt.obj_mas[0].file_name, num_obj++);
	check_objs(&rt);
	printf("1START\n");
	sdl_initialize(&rt);
	if(!(cl->data = (int*)malloc(sizeof(int) * rt.window.size[0] * rt.window.size[1])))
		kill_all("Can't initialize CL_data <main>");
	rt.window.textur = SDL_CreateTexture(rt.window.render, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, rt.window.size[0], rt.window.size[1]);
	init_cl(cl, &rt);
	start_kernel(cl, &rt);
	rt.cl = cl;
	//printf_scene_data(&rt);
	events(&rt);
	return (0);
}
