/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 17:58:47 by daron             #+#    #+#             */
/*   Updated: 2020/03/05 16:41:39 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static char	*object_parser_4(t_rt *rt, char *line, int str_c)
{
	if (rt->read_b.str_c == 2 && (ft_strequ("contruction",
			rt->read_b.buff[1])) == 1 && *line == '{')
	{
		line = take_construction(line, &rt->obj_cur->contruction_id, str_c);
		rt->obj_cur->check[12] += 1;
	}
	else if (rt->read_b.str_c == 2 && (ft_strequ("type",
			rt->read_b.buff[1])) == 1 && *line == '{')
	{
		line = take_word(line, &(rt->obj_cur->obj_name), str_c);
		check_inti_obj_type(rt, str_c);
		rt->obj_cur->check[0] += 1;
	}
	return (line);
}

static char	*object_parser_3(t_rt *rt, char *line, int str_c)
{
	if (rt->read_b.str_c == 2 && (ft_strequ("radius",
			rt->read_b.buff[1])) == 1 && *line == '{')
	{
		line = take_double(line, &rt->obj_cur->radius, str_c);
		check_inti_radius(rt, str_c);
		rt->obj_cur->check[4] += 1;
	}
	else if (rt->read_b.str_c == 2 && (ft_strequ("torus_R",
			rt->read_b.buff[1])) == 1 && *line == '{')
	{
		line = take_double(line, &rt->obj_cur->torus_r, str_c);
		check_inti_radius(rt, str_c);
		rt->obj_cur->check[11] += 1;
	}
	else if (rt->read_b.str_c == 2 && (ft_strequ("spec",
			rt->read_b.buff[1])) == 1 && *line == '{')
	{
		line = take_on_off(line, &rt->obj_cur->spec, str_c);
		rt->obj_cur->check[7] += 1;
	}
	return (line);
}

static char	*object_parser_2(t_rt *rt, char *line, int str_c)
{
	if (rt->read_b.str_c == 2 && (ft_strequ("limit",
			rt->read_b.buff[1])) == 1 && *line == '{')
	{
		line = take_double(line, &rt->obj_cur->limit, str_c);
		rt->obj_cur->check[9] += 1;
	}
	else if (rt->read_b.str_c == 2 && (ft_strequ("texture",
			rt->read_b.buff[1])) == 1 && *line == '{')
	{
		line = take_texture(line, rt->obj_cur, "img", str_c);
		rt->obj_cur->check[8] += 1;
	}
	else if (rt->read_b.str_c == 2 && (ft_strequ("file_addr",
			rt->read_b.buff[1])) == 1 && *line == '{')
	{
		line = take_texture(line, rt->obj_cur, "obj", str_c);
		rt->obj_cur->check[10] += 1;
	}
	return (line);
}

static char	*object_parser_1(t_rt *rt, char *line, int str_c)
{
	if (rt->read_b.str_c == 2 && (ft_strequ("dir",
			rt->read_b.buff[1])) == 1 && *line == '{')
	{
		line = take_vector(line, &rt->obj_cur->dir, str_c);
		check_inti_dir_obj(rt, str_c);
		rt->obj_cur->check[2] += 1;
	}
	else if (rt->read_b.str_c == 2 && (ft_strequ("pos",
			rt->read_b.buff[1])) == 1 && *line == '{')
	{
		line = take_vector(line, &rt->obj_cur->pos, str_c);
		rt->obj_cur->check[1] += 1;
	}
	else if (rt->read_b.str_c == 2 && (ft_strequ("rgb",
			rt->read_b.buff[1])) == 1 && *line == '{')
	{
		line = take_rgb(line, &rt->obj_cur->rgb, str_c);
		check_inti_obj_rgb(rt, str_c);
		rt->obj_cur->check[3] += 1;
	}
	return (line);
}

void		object_parser(t_rt *rt, char *line, int str_c)
{
	while (*line && rt->read_b.str_c >= 1)
	{
		check_tag(rt, line, str_c);
		if (rt->read_b.str_c == 2 && (ft_strequ("reflect",
				rt->read_b.buff[1])) == 1 && *line == '{')
		{
			line = take_refl(line, rt->obj_cur, str_c);
			check_inti_reflection(rt, str_c);
			rt->obj_cur->check[5] += 1;
		}
		else if (rt->read_b.str_c == 2 && (ft_strequ("refract",
				rt->read_b.buff[1])) == 1 && *line == '{')
		{
			line = take_refraction(line, rt->obj_cur, str_c);
			check_inti_refraction(rt, str_c);
			rt->obj_cur->check[6] += 1;
		}
		line = object_parser_1(rt, line, str_c);
		line = object_parser_2(rt, line, str_c);
		line = object_parser_3(rt, line, str_c);
		line = object_parser_4(rt, line, str_c);
		test_object(rt, str_c);
		line++;
	}
	rt->scene.check[3] = 1;
}
