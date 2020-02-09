/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_for_other.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 15:37:42 by daron             #+#    #+#             */
/*   Updated: 2020/02/09 13:10:30 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	detail_key(t_rt *rt)
{
	if (SDLK_p == rt->window.event.key.keysym.sym && rt->window.anti_alias < 64)
		rt->window.anti_alias *= 2;
	else if (SDLK_o == rt->window.event.key.keysym.sym && rt->window.anti_alias > 1)
		rt->window.anti_alias /= 2;
	start_kernel(rt->cl, rt);
}

void	reflection_key(t_rt *rt)
{
	if (SDLK_r == rt->window.event.key.keysym.sym && rt->scene.maxref < 5)
		rt->scene.maxref++;
	else if (SDLK_f == rt->window.event.key.keysym.sym && rt->scene.maxref > 0)
		rt->scene.maxref--;
	start_kernel(rt->cl, rt);
}
