/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_function.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 15:54:57 by daron             #+#    #+#             */
/*   Updated: 2020/03/06 13:46:26 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			my_free(t_rt *rt)
{
	free(rt->obj_mas);
	if (rt->scene.lgh_c)
		free(rt->lgh_mas);
	SDL_DestroyRenderer(rt->window.render);
	SDL_DestroyWindow(rt->window.window);
	SDL_Quit();
	exit(0);
}
