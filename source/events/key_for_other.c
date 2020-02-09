/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_for_other.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 15:37:42 by daron             #+#    #+#             */
/*   Updated: 2020/02/09 15:36:22 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	detail_key(t_sdl *sdl)
{
	if (SDLK_p == SEKKS && sdl->dital < 64)
		sdl->dital *= 2;
	else if (SDLK_o == SEKKS && sdl->dital > 1)
		sdl->dital /= 2;
	start_kernel(sdl->cl, sdl);
}

void	swithc_gloss(t_sdl *sdl)
{
	sdl->gloss_activ = (sdl->gloss_activ == 0) ? 1 : 0;
	start_kernel(sdl->cl, sdl);
}

void	reflection_key(t_sdl *sdl)
{
	if (SDLK_r == SEKKS && sdl->reflect_count < 5)
		sdl->reflect_count++;
	else if (SDLK_f == SEKKS && sdl->reflect_count > 0)
		sdl->reflect_count--;
	start_kernel(sdl->cl, sdl);
}

void	swithc_pref(t_sdl *sdl)
{
	sdl->pref = (sdl->pref == 0) ? 1 : 0;
	start_kernel(sdl->cl, sdl);
}
