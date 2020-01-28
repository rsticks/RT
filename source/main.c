/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 16:08:56 by daron             #+#    #+#             */
/*   Updated: 2020/01/27 17:19:40 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			ft_fzero(float *s, int n)
{
	int			i;

	i = 0;
	while (i < n)
	{
		s[i] = 0.0f;
		i++;
	}
}

double			get_quadratic_solution(double a, double b, double discriminant)
{
	double		t1;
	double		t2;

	t1 = (-b - sqrt(discriminant)) / (2 * a);
	t2 = (-b + sqrt(discriminant)) / (2 * a);
	if ((t1 <= t2 && t1 >= 0) || (t1 >= 0 && t2 < 0))
		return (t1);
	else if ((t2 <= t1 && t2 >= 0) || (t1 < 0 && t2 >= 0))
		return (t2);
	return (-1);
}

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
//------------------------------------------------------------------------------
void kill_error(char *message, int string_number)
{
	// Message: ERROR: {message}  String number {string_number}
	kill_all(ft_strjoin_del(ft_strjoin(
			ft_strjoin("ERROR: ", message),
			" String number "), ft_itoa(string_number), 'R'));
}

void init_struct(t_rt *rt)
{
	if (!(rt->read_b.buff = (char**)malloc(sizeof(char*) * 2)))
		kill_all("ERROR can't create buffer for reading file <init_struct>");
	rt->read_b.str_c = 0;

	rt->scene.spec = 0.0;
	rt->scene.reflection_c = 0;
	rt->scene.obj_c = 0;
	rt->scene.lgh_c = 0;


	rt->obj_head = NULL;
	rt->lgh_head = NULL;

	rt->window.windname = NULL;
	rt->window.effecr_name = NULL;
	rt->window.effect_on = 0;

	ft_memset_int(rt->scene.check, 0, 4);
	ft_memset_int(rt->window.check, 0, 6);
	ft_memset_int(rt->cam.check, 0, 2);
}

void parse_line(t_rt *rt, char *line, int str_c)
{
	if (*line)
	{
		if (rt->read_b.str_c >= 1)
		{
			if (rt->read_b.str_c >= 1 && (ft_strequ(rt->read_b.buff[0], "scene")) > 0)
				scene_parser(rt, line, str_c);
			else if (rt->read_b.str_c >= 1 && (ft_strequ(rt->read_b.buff[0], "camera")) > 0)
				camera_parser(rt, line, str_c);
			else if (rt->read_b.str_c >= 1 && (ft_strequ(rt->read_b.buff[0], "light")) > 0)
				light_parser(rt, line, str_c);
			else if (rt->read_b.str_c >= 1 && (ft_strequ(rt->read_b.buff[0], "object")) > 0)
				object_parser(rt, line, str_c);
			else
				kill_error("Uncorrected object tag" , str_c - 1);
		}
		else
			check_tag(rt, line, str_c);
	}
}

void init_rt(t_rt *rt, char *filename, int str_c)
{
	int fd;
	int read_count;
	char *line;

	if ((fd = open(filename, O_RDWR)) < 0)
		kill_all(ft_strjoin("ERROR: Can't open file ", filename));
	init_struct(rt);
	while ((read_count = get_next_line(fd, &line)) > 0)
	{
		parse_line(rt, line, str_c);
		free(line);
		str_c++;
	}
	close(fd);
	free(rt->read_b.buff);
	cheak_camera(rt);
	cheak_scene(rt);
	cheak_object(rt);
	if (rt->lgh_head != NULL)
		cheak_light(rt);
	cheak_part(rt);
	list_to_mas(rt);
}

//------------------------------------------------------------------------------
int				main(int argc, char **argv)
{
	t_cl		*cl;
	t_rt		rt;

	if (argc != 2 || !argv[1] || !ft_strstr(argv[1], ".rt"))
		kill_all("usage: ./RTv1 scene_name");
	if (!(cl = (t_cl*)malloc(sizeof(t_cl))))
		kill_all("Can't initialize CL <main>");
	cl->data = (int*)malloc(sizeof(int) * W_HEIGHT * W_WIDTH);

	init_rt(&rt, argv[1], 1);
	sdl_initialize(&rt);
	//scene_parser(&sdl, argv[1]);

	rt.window.textur = SDL_CreateTexture(rt.window.render, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, rt.window.size[0], rt.window.size[0]);
	cl->cl_obj = transform_obj_data(&rt);
	cl->cl_light = transform_light_data(&rt);
	init_cl(cl, &rt);
	start_kernel(cl, &rt);
	//sdl.cl = cl;


	/*printf("\n\nWindow name = %s\nWindow size = {%d, %d}\n maxref = %d \n "
		   "antialias = %d\n ambient = %g\n effect = %s\n", rt.window.windname,
		   rt.window.size[0], rt.window.size[1], rt.scene.maxref,
		   rt.window.anti_alias, rt.scene.ambient, rt.window.effecr_name);
	printf("\n");
	printf("Camera pos = {%g, %g, %g}\n Camera dir = {%g, %g, %g}\n",
		   rt.cam.pos.x, rt.cam.pos.y, rt.cam.pos.z,
		   rt.cam.dir.x, rt.cam.dir.y, rt.cam.dir.z);
	printf("\n");

	int i = 0;
	while (i < rt.scene.lgh_c)
	{
		printf("Light pos = {%g, %g, %g}\nLight rgb = {%d, %d, %d}\n",
			   rt.lgh_mas[i].pos.x, rt.lgh_mas[i].pos.y, rt.lgh_mas[i].pos.z,
			   rt.lgh_mas[i].rgb.r, rt.lgh_mas[i].rgb.g, rt.lgh_mas[i].rgb.b);
		i++;
		printf("\n");
	}

	i = 0;
	while (i < rt.scene.obj_c)
	{
		printf("Name = %s type = %d\n"
			   "Object reflection = %d refl_coeff = %g\n"
			   "Refract on/off= %d ind_refr = %g coef_refr = %g\n"
			   "Dir = {%g, %g, %g}\n"
			   "Pos = {%g, %g, %g}\n"
			   "RGB = {%d, %d, %d}\n"
			   "Radius = %g\n"
			   "Spec = %d\n"
			   "Limit = %g\n"
			   "Texture_on = %d texture_name = %s\n"
			   "Obj_on = %d "
			   "file_name = %s\n",
			   rt.obj_mas[i].obj_name, rt.obj_mas[i].type,
			   rt.obj_mas[i].reflect, rt.obj_mas[i].coef_refl,
			   rt.obj_mas[i].refr, rt.obj_mas[i].ind_refr, rt.obj_mas[i].coef_refl,
			   rt.obj_mas[i].dir.x, rt.obj_mas[i].dir.y, rt.obj_mas[i].dir.z,
			   rt.obj_mas[i].pos.x, rt.obj_mas[i].pos.y, rt.obj_mas[i].pos.z,
			   rt.obj_mas[i].rgb.r, rt.obj_mas[i].rgb.g, rt.obj_mas[i].rgb.b,
			   rt.obj_mas[i].radius,
			   rt.obj_mas[i].spec,
			   rt.obj_mas[i].limit,
			   rt.obj_mas[i].text_on, rt.obj_mas[i].texture,
			   rt.obj_mas[i].obj_on, rt.obj_mas[i].file_name);
		i++;
		printf("\n");
	}*/

	while (1)
		while (SDL_PollEvent(&rt.window.event))
			if ((SDL_QUIT == rt.window.event.type) || (SDL_SCANCODE_ESCAPE == rt.window.event.key.keysym.scancode))
				exit(0);


	//events(&sdl);
	return (0);
}
