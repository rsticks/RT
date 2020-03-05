/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzina <kzina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 15:49:21 by kzina             #+#    #+#             */
/*   Updated: 2020/03/05 21:07:58 by kzina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		draw_text(t_rt *rt, int t, int x, int y)
{
	rt->ui.temp_surf[t] = TTF_RenderText_Blended(rt->ui.font[1],
		rt->text, rt->ui.color);
	rt->ui.textur[t] = SDL_CreateTextureFromSurface(rt->win_menu.render,
		rt->ui.temp_surf[t]);
	SDL_FreeSurface(rt->ui.temp_surf[t]);
	SDL_QueryTexture(rt->ui.textur[t], NULL, NULL,
		&rt->ui.rect[t].w, &rt->ui.rect[t].h);
	rt->ui.rect[t].x = x;
	rt->ui.rect[t].y = y;
	SDL_RenderCopy(rt->win_menu.render,
		rt->ui.textur[t], NULL, &rt->ui.rect[t]);
	SDL_DestroyTexture(rt->ui.textur[t]);
}

void		draw_color_2(t_rt *rt)
{
	int x;
	int y;

	SDL_GetMouseState(&x, &y);
	if (x > 238 && x < 258 && y > 204 && y < 224)
		rt->obj_mas[rt->select_obj].rgb = (t_rgb2){BLU};
	else if (x > 268 && x < 288 && y > 204 && y < 224)
		rt->obj_mas[rt->select_obj].rgb = (t_rgb2){DBL};
	else if (x > 298 && x < 318 && y > 204 && y < 224)
		rt->obj_mas[rt->select_obj].rgb = (t_rgb2){PUR};
	else if (x > 328 && x < 348 && y > 204 && y < 224)
		rt->obj_mas[rt->select_obj].rgb = (t_rgb2){VIO};
}

void		draw_color(t_rt *rt)
{
	int x;
	int y;

	SDL_GetMouseState(&x, &y);
	if (rt->select_obj != -1)
	{
		if (x > 238 && x < 258 && y > 174 && y < 194)
			rt->obj_mas[rt->select_obj].rgb = (t_rgb2){RED};
		else if (x > 268 && x < 288 && y > 174 && y < 194)
			rt->obj_mas[rt->select_obj].rgb = (t_rgb2){ORE};
		else if (x > 298 && x < 318 && y > 174 && y < 194)
			rt->obj_mas[rt->select_obj].rgb = (t_rgb2){YEL};
		else if (x > 328 && x < 348 && y > 174 && y < 194)
			rt->obj_mas[rt->select_obj].rgb = (t_rgb2){GRE};
		draw_color_2(rt);
	}
}

void		draw_scene_param(t_rt *rt)
{
	rt->ui.color = (SDL_Color){TXT};
	itoa((int)rt->scene.obj_c, rt->text);
	draw_text(rt, 11, 363, 41);
	itoa((int)rt->scene.lgh_c, rt->text);
	draw_text(rt, 12, 363, 71);
	itoa((int)rt->window.anti_alias, rt->text);
	draw_text(rt, 13, 363, 101);
}
