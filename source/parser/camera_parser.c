/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 14:48:46 by daron             #+#    #+#             */
/*   Updated: 2020/03/06 13:46:27 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		test_camera(t_rt *rt, int str_c)
{
	if (rt->read_b.str_c == 2 && (((ft_strequ("pos", rt->read_b.buff[1])) == 0)
			&& (ft_strequ("dir", rt->read_b.buff[1])) == 0))
		kill_error("Invalid tag fot camera", str_c);
}

static void	check_inti_dir(t_rt *rt, int str_c)
{
	if (rt->cam.dir.x == 0. && rt->cam.dir.y == 0. && rt->cam.dir.z == 0.)
		kill_error("Set other direction ", str_c);
}

void		camera_parser(t_rt *rt, char *line, int str_c)
{
	while (*line && rt->read_b.str_c >= 1)
	{
		check_tag(rt, line, str_c);
		if (rt->read_b.str_c == 2 && (ft_strequ("pos",
				rt->read_b.buff[1])) == 1 && *line == '{')
		{
			line = take_vector(line, &rt->cam.pos, str_c);
			rt->cam.check[0] += 1;
		}
		else if (rt->read_b.str_c == 2 && (ft_strequ("dir",
				rt->read_b.buff[1])) == 1 && *line == '{')
		{
			line = take_vector(line, &rt->cam.dir, str_c);
			check_inti_dir(rt, str_c);
			rt->cam.check[1] += 1;
		}
		test_camera(rt, str_c);
		line++;
	}
	rt->scene.check[0] = 1;
}
