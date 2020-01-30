/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzina <kzina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 18:46:49 by kzina             #+#    #+#             */
/*   Updated: 2020/01/30 20:51:21 by kzina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		sdl_init_menu(t_sdl *sdl)
{
	TTF_Init();
	 if (!(sdl->window2 = SDL_CreateWindow("MENU", 1920,
	 80, WIDTH_M, HEIGHT_M, SDL_WINDOW_SHOWN)))
	 	kill_all("Can't initialize Window <sdl_initialize>");
	if (!(sdl->render2 = SDL_CreateRenderer(sdl->window2, -1,
		SDL_RENDERER_ACCELERATED)))
		kill_all("Can't render Window <sdl_initialize>");
	sdl->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	SDL_SetCursor(sdl->cursor);
	SDL_SetRenderDrawColor(sdl->render2, SILV);
	SDL_RenderClear(sdl->render2);

	SDL_Surface    *temp_surface	= NULL;

	TTF_Font       *font		= NULL;
	TTF_Font       *font2		= NULL;
	font = TTF_OpenFont("./assets/font/SourceCodePro.ttf", 20);
	font2 = TTF_OpenFont("./assets/font/SourceCodePro.ttf", 16);

	SDL_Texture    *link2_tp	= NULL;
	SDL_Rect 	link2_tp_dst;
	SDL_Texture    *link1_tp	= NULL;
	SDL_Rect 	link1_tp_dst;

	SDL_Color color ={BLACK};
	temp_surface=TTF_RenderText_Blended(font,"MENU",color);
	link2_tp= SDL_CreateTextureFromSurface(sdl->render2, temp_surface);
	SDL_QueryTexture(link2_tp, NULL, NULL, &link2_tp_dst.w, &link2_tp_dst.h);
	link2_tp_dst.x= 170;
	link2_tp_dst.y= 10;
	SDL_RenderCopy(sdl->render2, link2_tp, NULL, &link2_tp_dst);
	temp_surface=TTF_RenderText_Blended(font2, ft_itoa(sdl->select_obj->name),color);
	link1_tp= SDL_CreateTextureFromSurface(sdl->render2, temp_surface);
	SDL_QueryTexture(link1_tp, NULL, NULL, &link1_tp_dst.w, &link1_tp_dst.h);
	link1_tp_dst.x= 10;
	link1_tp_dst.y= 30;
	SDL_RenderCopy(sdl->render2, link1_tp, NULL, &link1_tp_dst);
	SDL_RenderPresent(sdl->render2);
}

void		sdl_refresh(t_sdl *sdl, t_cl *cl)
{
	//SDL_RenderClear(sdl->render2);
	//SDL_RenderCopy(sdl->render2, sdl->textur2, NULL, NULL);
	//SDL_RenderPresent(sdl->render2);
	SDL_RenderClear(sdl->render);
	SDL_UpdateTexture(sdl->textur, NULL, cl->data, W_WIDTH * sizeof(int));
	SDL_RenderCopy(sdl->render, sdl->textur, NULL, NULL);
	SDL_RenderPresent(sdl->render);
	SDL_SetCursor(sdl->cursor);
}
