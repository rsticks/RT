/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_for_cam.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 15:00:12 by daron             #+#    #+#             */
/*   Updated: 2019/11/28 16:52:35 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	rotate_key_1(t_sdl *sdl)
{
	float	tmp;

	if (SDLK_UP == SEKKS && (tmp = SC.pos.y) < 20000)
	{
		SC.pos.y = SC.pos.y * cosf(ALPHA) + SC.pos.z * (-sinf(ALPHA));
		SC.pos.z = tmp * sinf(ALPHA) + SC.pos.z * cosf(ALPHA);
	}
	else if (SDLK_PAGEUP == SEKKS && (tmp = SC.pos.x) < 2000.0)
	{
		SC.pos.x = SC.pos.x * cosf(ALPHA) + SC.pos.y * (-sinf(ALPHA));
		SC.pos.y = tmp * sinf(ALPHA) + SC.pos.y * cosf(ALPHA);
	}
	else if (SDLK_PAGEDOWN == SEKKS && (tmp = SC.pos.x) > -2000.0)
	{
		SC.pos.x = SC.pos.x * cosf(ALPHA) + SC.pos.y * (sinf(ALPHA));
		SC.pos.y = tmp * (-sinf(-ALPHA)) + SC.pos.y * cosf(ALPHA);
	}
	start_kernel(sdl->cl, sdl);
}

static void	rotate_key(t_sdl *sdl)
{
	float	tmp;

	sdl->dital = 1;
	if (SDLK_LEFT == SEKKS && (tmp = SC.pos.x) < 20000)
	{
		SC.pos.x = SC.pos.x * cosf(ALPHA) + SC.pos.z * sinf(ALPHA);
		SC.pos.z = tmp * (-sinf(ALPHA)) + SC.pos.z * cosf(ALPHA);
	}
	else if (SDLK_RIGHT == SEKKS && (tmp = SC.pos.x) > -20000)
	{
		SC.pos.x = SC.pos.x * cosf(-ALPHA) + SC.pos.z * sinf(-ALPHA);
		SC.pos.z = tmp * (-sinf(-ALPHA)) + SC.pos.z * cosf(-ALPHA);
	}
	else if (SDLK_DOWN == SEKKS && (tmp = SC.pos.y) > -20000)
	{
		SC.pos.y = SC.pos.y * cosf(-ALPHA) + SC.pos.z * (-sinf(-ALPHA));
		SC.pos.z = tmp * sinf(-ALPHA) + SC.pos.z * cosf(-ALPHA);
	}
	rotate_key_1(sdl);
}

static void	move_key_1(t_sdl *sdl, t_move *move)
{
	if (SDLK_d == SEKKS)
	{
		SC.rot = (t_vector){SC.rot.x - DELTA * move->i.x,
			SC.rot.y - DELTA * move->i.y, SC.rot.z - DELTA * move->i.z};
		SC.pos = (t_vector){SC.pos.x - DELTA * move->i.x,
			SC.pos.y - DELTA * move->i.y, SC.pos.z - DELTA * move->i.z};
	}
	else if (SDLK_KP_PLUS == SEKKS)
	{
		SC.rot = (t_vector){SC.rot.x + DELTA * move->k.x,
			SC.rot.y + DELTA * move->k.y, SC.rot.z + DELTA * move->k.z};
		SC.pos = (t_vector){SC.pos.x + DELTA * move->k.x,
			SC.pos.y + DELTA * move->k.y, SC.pos.z + DELTA * move->k.z};
	}
	else if (SDLK_KP_MINUS == SEKKS)
	{
		SC.rot = (t_vector){SC.rot.x - DELTA * move->k.x,
			SC.rot.y - DELTA * move->k.y, SC.rot.z - DELTA * move->k.z};
		SC.pos = (t_vector){SC.pos.x - DELTA * move->k.x,
			SC.pos.y - DELTA * move->k.y, SC.pos.z - DELTA * move->k.z};
	}
	start_kernel(sdl->cl, sdl);
}

static void	move_key(t_sdl *sdl, t_move *move)
{
	sdl->dital = 1;
	if (SDLK_w == SEKKS)
	{
		SC.rot = (t_vector){SC.rot.x + DELTA * move->j.x,
			SC.rot.y + DELTA * move->j.y, SC.rot.z + DELTA * move->j.z};
		SC.pos = (t_vector){SC.pos.x + DELTA * move->j.x,
			SC.pos.y + DELTA * move->j.y, SC.pos.z - DELTA * move->j.z};
	}
	else if (SDLK_s == SEKKS)
	{
		SC.rot = (t_vector){SC.rot.x - DELTA * move->j.x,
			SC.rot.y - DELTA * move->j.y, SC.rot.z - DELTA * move->j.z};
		SC.pos = (t_vector){SC.pos.x - DELTA * move->j.x,
			SC.pos.y - DELTA * move->j.y, SC.pos.z - DELTA * move->j.z};
	}
	else if (SDLK_a == SEKKS)
	{
		SC.rot = (t_vector){SC.rot.x + DELTA * move->i.x,
			SC.rot.y + DELTA * move->i.y, SC.rot.z + DELTA * move->i.z};
		SC.pos = (t_vector){SC.pos.x + DELTA * move->i.x,
			SC.pos.y + DELTA * move->i.y, SC.pos.z + DELTA * move->i.z};
	}
	move_key_1(sdl, move);
}

void		key_down(t_sdl *sdl, t_move *move)
{
	if (SDLK_w == SEKKS || SDLK_s == SEKKS || SDLK_a == SEKKS || SDLK_d == SEKKS
		|| SDLK_KP_PLUS == SEKKS || SDLK_KP_MINUS == SEKKS)
		move_key(sdl, move);
	else if (SDLK_LEFT == SEKKS || SDLK_RIGHT == SEKKS || SDLK_DOWN == SEKKS ||
		SDLK_UP == SEKKS || SDLK_PAGEUP == SEKKS || SDLK_PAGEDOWN == SEKKS)
		rotate_key(sdl);
}
