/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 15:44:52 by daron             #+#    #+#             */
/*   Updated: 2020/02/09 13:10:30 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void test_light(t_rt *rt, int str_c)
{
	if (rt->read_b.str_c == 2 && (((ft_strequ("pos", rt->read_b.buff[1])) == 0)
								  && (ft_strequ("rgb", rt->read_b.buff[1])) == 0))
		kill_error("Invalid tag fot light", str_c);
}

void check_inti_rgb(t_rt *rt, int str_c)
{
	if (!(rt->lgh_cur->rgb.r >= 0 && rt->lgh_cur->rgb.r <= 255))
		kill_error("Wrong red color component", str_c);
	else if (!(rt->lgh_cur->rgb.g >= 0 && rt->lgh_cur->rgb.g <= 255))
		kill_error("Wrong green color component", str_c);
	else if (!(rt->lgh_cur->rgb.b >= 0 && rt->lgh_cur->rgb.b <= 255))
		kill_error("Wrong blue color component", str_c);
}

void light_parser(t_rt *rt, char *line, int str_c)
{
	while (*line && rt->read_b.str_c >= 1)
	{
		check_tag(rt, line, str_c);
		if (rt->read_b.str_c == 2 && (ft_strequ("pos", rt->read_b.buff[1])) == 1 && *line == '{')
		{
			line = take_vector(line, &rt->lgh_cur->pos, str_c);
			rt->lgh_cur->check[0] += 1;
		}
		else if (rt->read_b.str_c == 2 && (ft_strequ("rgb", rt->read_b.buff[1])) == 1 && *line == '{')
		{
			line = take_rgb(line, &rt->lgh_cur->rgb, str_c);
			check_inti_rgb(rt, str_c);
			rt->lgh_cur->check[1] += 1;
		}
		test_light(rt, str_c);
		line++;
	}
	rt->scene.check[1] = 1;
}