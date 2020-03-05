/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_objs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 17:06:14 by rsticks           #+#    #+#             */
/*   Updated: 2020/03/05 16:41:39 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void				check_objs(t_rt *rt)
{
	int				i;
	int				num_obj;

	num_obj = 0;
	i = 0;
	while (i < rt->scene.obj_c)
	{
		if (rt->obj_mas[i].type == OBJ_FILE_ID)
		{
			rt->data_obj = parsing_obj(rt->obj_mas[0].file_name, num_obj++);
		}
		i++;
	}
}
