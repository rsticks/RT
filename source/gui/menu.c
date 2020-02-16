/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzina <kzina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 18:46:49 by kzina             #+#    #+#             */
/*   Updated: 2020/02/16 16:57:39 by kzina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		draw_selected(t_rt *rt)
{
	char *pos;
	t_obj *obj;
	
	if (rt->select_obj != -1)
	{
		if ((obj = &rt->obj_mas[rt->select_obj]) != NULL)
		{
			if (!(rt->ui.temp_surf[1] = TTF_RenderText_Blended(rt->ui.font[1], obj->obj_name, (SDL_Color){SILV})))
				printf("wrong");
			if (!(pos = ft_itoa((int)obj->pos.x)))
				printf("wrong");
			if (!(rt->ui.temp_surf[2] = TTF_RenderText_Blended(rt->ui.font[1], pos, (SDL_Color){SILV})))
				printf("wrong");
			free(pos);
			if (!(pos = ft_itoa((int)obj->pos.y)))
				printf("wrong");
			if (!(rt->ui.temp_surf[3] = TTF_RenderText_Blended(rt->ui.font[1], pos, (SDL_Color){SILV})))
				printf("wrong");
			free(pos);
			if (!(pos = ft_itoa((int)obj->pos.z)))
				printf("wrong");
			if (!(rt->ui.temp_surf[4] = TTF_RenderText_Blended(rt->ui.font[1], pos, (SDL_Color){SILV})))
				printf("wrong");
			free(pos);
			if (!(pos = ft_itoa((int)obj->dir.x)))
				printf("wrong");
			if (!(rt->ui.temp_surf[5] = TTF_RenderText_Blended(rt->ui.font[1], pos, (SDL_Color){SILV})))
				printf("wrong");
			free(pos);
			if (!(pos = ft_itoa((int)obj->dir.y)))
				printf("wrong");
			if (!(rt->ui.temp_surf[6] = TTF_RenderText_Blended(rt->ui.font[1], pos, (SDL_Color){SILV})))
				printf("wrong");
			free(pos);
			if (!(pos = ft_itoa((int)obj->dir.z)))
				printf("wrong");
			if (!(rt->ui.temp_surf[7] = TTF_RenderText_Blended(rt->ui.font[1], pos, (SDL_Color){SILV})))
				printf("wrong");
			free(pos);
			rt->ui.textur[1] = SDL_CreateTextureFromSurface(rt->win_menu.render, rt->ui.temp_surf[1]);
			rt->ui.textur[2] = SDL_CreateTextureFromSurface(rt->win_menu.render, rt->ui.temp_surf[2]);
			rt->ui.textur[3] = SDL_CreateTextureFromSurface(rt->win_menu.render, rt->ui.temp_surf[3]);
			rt->ui.textur[4] = SDL_CreateTextureFromSurface(rt->win_menu.render, rt->ui.temp_surf[4]);
			rt->ui.textur[5] = SDL_CreateTextureFromSurface(rt->win_menu.render, rt->ui.temp_surf[5]);
			rt->ui.textur[6] = SDL_CreateTextureFromSurface(rt->win_menu.render, rt->ui.temp_surf[6]);
			rt->ui.textur[7] = SDL_CreateTextureFromSurface(rt->win_menu.render, rt->ui.temp_surf[7]);
			SDL_FreeSurface(rt->ui.temp_surf[1]);
			SDL_FreeSurface(rt->ui.temp_surf[2]);
			SDL_FreeSurface(rt->ui.temp_surf[3]);
			SDL_FreeSurface(rt->ui.temp_surf[4]);
			SDL_FreeSurface(rt->ui.temp_surf[5]);
			SDL_FreeSurface(rt->ui.temp_surf[6]);
			SDL_FreeSurface(rt->ui.temp_surf[7]);
			SDL_QueryTexture(rt->ui.textur[1], NULL, NULL, &rt->ui.rect[1].w, &rt->ui.rect[1].h);
			SDL_QueryTexture(rt->ui.textur[2], NULL, NULL, &rt->ui.rect[2].w, &rt->ui.rect[2].h);
			SDL_QueryTexture(rt->ui.textur[3], NULL, NULL, &rt->ui.rect[3].w, &rt->ui.rect[3].h);
			SDL_QueryTexture(rt->ui.textur[4], NULL, NULL, &rt->ui.rect[4].w, &rt->ui.rect[4].h);
			SDL_QueryTexture(rt->ui.textur[5], NULL, NULL, &rt->ui.rect[5].w, &rt->ui.rect[5].h);
			SDL_QueryTexture(rt->ui.textur[6], NULL, NULL, &rt->ui.rect[6].w, &rt->ui.rect[6].h);
			SDL_QueryTexture(rt->ui.textur[7], NULL, NULL, &rt->ui.rect[7].w, &rt->ui.rect[7].h);
			rt->ui.rect[1].x= 115;
			rt->ui.rect[1].y= 40;
			rt->ui.rect[2].x= 45;
			rt->ui.rect[2].y= 146;
			rt->ui.rect[3].x= 103;
			rt->ui.rect[3].y= 146;
			rt->ui.rect[4].x= 160;
			rt->ui.rect[4].y= 146;
			rt->ui.rect[5].x= 45;
			rt->ui.rect[5].y= 200;
			rt->ui.rect[6].x= 103;
			rt->ui.rect[6].y= 200;
			rt->ui.rect[7].x= 310;
			rt->ui.rect[7].y= 40;
			SDL_RenderCopy(rt->win_menu.render, rt->ui.textur[1], NULL, &rt->ui.rect[1]);
			SDL_RenderCopy(rt->win_menu.render, rt->ui.textur[2], NULL, &rt->ui.rect[2]);
			SDL_RenderCopy(rt->win_menu.render, rt->ui.textur[3], NULL, &rt->ui.rect[3]);
			SDL_RenderCopy(rt->win_menu.render, rt->ui.textur[4], NULL, &rt->ui.rect[4]);
			SDL_RenderCopy(rt->win_menu.render, rt->ui.textur[5], NULL, &rt->ui.rect[5]);
			SDL_RenderCopy(rt->win_menu.render, rt->ui.textur[6], NULL, &rt->ui.rect[6]);
			SDL_RenderCopy(rt->win_menu.render, rt->ui.textur[7], NULL, &rt->ui.rect[7]);
			SDL_DestroyTexture(rt->ui.textur[1]);
			SDL_DestroyTexture(rt->ui.textur[2]);
			SDL_DestroyTexture(rt->ui.textur[3]);
			SDL_DestroyTexture(rt->ui.textur[4]);
			SDL_DestroyTexture(rt->ui.textur[5]);
			SDL_DestroyTexture(rt->ui.textur[6]);
			SDL_DestroyTexture(rt->ui.textur[7]);
			/*draw_text(rt, obj.obj_name, 1, 115, 40);
			draw_text(rt, ft_itoa(pos[0]), 2, 45, 146);
			draw_text(rt, ft_itoa(pos[1]), 3, 103, 146);
			draw_text(rt, ft_itoa(pos[2]), 4, 160, 146);
			draw_text(rt, ft_itoa(pos[3]), 5, 45, 200);
			draw_text(rt, ft_itoa(pos[4]), 6, 103, 200);
			draw_text(rt, ft_itoa(pos[5]), 7, 160, 200);*/
		}
	}
}

void		draw_essentil_menu(t_rt *rt)
{
	if (rt->ui.textur[0] = SDL_CreateTextureFromSurface(rt->win_menu.render, rt->ui.temp_surf[0]))
	{
		SDL_QueryTexture(rt->ui.textur[0], NULL, NULL, &rt->ui.rect[0].w, &rt->ui.rect[0].h);
		rt->ui.rect[0].x= 0;
		rt->ui.rect[0].y= 0;
		SDL_RenderCopy(rt->win_menu.render, rt->ui.textur[0], NULL, &rt->ui.rect[0]);
	}
	else
		printf("shiiit");
}

/*void		my_free_ui(t_rt *rt)
{
	free(&rt->ui);
}**/

void		sdl_init_menu(t_rt *rt)
{
	TTF_Init();
	 if (!(rt->win_menu.window = SDL_CreateWindow("MENU", STATE_W,
	 STATE_H, WIDTH_M, HEIGHT_M, SDL_WINDOW_SHOWN)))
	 	kill_all("Can't initialize Window <sdl_initialize>");
	if (!(rt->win_menu.render = SDL_CreateRenderer(rt->win_menu.window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)))
		kill_all("Can't render menu window <sdl_init_menu>");
	if (!(rt->w_icon = IMG_Load("./assets/images/icon.png")))
		kill_all("Can't open image <sdl_init_menu>");
	if (!(rt->ui.font[0] = TTF_OpenFont("./assets/font/SourceCodePro.ttf", 16)))
		kill_all("Can't open font <sdl_init_menu>");
	if (!(rt->ui.font[1]= TTF_OpenFont("./assets/font/SourceCodePro.ttf", 14)))
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
	SDL_RenderPresent(rt->win_menu.render);
}

void		sdl_refresh(t_rt *rt, t_cl *cl)
{
	SDL_RenderClear(rt->window.render);
	SDL_UpdateTexture(rt->window.textur, NULL, cl->data, rt->window.size[0] * sizeof(int));
	SDL_RenderCopy(rt->window.render, rt->window.textur, NULL, NULL);
	SDL_RenderPresent(rt->window.render);
	free_o_l(cl);
	//SDL_SetCursor(rt->cursor);
}
