/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzina <kzina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 16:08:56 by daron             #+#    #+#             */
/*   Updated: 2020/03/06 13:46:26 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			sdl_initialize(t_rt *rt)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		kill_all("Can't initialize SDL <sdl_initialize>");
	if (!(rt->window.window = SDL_CreateWindow(
		(const char*)rt->window.windname, STATE_X, STATE_Y,
		rt->window.size[0], rt->window.size[1],
			SDL_WINDOW_SHOWN)))
		kill_all("Can't initialize Window <sdl_initialize>");
	if (!(rt->window.render = SDL_CreateRenderer(rt->window.window, -1,
			SDL_RENDERER_ACCELERATED)))
		kill_all("Can't render Window <sdl_initialize>");
	sdl_init_menu(rt);
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
	texture_init(&rt);
	check_objs(&rt);
	sdl_initialize(&rt);
	if (!(cl->data = (int*)malloc(sizeof(int) * rt.window.size[0]
			* rt.window.size[1])))
		kill_all("Can't initialize CL_data <main>");
	rt.window.textur = SDL_CreateTexture(rt.window.render,
			SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET,
			rt.window.size[0], rt.window.size[1]);
	init_cl(cl, &rt);
	start_kernel(cl, &rt);
	rt.cl = cl;
	printf_scene_data(&rt);
	events(&rt);
	return (0);
}
