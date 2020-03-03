/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 14:22:01 by daron             #+#    #+#             */
/*   Updated: 2020/03/03 17:16:03 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		test_scene(t_rt *rt, int str_c)
{
	if (rt->read_b.str_c == 2 && (((ft_strequ("name", rt->read_b.buff[1])) == 0)
	&& (ft_strequ("res", rt->read_b.buff[1])) == 0
	&& ((ft_strequ("antialias", rt->read_b.buff[1])) == 0)
	&& (ft_strequ("maxref", rt->read_b.buff[1])) == 0
	&& (ft_strequ("ambiant", rt->read_b.buff[1])) == 0
	&& (ft_strequ("skybox", rt->read_b.buff[1])) == 0
	&& (ft_strequ("effect", rt->read_b.buff[1])) == 0))
		kill_error("Invalid tag fot scene", str_c);
}

static char	*scene_parser_2(t_rt *rt, char *line, int str_c)
{
	if (rt->read_b.str_c == 2 && (ft_strequ("ambiant",
			rt->read_b.buff[1])) == 1 && *line == '{')
	{
		line = take_double(line, &rt->scene.ambient, str_c);
		check_inti_ambiant(rt->scene.ambient, str_c);
		rt->window.check[4] += 1;
	}
	if (rt->read_b.str_c == 2 && (ft_strequ("skybox",
			rt->read_b.buff[1])) == 1 && *line == '{')
	{
		line = take_skybox(line, &rt->scene.skybox_id, str_c);
		rt->scene.check[4] += 1;
	}
	return (line);
}

static char	*scene_parser_1(t_rt *rt, char *line, int str_c)
{
	if (rt->read_b.str_c == 2 && (ft_strequ("name",
			rt->read_b.buff[1])) == 1 && *line == '{')
	{
		line = take_word(line, &rt->window.windname, str_c);
		rt->window.check[0] += 1;
	}
	else if (rt->read_b.str_c == 2 && (ft_strequ("effect",
			rt->read_b.buff[1])) == 1 && *line == '{')
	{
		line = take_word(line, &rt->window.effecr_name, str_c);
		check_inti_effect(rt, str_c);
		rt->window.check[5] += 1;
	}
	else if (rt->read_b.str_c == 2 && (ft_strequ("res",
			rt->read_b.buff[1])) == 1 && *line == '{')
	{
		line = take_res(line, rt->window.size, str_c);
		check_inti_res(rt, str_c);
		rt->window.check[1] += 1;
	}
	return (line);
}

void		scene_parser(t_rt *rt, char *line, int str_c)
{
	while (*line && rt->read_b.str_c >= 1)
	{
		check_tag(rt, line, str_c);
		if (rt->read_b.str_c == 2 && (ft_strequ("antialias",
				rt->read_b.buff[1])) == 1 && *line == '{')
		{
			line = take_int(line, &rt->window.anti_alias, str_c);
			check_inti_alias(rt->window.anti_alias, str_c);
			rt->window.check[2] += 1;
		}
		else if (rt->read_b.str_c == 2 && (ft_strequ("maxref",
				rt->read_b.buff[1])) == 1 && *line == '{')
		{
			line = take_int(line, &rt->scene.maxref, str_c);
			check_inti_maxref(rt->scene.maxref, str_c);
			rt->window.check[3] += 1;
		}
		line = scene_parser_1(rt, line, str_c);
		line = scene_parser_2(rt, line, str_c);
		test_scene(rt, str_c);
		line++;
	}
	rt->scene.check[2] = 1;
}
