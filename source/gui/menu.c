/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzina <kzina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 18:46:49 by kzina             #+#    #+#             */
/*   Updated: 2020/03/05 18:57:14 by kzina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		draw_selected(t_rt *rt)
{
	t_obj	*obj;

	if (rt->select_obj != -1)
	{
		obj = &rt->obj_mas[rt->select_obj];
		rt->ui.color = (SDL_Color){TXT};
		ft_strcpy(rt->text, obj->obj_name);
		draw_text(rt, 1, 82, 40);
		itoa((int)obj->pos.x, rt->text);
		calc_shift(rt);
		draw_text(rt, 2, 37 - rt->ui.shift, 100);
		itoa((int)obj->pos.y, rt->text);
		calc_shift(rt);
		draw_text(rt, 3, 103 - rt->ui.shift, 100);
		itoa((int)obj->pos.z, rt->text);
		calc_shift(rt);
		draw_text(rt, 4, 170 - rt->ui.shift, 100);
		draw_selected_2(rt, obj);
	}
}

void		draw_essentil_menu(t_rt *rt)
{
	rt->ui.textur[0] = SDL_CreateTextureFromSurface(rt->win_menu.render,
		rt->ui.temp_surf[0]);
	SDL_QueryTexture(rt->ui.textur[0], NULL, NULL,
		&rt->ui.rect[0].w, &rt->ui.rect[0].h);
	rt->ui.rect[0].x = 0;
	rt->ui.rect[0].y = 0;
	SDL_RenderCopy(rt->win_menu.render,
		rt->ui.textur[0], NULL, &rt->ui.rect[0]);
}

void		sdl_init_menu(t_rt *rt)
{
	TTF_Init();
	if (!(rt->win_menu.window = SDL_CreateWindow("MENU",
		STATE_X + rt->window.size[0], STATE_Y,
			WIDTH_M, HEIGHT_M, SDL_WINDOW_SHOWN)))
		kill_all("Can't initialize Window <sdl_initialize>");
	if (!(rt->win_menu.render = SDL_CreateRenderer(rt->win_menu.window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)))
		kill_all("Can't render menu window <sdl_init_menu>");
	else
	{
		SDL_SetRenderDrawBlendMode(rt->win_menu.render, SDL_BLENDMODE_BLEND);
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	}
	if (!(rt->w_icon = IMG_Load("./assets/images/icon.png")))
		kill_all("Can't open image <sdl_init_menu>");
	if (!(rt->ui.font[0] = TTF_OpenFont("./assets/font/SourceCodePro.ttf", 16)))
		kill_all("Can't open font <sdl_init_menu>");
	if (!(rt->ui.font[1] = TTF_OpenFont("./assets/font/SourceCodePro.ttf", 14)))
		kill_all("Can't open font <sdl_init_menu>");
	if (!(rt->ui.temp_surf[0] = IMG_Load("./assets/images/menu_rt.png")))
		kill_all("Can't open menu image <sdl_init_menu>");
	SDL_SetWindowIcon(rt->win_menu.window, rt->w_icon);
	rt->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	SDL_SetCursor(rt->cursor);
}

void		refresh_menu(t_rt *rt)
{
	SDL_RenderClear(rt->win_menu.render);
	draw_essentil_menu(rt);
	draw_selected(rt);
	draw_scene_param(rt);
	draw_color(rt);
	SDL_RenderPresent(rt->win_menu.render);
}

void		sdl_refresh(t_rt *rt, t_cl *cl)
{
	SDL_RenderClear(rt->window.render);
	SDL_UpdateTexture(rt->window.textur, NULL,
		cl->data, rt->window.size[0] * sizeof(int));
	SDL_RenderCopy(rt->window.render, rt->window.textur, NULL, NULL);
	SDL_RenderPresent(rt->window.render);
	free_o_l(cl);
}
