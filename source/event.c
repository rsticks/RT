/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 12:30:37 by daron             #+#    #+#             */
/*   Updated: 2019/11/28 16:27:53 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	create_guide_sides(t_move *move, t_sdl *sdl)
{
	move->k = vec_sub(&SC.rot, &SC.pos);
	move->k = vec_norm(&move->k);
	move->i = vec_cross(&move->k, &(t_vector){0.0, 1.0, 0.0});
	move->i = vec_norm(&move->i);
	move->j = vec_cross(&move->i, &move->k);
}

static void	event_2(t_sdl *sdl, t_move *move)
{
	if (SDLK_e == SEKKS && sdl->event.type == SDL_KEYDOWN)
		swithc_pref(sdl);
	else if (sdl->event.type == SDL_KEYDOWN && SSO == NULL)
		key_down(sdl, move);
	else if (sdl->event.type == SDL_KEYDOWN && SSO != NULL)
		key_down_for_object(sdl, move);
	else if (sdl->event.type == SDL_MOUSEBUTTONDOWN)
		mouse_down(sdl);
}

void		events(t_sdl *sdl)
{
	t_move	move;

	create_guide_sides(&move, sdl);
	while (1)
		while (SDL_PollEvent(&sdl->event))
		{
			if ((SDL_QUIT == sdl->event.type) ||
				(SDL_SCANCODE_ESCAPE == sdl->event.key.keysym.scancode))
			{
				my_free(sdl);
				exit(0);
			}
			else if (SDLK_RETURN == SEKKS && sdl->event.type == SDL_KEYDOWN)
				SSO = NULL;
			else if ((SDLK_p == SEKKS || SDLK_o == SEKKS)
						&& sdl->event.type == SDL_KEYDOWN)
				detail_key(sdl);
			else if (SDLK_g == SEKKS && sdl->event.type == SDL_KEYDOWN)
				swithc_gloss(sdl);
			else if ((SDLK_r == SEKKS || SDLK_f == SEKKS)
						&& sdl->event.type == SDL_KEYDOWN)
				reflection_key(sdl);
			else
				event_2(sdl, &move);
		}
}
