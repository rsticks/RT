/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_parser_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 15:34:55 by daron             #+#    #+#             */
/*   Updated: 2020/03/02 15:44:45 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	test_object(t_rt *rt, int str_c)
{
	if (rt->read_b.str_c == 2 && (
			(ft_strequ("reflect", rt->read_b.buff[1])) == 0
			&& (ft_strequ("refract", rt->read_b.buff[1])) == 0
			&& (ft_strequ("type", rt->read_b.buff[1])) == 0
			&& (ft_strequ("dir", rt->read_b.buff[1])) == 0
			&& (ft_strequ("rgb", rt->read_b.buff[1])) == 0
			&& (ft_strequ("spec", rt->read_b.buff[1])) == 0
			&& (ft_strequ("texture", rt->read_b.buff[1])) == 0
			&& (ft_strequ("limit", rt->read_b.buff[1])) == 0
			&& (ft_strequ("pos", rt->read_b.buff[1])) == 0
			&& (ft_strequ("file_addr", rt->read_b.buff[1])) == 0
			&& (ft_strequ("contruction", rt->read_b.buff[1])) == 0
			&& (ft_strequ("torus_R", rt->read_b.buff[1])) == 0
			&& (ft_strequ("radius", rt->read_b.buff[1])) == 0))
		kill_error("Invalid tag fot object", str_c);
}

void	check_inti_obj_type(t_rt *rt, int str_c)
{
	if ((ft_strnequ("sphere", rt->obj_cur->obj_name, 6)) == 1)
		rt->obj_cur->type = SPHERE_ID;
	else if ((ft_strnequ("cylinder", rt->obj_cur->obj_name, 8)) == 1)
		rt->obj_cur->type = CYLINDER_ID;
	else if ((ft_strnequ("cone", rt->obj_cur->obj_name, 4)) == 1)
		rt->obj_cur->type = CONE_ID;
	else if ((ft_strnequ("plane", rt->obj_cur->obj_name, 5)) == 1)
		rt->obj_cur->type = PLANE_ID;
	else if ((ft_strnequ("object_f", rt->obj_cur->obj_name, 8)) == 1)
		rt->obj_cur->type = OBJ_FILE_ID;
	else if ((ft_strnequ("paraboloid", rt->obj_cur->obj_name, 8)) == 1)
		rt->obj_cur->type = PARABOLOID_ID;
	else if ((ft_strnequ("disk", rt->obj_cur->obj_name, 8)) == 1)
		rt->obj_cur->type = DISK_ID;
	else if ((ft_strnequ("torus", rt->obj_cur->obj_name, 8)) == 1)
		rt->obj_cur->type = TORUS_ID;
	else
		kill_error("uncorrected object type", str_c);
}
