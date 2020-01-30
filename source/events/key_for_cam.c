/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_for_cam.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 15:00:12 by daron             #+#    #+#             */
/*   Updated: 2020/01/30 14:51:36 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	dirate_key_1(t_rt *rt)
{
	float	tmp;

	if (SDLK_UP == rt->window.event.key.keysym.sym && (tmp = rt->cam.pos.y) < 20000)
	{
		rt->cam.pos.y = rt->cam.pos.y * cosf(ALPHA) + rt->cam.pos.z * (-sinf(ALPHA));
		rt->cam.pos.z = tmp * sinf(ALPHA) + rt->cam.pos.z * cosf(ALPHA);
	}
	else if (SDLK_PAGEUP == rt->window.event.key.keysym.sym && (tmp = rt->cam.pos.x) < 2000.0)
	{
		rt->cam.pos.x = rt->cam.pos.x * cosf(ALPHA) + rt->cam.pos.y * (-sinf(ALPHA));
		rt->cam.pos.y = tmp * sinf(ALPHA) + rt->cam.pos.y * cosf(ALPHA);
	}
	else if (SDLK_PAGEDOWN == rt->window.event.key.keysym.sym && (tmp = rt->cam.pos.x) > -2000.0)
	{
		rt->cam.pos.x = rt->cam.pos.x * cosf(ALPHA) + rt->cam.pos.y * (sinf(ALPHA));
		rt->cam.pos.y = tmp * (-sinf(-ALPHA)) + rt->cam.pos.y * cosf(ALPHA);
	}
	start_kernel(rt->cl, rt);
}

static void	dirate_key(t_rt *rt)
{
	float	tmp;

	rt->window.anti_alias = 1;
	if (SDLK_LEFT == rt->window.event.key.keysym.sym && (tmp = rt->cam.pos.x) < 20000)
	{
		rt->cam.pos.x = rt->cam.pos.x * cosf(ALPHA) + rt->cam.pos.z * sinf(ALPHA);
		rt->cam.pos.z = tmp * (-sinf(ALPHA)) + rt->cam.pos.z * cosf(ALPHA);
	}
	else if (SDLK_RIGHT == rt->window.event.key.keysym.sym && (tmp = rt->cam.pos.x) > -20000)
	{
		rt->cam.pos.x = rt->cam.pos.x * cosf(-ALPHA) + rt->cam.pos.z * sinf(-ALPHA);
		rt->cam.pos.z = tmp * (-sinf(-ALPHA)) + rt->cam.pos.z * cosf(-ALPHA);
	}
	else if (SDLK_DOWN == rt->window.event.key.keysym.sym && (tmp = rt->cam.pos.y) > -20000)
	{
		rt->cam.pos.y = rt->cam.pos.y * cosf(-ALPHA) + rt->cam.pos.z * (-sinf(-ALPHA));
		rt->cam.pos.z = tmp * sinf(-ALPHA) + rt->cam.pos.z * cosf(-ALPHA);
	}
	dirate_key_1(rt);
}

static void	move_key_1(t_rt *rt, t_move *move)
{
	if (SDLK_d == rt->window.event.key.keysym.sym)
	{
		rt->cam.dir = (t_vector){rt->cam.dir.x - DELTA * move->i.x,
			rt->cam.dir.y - DELTA * move->i.y, rt->cam.dir.z - DELTA * move->i.z};
		rt->cam.pos = (t_vector){rt->cam.pos.x - DELTA * move->i.x,
			rt->cam.pos.y - DELTA * move->i.y, rt->cam.pos.z - DELTA * move->i.z};
	}
	else if (SDLK_KP_PLUS == rt->window.event.key.keysym.sym)
	{
		rt->cam.dir = (t_vector){rt->cam.dir.x + DELTA * move->k.x,
			rt->cam.dir.y + DELTA * move->k.y, rt->cam.dir.z + DELTA * move->k.z};
		rt->cam.pos = (t_vector){rt->cam.pos.x + DELTA * move->k.x,
			rt->cam.pos.y + DELTA * move->k.y, rt->cam.pos.z + DELTA * move->k.z};
	}
	else if (SDLK_KP_MINUS == rt->window.event.key.keysym.sym)
	{
		rt->cam.dir = (t_vector){rt->cam.dir.x - DELTA * move->k.x,
			rt->cam.dir.y - DELTA * move->k.y, rt->cam.dir.z - DELTA * move->k.z};
		rt->cam.pos = (t_vector){rt->cam.pos.x - DELTA * move->k.x,
			rt->cam.pos.y - DELTA * move->k.y, rt->cam.pos.z - DELTA * move->k.z};
	}
	start_kernel(rt->cl, rt);
}

static void	move_key(t_rt *rt, t_move *move)
{
	rt->window.anti_alias = 1;
	if (SDLK_w == rt->window.event.key.keysym.sym)
	{
		rt->cam.dir = (t_vector){rt->cam.dir.x + DELTA * move->j.x,
			rt->cam.dir.y + DELTA * move->j.y, rt->cam.dir.z + DELTA * move->j.z};
		rt->cam.pos = (t_vector){rt->cam.pos.x + DELTA * move->j.x,
			rt->cam.pos.y + DELTA * move->j.y, rt->cam.pos.z - DELTA * move->j.z};
	}
	else if (SDLK_s == rt->window.event.key.keysym.sym)
	{
		rt->cam.dir = (t_vector){rt->cam.dir.x - DELTA * move->j.x,
			rt->cam.dir.y - DELTA * move->j.y, rt->cam.dir.z - DELTA * move->j.z};
		rt->cam.pos = (t_vector){rt->cam.pos.x - DELTA * move->j.x,
			rt->cam.pos.y - DELTA * move->j.y, rt->cam.pos.z - DELTA * move->j.z};
	}
	else if (SDLK_a == rt->window.event.key.keysym.sym)
	{
		rt->cam.dir = (t_vector){rt->cam.dir.x + DELTA * move->i.x,
			rt->cam.dir.y + DELTA * move->i.y, rt->cam.dir.z + DELTA * move->i.z};
		rt->cam.pos = (t_vector){rt->cam.pos.x + DELTA * move->i.x,
			rt->cam.pos.y + DELTA * move->i.y, rt->cam.pos.z + DELTA * move->i.z};
	}
	move_key_1(rt, move);
}

void		key_down(t_rt *rt, t_move *move)
{
	if (SDLK_w == rt->window.event.key.keysym.sym || SDLK_s == rt->window.event.key.keysym.sym || SDLK_a == rt->window.event.key.keysym.sym || SDLK_d == rt->window.event.key.keysym.sym
		|| SDLK_KP_PLUS == rt->window.event.key.keysym.sym || SDLK_KP_MINUS == rt->window.event.key.keysym.sym)
		move_key(rt, move);
	else if (SDLK_LEFT == rt->window.event.key.keysym.sym || SDLK_RIGHT == rt->window.event.key.keysym.sym || SDLK_DOWN == rt->window.event.key.keysym.sym ||
		SDLK_UP == rt->window.event.key.keysym.sym || SDLK_PAGEUP == rt->window.event.key.keysym.sym || SDLK_PAGEDOWN == rt->window.event.key.keysym.sym)
		dirate_key(rt);
}
