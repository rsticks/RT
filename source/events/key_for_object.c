/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_for_object.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 14:36:19 by daron             #+#    #+#             */
/*   Updated: 2020/03/05 17:12:54 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	resize_object(t_rt *rt)
{
	if (rt->obj_mas[rt->select_obj].type != PLANE_ID)
	{
		if (SDLK_KP_1 == rt->window.event.key.keysym.sym
		&& rt->obj_mas[rt->select_obj].radius > 0.5)
			rt->obj_mas[rt->select_obj].radius -= 1;
		else if (SDLK_KP_2 == rt->window.event.key.keysym.sym
		&& rt->obj_mas[rt->select_obj].radius < 200.0)
			rt->obj_mas[rt->select_obj].radius += 1;
	}
	start_kernel(rt->cl, rt);
}

static void	move_object(t_rt *rt, t_move *move)
{
	rt->window.anti_alias = 1;
	if (SDLK_w == rt->window.event.key.keysym.sym)
		ROP = (t_vector){ROP.x + DELTA * move->j.x, ROP.y + DELTA * move->j.y,
		ROP.z + DELTA * move->j.z};
	else if (SDLK_s == rt->window.event.key.keysym.sym)
		ROP = (t_vector){ROP.x - DELTA * move->j.x, ROP.y - DELTA * move->j.y,
		ROP.z - DELTA * move->j.z};
	else if (SDLK_a == rt->window.event.key.keysym.sym)
		ROP = (t_vector){ROP.x + DELTA * move->i.x, ROP.y + DELTA * move->i.y,
		ROP.z + DELTA * move->i.z};
	else if (SDLK_d == rt->window.event.key.keysym.sym)
		ROP = (t_vector){ROP.x - DELTA * move->i.x, ROP.y - DELTA * move->i.y,
				ROP.z - DELTA * move->i.z};
	else if (SDLK_KP_PLUS == rt->window.event.key.keysym.sym)
		ROP = (t_vector){ ROP.x + DELTA * move->k.x, ROP.y + DELTA * move->k.y,
		ROP.z + DELTA * move->k.z};
	else if (SDLK_KP_MINUS == rt->window.event.key.keysym.sym)
		ROP = (t_vector){ROP.x - DELTA * move->k.x, ROP.y - DELTA * move->k.y,
				ROP.z - DELTA * move->k.z};
	start_kernel(rt->cl, rt);
}

static void	dirate_object_1(t_rt *rt)
{
	float	tmp_dir;

	if (SDLK_UP == rt->window.event.key.keysym.sym
	&& (tmp_dir = ROD.y) < 6000.0)
	{
		ROD.y = ROD.y * cosf(ALPHA) + ROD.z * (-sinf(ALPHA));
		ROD.z = tmp_dir * sinf(ALPHA) + ROD.z * cosf(ALPHA);
	}
	else if (SDLK_PAGEUP == rt->window.event.key.keysym.sym
	&& (tmp_dir = ROD.x) < 6000.0)
	{
		ROD.x = ROD.x * cosf(ALPHA) + ROD.y * (-sinf(ALPHA));
		ROD.y = tmp_dir * sinf(ALPHA) + ROD.y * cosf(ALPHA);
	}
	else if (SDLK_PAGEDOWN == rt->window.event.key.keysym.sym
	&& (tmp_dir = ROD.x) > -6000.0)
	{
		ROD.x = ROD.x * cosf(-ALPHA) + ROD.y * (-sinf(-ALPHA));
		ROD.y = tmp_dir * sinf(-ALPHA) + ROD.y * cosf(-ALPHA);
	}
	start_kernel(rt->cl, rt);
}

static void	dirate_object(t_rt *rt)
{
	float	tmp_dir;

	rt->window.anti_alias = 1;
	if (SDLK_LEFT == rt->window.event.key.keysym.sym
	&& (tmp_dir = ROD.x) < 6000.0)
	{
		ROD.x = ROD.x * cosf(ALPHA) + ROD.z * sinf(ALPHA);
		ROD.z = tmp_dir * (-sinf(ALPHA)) + ROD.z * cosf(ALPHA);
	}
	else if (SDLK_RIGHT == rt->window.event.key.keysym.sym
	&& (tmp_dir = ROD.x) > -6000.0)
	{
		ROD.x = ROD.x * cosf(-ALPHA) + ROD.z * sinf(-ALPHA);
		ROD.z = tmp_dir * (-sinf(-ALPHA)) + ROD.z * cosf(-ALPHA);
	}
	else if (SDLK_DOWN == rt->window.event.key.keysym.sym
	&& (tmp_dir = ROD.y) > -6000.0)
	{
		ROD.y = ROD.y * cosf(-ALPHA) + ROD.z * (-sinf(-ALPHA));
		ROD.z = tmp_dir * sinf(-ALPHA) + ROD.z * cosf(-ALPHA);
	}
	dirate_object_1(rt);
}

void		key_down_for_object(t_rt *rt, t_move *move)
{
	if (SDLK_KP_1 == rt->window.event.key.keysym.sym
	|| SDLK_KP_2 == rt->window.event.key.keysym.sym)
		resize_object(rt);
	else if (SDLK_w == rt->window.event.key.keysym.sym
	|| SDLK_s == rt->window.event.key.keysym.sym
	|| SDLK_a == rt->window.event.key.keysym.sym
	|| SDLK_d == rt->window.event.key.keysym.sym
	|| SDLK_KP_PLUS == rt->window.event.key.keysym.sym
	|| SDLK_KP_MINUS == rt->window.event.key.keysym.sym)
		move_object(rt, move);
	else if (SDLK_LEFT == rt->window.event.key.keysym.sym
	|| SDLK_RIGHT == rt->window.event.key.keysym.sym
	|| SDLK_DOWN == rt->window.event.key.keysym.sym
	|| SDLK_UP == rt->window.event.key.keysym.sym
	|| SDLK_PAGEUP == rt->window.event.key.keysym.sym
	|| SDLK_PAGEDOWN == rt->window.event.key.keysym.sym)
		dirate_object(rt);
}
