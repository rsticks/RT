/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzina <kzina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 18:46:49 by kzina             #+#    #+#             */
/*   Updated: 2020/02/01 19:59:51 by kzina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		draw_selected(t_sdl *sdl)
{
	int x;
	int y;
	int z;
	char *name;
	t_object obj;

	SDL_SetRenderDrawColor(sdl->render2, SILV);
	SDL_RenderClear(sdl->render2);
	draw_essentil_menu(sdl);
	if (sdl->select_obj)
	{
		obj = sdl->select_obj[0];
		x = (int)obj.pos.x;
		y = (int)obj.pos.y;
		z = (int)obj.pos.z;
		if (sdl->select_obj->name == SPHERE_ID)
			name = SPHERE;
		if (sdl->select_obj->name == PLANE_ID)
			name = PLANE;
		if (sdl->select_obj->name == CYLINDER_ID)
			name = CYLINDER;
		if (sdl->select_obj->name == CONE_ID)
			name = CONE;
		sdl->ui->temp_surf[4] = TTF_RenderText_Blended(sdl->ui->font[1], name, (SDL_Color){BLACK});
		sdl->ui->temp_surf[5] = TTF_RenderText_Blended(sdl->ui->font[1], ft_itoa(x), (SDL_Color){BLACK});
		sdl->ui->temp_surf[6] = TTF_RenderText_Blended(sdl->ui->font[1], ft_itoa(y), (SDL_Color){BLACK});
		sdl->ui->temp_surf[7] = TTF_RenderText_Blended(sdl->ui->font[1], ft_itoa(z), (SDL_Color){BLACK});
		sdl->ui->textur[4] = SDL_CreateTextureFromSurface(sdl->render2, sdl->ui->temp_surf[4]);
		sdl->ui->textur[5] = SDL_CreateTextureFromSurface(sdl->render2, sdl->ui->temp_surf[5]);
		sdl->ui->textur[6] = SDL_CreateTextureFromSurface(sdl->render2, sdl->ui->temp_surf[6]);
		sdl->ui->textur[7] = SDL_CreateTextureFromSurface(sdl->render2, sdl->ui->temp_surf[7]);
		SDL_QueryTexture(sdl->ui->textur[4], NULL, NULL, &sdl->ui->rect[4].w, &sdl->ui->rect[4].h);
		SDL_QueryTexture(sdl->ui->textur[5], NULL, NULL, &sdl->ui->rect[5].w, &sdl->ui->rect[5].h);
		SDL_QueryTexture(sdl->ui->textur[6], NULL, NULL, &sdl->ui->rect[6].w, &sdl->ui->rect[6].h);
		SDL_QueryTexture(sdl->ui->textur[7], NULL, NULL, &sdl->ui->rect[7].w, &sdl->ui->rect[7].h);
		sdl->ui->rect[4].x= 10;
		sdl->ui->rect[4].y= 30;
		sdl->ui->rect[5].x= 60;
		sdl->ui->rect[5].y= 50;
		sdl->ui->rect[6].x= 160;
		sdl->ui->rect[6].y= 50;
		sdl->ui->rect[7].x= 260;
		sdl->ui->rect[7].y= 50;
		SDL_RenderCopy(sdl->render2, sdl->ui->textur[4], NULL, &sdl->ui->rect[4]);
		SDL_RenderCopy(sdl->render2, sdl->ui->textur[5], NULL, &sdl->ui->rect[5]);
		SDL_RenderCopy(sdl->render2, sdl->ui->textur[6], NULL, &sdl->ui->rect[6]);
		SDL_RenderCopy(sdl->render2, sdl->ui->textur[7], NULL, &sdl->ui->rect[7]);
	}
	SDL_RenderPresent(sdl->render2);
}

void		draw_essentil_menu(t_sdl *sdl)
{
	sdl->ui->font[0] = TTF_OpenFont("./assets/font/SourceCodePro.ttf", 16);
	sdl->ui->font[1]= TTF_OpenFont("./assets/font/SourceCodePro.ttf", 14);
	sdl->ui->temp_surf[0] = TTF_RenderText_Blended(sdl->ui->font[0],"TYPE OF OBJECT:", (SDL_Color){BLACK});
	sdl->ui->temp_surf[1] = TTF_RenderText_Blended(sdl->ui->font[0],"X:", (SDL_Color){BLACK});
	sdl->ui->temp_surf[2] = TTF_RenderText_Blended(sdl->ui->font[0],"Y:", (SDL_Color){BLACK});
	sdl->ui->temp_surf[3] = TTF_RenderText_Blended(sdl->ui->font[0],"Z:", (SDL_Color){BLACK});
	sdl->ui->textur[0] = SDL_CreateTextureFromSurface(sdl->render2, sdl->ui->temp_surf[0]);
	sdl->ui->textur[1] = SDL_CreateTextureFromSurface(sdl->render2, sdl->ui->temp_surf[1]);
	sdl->ui->textur[2] = SDL_CreateTextureFromSurface(sdl->render2, sdl->ui->temp_surf[2]);
	sdl->ui->textur[3] = SDL_CreateTextureFromSurface(sdl->render2, sdl->ui->temp_surf[3]);
	SDL_QueryTexture(sdl->ui->textur[0], NULL, NULL, &sdl->ui->rect[0].w, &sdl->ui->rect[0].h);
	SDL_QueryTexture(sdl->ui->textur[1], NULL, NULL, &sdl->ui->rect[1].w, &sdl->ui->rect[1].h);
	SDL_QueryTexture(sdl->ui->textur[2], NULL, NULL, &sdl->ui->rect[2].w, &sdl->ui->rect[2].h);
	SDL_QueryTexture(sdl->ui->textur[3], NULL, NULL, &sdl->ui->rect[3].w, &sdl->ui->rect[3].h);
	sdl->ui->rect[0].x= 10;
	sdl->ui->rect[0].y= 10;
	sdl->ui->rect[1].x= 10;
	sdl->ui->rect[1].y= 50;
	sdl->ui->rect[2].x= 110;
	sdl->ui->rect[2].y= 50;
	sdl->ui->rect[3].x= 210;
	sdl->ui->rect[3].y= 50;
	SDL_RenderCopy(sdl->render2, sdl->ui->textur[0], NULL, &sdl->ui->rect[0]);
	SDL_RenderCopy(sdl->render2, sdl->ui->textur[1], NULL, &sdl->ui->rect[1]);
	SDL_RenderCopy(sdl->render2, sdl->ui->textur[2], NULL, &sdl->ui->rect[2]);
	SDL_RenderCopy(sdl->render2, sdl->ui->textur[3], NULL, &sdl->ui->rect[3]);
}

void		my_free_ui(t_sdl *sdl)
{
	free(sdl->ui);
}

void		sdl_init_menu(t_sdl *sdl)
{
	TTF_Init();
	 if (!(sdl->window2 = SDL_CreateWindow("MENU", 1920,
	 80, WIDTH_M, HEIGHT_M, SDL_WINDOW_SHOWN)))
	 	kill_all("Can't initialize Window <sdl_initialize>");
	if (!(sdl->render2 = SDL_CreateRenderer(sdl->window2, -1,
		SDL_RENDERER_ACCELERATED)))
		kill_all("Can't render Window <sdl_initialize>");
	if (!(sdl->w_icon = IMG_Load("./assets/images/icon.png")))
		kill_all("Can't render Window <sdl_initialize>");
	SDL_SetWindowIcon(sdl->window, sdl->w_icon);
	sdl->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	SDL_SetCursor(sdl->cursor);
	if (!(sdl->ui = (t_ui*)ft_memalloc(sizeof(t_ui))))
		ft_putstr("ui init error\n");
	//draw_essentil_menu(sdl);
}

void		sdl_refresh(t_sdl *sdl, t_cl *cl)
{
	SDL_SetRenderDrawColor(sdl->render2, SILV);
	SDL_RenderClear(sdl->render2);
	draw_essentil_menu(sdl);
	SDL_RenderPresent(sdl->render2);
	SDL_RenderClear(sdl->render);
	SDL_UpdateTexture(sdl->textur, NULL, cl->data, W_WIDTH * sizeof(int));
	SDL_RenderCopy(sdl->render, sdl->textur, NULL, NULL);
	SDL_RenderPresent(sdl->render);
	SDL_SetCursor(sdl->cursor);
}
