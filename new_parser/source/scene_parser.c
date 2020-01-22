/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 14:22:01 by daron             #+#    #+#             */
/*   Updated: 2020/01/21 17:24:57 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void check_inti_alias(int anti_alias, int str_c)
{
	if ((anti_alias != 1 && anti_alias != 2 && anti_alias != 4 &&
	anti_alias != 8 && anti_alias != 16) || anti_alias < 0)
		kill_error("Wrong format for AntiAliasing", str_c);
}

static void check_inti_maxref(int maxref, int str_c)
{
	if (!(maxref >= 0 && maxref < 15))
		kill_error("Wrong format for reflection count", str_c);
}

static void check_inti_ambiant(float ambiant, int str_c)
{
	if (!(ambiant >= 0.0 && ambiant <= 1.0))
		kill_error("Wrong format for ambiant count", str_c);
}

void scene_parser(t_rt *rt, char *line, int str_c)
{
	while (*line && rt->read_b.str_c >= 1)
	{
		check_tag(rt, line, str_c);
		if (rt->read_b.str_c == 2 && (ft_strequ("antialias", rt->read_b.buff[1])) == 1 && *line == '{')
		{
			line = take_int(line, &rt->window.anti_alias, str_c);
			check_inti_alias(rt->window.anti_alias, str_c);
			rt->window.check[2] += 1;
		}
		else if (rt->read_b.str_c == 2 && (ft_strequ("maxref", rt->read_b.buff[1])) == 1 && *line == '{')
		{
			line = take_int(line, &rt->scene.maxref, str_c);
			check_inti_maxref(rt->scene.maxref, str_c);
			rt->window.check[3] += 1;
		}
		else if (rt->read_b.str_c == 2 && (ft_strequ("ambiant", rt->read_b.buff[1])) == 1 && *line == '{')
		{
			line = take_double(line, &rt->scene.ambient, str_c);
			check_inti_ambiant(rt->scene.ambient, str_c);
			rt->window.check[4] += 1;
		}
		line++;
	}
}