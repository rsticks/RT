/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_objs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzina <kzina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 17:06:14 by rsticks           #+#    #+#             */
/*   Updated: 2020/03/06 13:46:26 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void				check_objs(t_rt *rt)
{
	int				i;
	int				num_obj;
	char			kostil;

	kostil = 0;
	num_obj = 0;
	i = 0;
	while (i < rt->scene.obj_c)
	{
		if (rt->obj_mas[i].type == OBJ_FILE_ID)
		{
			kostil = 1;
			rt->data_obj = parsing_obj(rt->obj_mas[0].file_name, num_obj++);
		}
		i++;
	}
	if (kostil == 0)
	{
		if (!(rt->data_obj = (t_parse_obj*)malloc(sizeof(t_parse_obj))))
			kill_all("Can't initialize obj_data\n");
		rt->data_obj->max_c = 0;
	}
}
