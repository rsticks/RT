/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 16:08:56 by daron             #+#    #+#             */
/*   Updated: 2019/11/28 16:28:09 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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

void			sdl_initialize(t_sdl *sdl)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		kill_all("Can't initialize SDL <sdl_initialize>");
	if (!(sdl->window = SDL_CreateWindow("RTv1", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, W_WIDTH, W_HEIGHT, SDL_WINDOW_SHOWN)))
		kill_all("Can't initialize Window <sdl_initialize>");
	if (!(sdl->render = SDL_CreateRenderer(sdl->window, -1,
		SDL_RENDERER_ACCELERATED)))
		kill_all("Can't render Window <sdl_initialize>");
}

int				main(int argc, char **argv)
{
	t_cl		*cl;
	t_sdl		sdl;

	if (argc != 2 || !argv[1] || !ft_strstr(argv[1], ".rt"))
		kill_all("usage: ./RTv1 scene_name");
	if (!(cl = (t_cl*)malloc(sizeof(t_cl))))
		kill_all("Can't initialize CL <main>");
	cl->data = (int*)malloc(sizeof(int) * W_HEIGHT * W_WIDTH);
	sdl_initialize(&sdl);
	scene_parser(&sdl, argv[1]);
	sdl.textur = SDL_CreateTexture(sdl.render, SDL_PIXELFORMAT_ARGB8888,
	SDL_TEXTUREACCESS_TARGET, W_WIDTH, W_HEIGHT);
	cl->cl_obj = transform_obj_data(sdl.obj, &cl->o_c);
	cl->cl_light = transform_light_data(sdl.light, &cl->l_c);
	init_cl(cl);
	start_kernel(cl, &sdl);
	sdl.cl = cl;
	events(&sdl);
	return (0);
}
