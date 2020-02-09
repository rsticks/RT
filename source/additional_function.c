/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_function.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 15:54:57 by daron             #+#    #+#             */
/*   Updated: 2020/02/09 13:32:45 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			my_free(t_rt *rt)
{

	if (rt->scene.obj_c > 0)
		free(rt->obj_mas);
	if (rt->scene.lgh_c > 0)
		free(rt->lgh_mas);

	SDL_DestroyRenderer(rt->window.render);
	SDL_DestroyWindow(rt->window.window);
	SDL_Quit();
}
