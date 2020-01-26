/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_for_object.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 14:36:19 by daron             #+#    #+#             */
/*   Updated: 2019/11/28 16:28:01 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	resize_object(t_sdl *sdl)
{
	if (SSO->name != PLANE_ID)
	{
		if (SDLK_KP_1 == SEKKS && SSO->r > 0.5)
			SSO->r -= 1;
		else if (SDLK_KP_2 == SEKKS && SSO->r < 200.0)
			SSO->r += 1;
	}
	start_kernel(sdl->cl, sdl);
}

static void	move_object(t_sdl *sdl, t_move *move)
{
	sdl->dital = 1;
	if (SDLK_w == SEKKS)
		SSO->pos = (t_vector){SSO->pos.x + DELTA * move->j.x,
			SSO->pos.y + DELTA * move->j.y, SSO->pos.z + DELTA * move->j.z};
	else if (SDLK_s == SEKKS)
		SSO->pos = (t_vector){SSO->pos.x - DELTA * move->j.x,
			SSO->pos.y - DELTA * move->j.y, SSO->pos.z - DELTA * move->j.z};
	else if (SDLK_a == SEKKS)
		SSO->pos = (t_vector){SSO->pos.x + DELTA * move->i.x,
			SSO->pos.y + DELTA * move->i.y, SSO->pos.z + DELTA * move->i.z};
	else if (SDLK_d == SEKKS)
		SSO->pos = (t_vector){SSO->pos.x - DELTA * move->i.x,
			SSO->pos.y - DELTA * move->i.y, SSO->pos.z - DELTA * move->i.z};
	else if (SDLK_KP_PLUS == SEKKS)
		SSO->pos = (t_vector){SSO->pos.x + DELTA * move->k.x,
			SSO->pos.y + DELTA * move->k.y, SSO->pos.z + DELTA * move->k.z};
	else if (SDLK_KP_MINUS == SEKKS)
		SSO->pos = (t_vector){SSO->pos.x - DELTA * move->k.x,
			SSO->pos.y - DELTA * move->k.y, SSO->pos.z - DELTA * move->k.z};
	start_kernel(sdl->cl, sdl);
}

static void	rotate_object_1(t_sdl *sdl)
{
	float	tmp_rot;

	if (SDLK_UP == SEKKS && (tmp_rot = SSO->rot.y) < 6000.0)
	{
		SSO->rot.y = SSO->rot.y * cosf(ALPHA) + SSO->rot.z * (-sinf(ALPHA));
		SSO->rot.z = tmp_rot * sinf(ALPHA) + SSO->rot.z * cosf(ALPHA);
	}
	else if (SDLK_PAGEUP == SEKKS && (tmp_rot = SSO->rot.x) < 6000.0)
	{
		SSO->rot.x = SSO->rot.x * cosf(ALPHA) + SSO->rot.y * (-sinf(ALPHA));
		SSO->rot.y = tmp_rot * sinf(ALPHA) + SSO->rot.y * cosf(ALPHA);
	}
	else if (SDLK_PAGEDOWN == SEKKS && (tmp_rot = SSO->rot.x) > -6000.0)
	{
		SSO->rot.x = SSO->rot.x * cosf(-ALPHA) + SSO->rot.y * (-sinf(-ALPHA));
		SSO->rot.y = tmp_rot * sinf(-ALPHA) + SSO->rot.y * cosf(-ALPHA);
	}
	start_kernel(sdl->cl, sdl);
}

static void	rotate_object(t_sdl *sdl)
{
	float	tmp_rot;

	sdl->dital = 1;
	if (SDLK_LEFT == SEKKS && (tmp_rot = SSO->rot.x) < 6000.0)
	{
		SSO->rot.x = SSO->rot.x * cosf(ALPHA) + SSO->rot.z * sinf(ALPHA);
		SSO->rot.z = tmp_rot * (-sinf(ALPHA)) + SSO->rot.z * cosf(ALPHA);
	}
	else if (SDLK_RIGHT == SEKKS && (tmp_rot = SSO->rot.x) > -6000.0)
	{
		SSO->rot.x = SSO->rot.x * cosf(-ALPHA) + SSO->rot.z * sinf(-ALPHA);
		SSO->rot.z = tmp_rot * (-sinf(-ALPHA)) + SSO->rot.z * cosf(-ALPHA);
	}
	else if (SDLK_DOWN == SEKKS && (tmp_rot = SSO->rot.y) > -6000.0)
	{
		SSO->rot.y = SSO->rot.y * cosf(-ALPHA) + SSO->rot.z * (-sinf(-ALPHA));
		SSO->rot.z = tmp_rot * sinf(-ALPHA) + SSO->rot.z * cosf(-ALPHA);
	}
	rotate_object_1(sdl);
}

void		key_down_for_object(t_sdl *sdl, t_move *move)
{
	if (SDLK_KP_1 == SEKKS || SDLK_KP_2 == SEKKS)
		resize_object(sdl);
	else if (SDLK_w == SEKKS || SDLK_s == SEKKS ||
				SDLK_a == SEKKS || SDLK_d == SEKKS ||
				SDLK_KP_PLUS == SEKKS || SDLK_KP_MINUS == SEKKS)
		move_object(sdl, move);
	else if (SDLK_LEFT == SEKKS || SDLK_RIGHT == SEKKS ||
				SDLK_DOWN == SEKKS || SDLK_UP == SEKKS ||
				SDLK_PAGEUP == SEKKS || SDLK_PAGEDOWN == SEKKS)
		rotate_object(sdl);
}
