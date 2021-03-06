/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_for_other.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzina <kzina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 15:37:42 by daron             #+#    #+#             */
/*   Updated: 2020/03/06 13:46:27 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	detail_key(t_rt *rt)
{
	if (SDLK_p == rt->event.key.keysym.sym && rt->window.anti_alias < 64)
		rt->window.anti_alias *= 2;
	else if (SDLK_o == rt->event.key.keysym.sym
	&& rt->window.anti_alias > 1)
		rt->window.anti_alias /= 2;
	start_kernel(rt->cl, rt);
}

void	reflection_key(t_rt *rt)
{
	if (SDLK_r == rt->event.key.keysym.sym && rt->scene.maxref < 5)
		rt->scene.maxref++;
	else if (SDLK_f == rt->event.key.keysym.sym && rt->scene.maxref > 0)
		rt->scene.maxref--;
	start_kernel(rt->cl, rt);
}
