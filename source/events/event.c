/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzina <kzina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 12:30:37 by daron             #+#    #+#             */
/*   Updated: 2020/03/06 13:46:27 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	create_guide_sides(t_move *move, t_rt *rt)
{
	move->k = vec_sub(&rt->cam.dir, &rt->cam.pos);
	move->k = vec_norm(&move->k);
	move->i = vec_cross(&move->k, &(t_vector){0.0, 1.0, 0.0});
	move->i = vec_norm(&move->i);
	move->j = vec_cross(&move->i, &move->k);
}

static void	event_2(t_rt *rt, t_move *move)
{
	if (rt->event.type == SDL_KEYDOWN && rt->select_obj == -1)
		key_down(rt, move);
	else if (rt->event.type == SDL_KEYDOWN && rt->select_obj != -1)
		key_down_for_object(rt, move);
	else if (rt->event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (rt->event.window.windowID == SDL_GetWindowID(rt->window.window))
			mouse_down(rt);
		else if (rt->event.window.windowID ==
		SDL_GetWindowID(rt->win_menu.window))
			m_down_menu(rt);
	}
}

void		events(t_rt *rt)
{
	t_move	move;

	create_guide_sides(&move, rt);
	while (1)
		while (SDL_PollEvent(&rt->event))
		{
			if ((SDL_QUIT == rt->event.type) ||
				(SDL_SCANCODE_ESCAPE == rt->event.key.keysym.scancode))
				my_free(rt);
			else if (SDLK_RETURN == rt->event.key.keysym.sym
			&& rt->event.type == SDL_KEYDOWN)
				rt->select_obj = -1;
			else if ((SDLK_p == rt->event.key.keysym.sym
			|| SDLK_o == rt->event.key.keysym.sym)
						&& rt->event.type == SDL_KEYDOWN)
				detail_key(rt);
			else if ((SDLK_r == rt->event.key.keysym.sym
			|| SDLK_f == rt->event.key.keysym.sym)
						&& rt->event.type == SDL_KEYDOWN)
				reflection_key(rt);
			else
				event_2(rt, &move);
		}
}
