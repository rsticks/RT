/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_mas_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 15:16:45 by daron             #+#    #+#             */
/*   Updated: 2020/03/02 15:20:12 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	list_to_mas(t_rt *rt)
{
	if (!(rt->obj_mas = (t_obj*)malloc(sizeof(t_obj) * rt->scene.obj_c)))
		kill_all("ERROR: malloc error <list_to_mas>");
	copy_obj(rt);
	delete_obj_list(rt);
	if (rt->scene.lgh_c > 0)
	{
		if (!(rt->lgh_mas = (t_light*)malloc(sizeof(t_light)
				* rt->scene.lgh_c)))
			kill_all("ERROR: malloc error <list_to_mas>");
		copy_light(rt);
		delete_light_list(rt);
	}
}
