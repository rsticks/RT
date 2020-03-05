/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzina <kzina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 15:49:21 by kzina             #+#    #+#             */
/*   Updated: 2020/03/01 18:51:15 by kzina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		draw_text(t_rt *rt, char *text, int t, int x, int y)
{
	rt->ui.temp_surf[t] = TTF_RenderText_Blended(rt->ui.font[1], text, rt->ui.color);
	rt->ui.textur[t] = SDL_CreateTextureFromSurface(rt->win_menu.render, rt->ui.temp_surf[t]);
	SDL_FreeSurface(rt->ui.temp_surf[t]);
	SDL_QueryTexture(rt->ui.textur[t], NULL, NULL, &rt->ui.rect[t].w, &rt->ui.rect[t].h);
	rt->ui.rect[t].x = x;
	rt->ui.rect[t].y = y;
	SDL_RenderCopy(rt->win_menu.render, rt->ui.textur[t], NULL, &rt->ui.rect[t]);
	SDL_DestroyTexture(rt->ui.textur[t]);
}

t_obj		*new_sphere(void)
{
	t_obj *obj;

	obj = (t_obj*)ft_memalloc(sizeof(t_obj));
	obj->obj_name = "sphere";
	obj->type = SPHERE_ID;
	obj->pos = (t_vector){0, 0, 0};
	obj->dir = (t_vector){0, 0, 0};
	obj->rgb = (t_rgb2){255.0, 0.0, 0.0};
	obj->radius = 25.00;
	obj->reflect = 1;
	obj->coef_refl = 0.5;
	obj->spec = 1;
	obj->refr = 0;
	obj->text_on = 0;
	return (obj);
}

void		menu_button(t_rt *rt, int x, int y)
{
	t_obj *obj;
	
	obj = rt->obj_head;
	if (x > 310 && x < 350 && y > 40 && y < 70)
	{
		while(obj)
			obj = obj->next;
		obj = new_sphere();
		obj->next = NULL;
	}
}