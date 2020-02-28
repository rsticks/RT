/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 17:58:47 by daron             #+#    #+#             */
/*   Updated: 2020/02/26 16:12:09 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void test_object(t_rt *rt, int str_c)
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
			&& (ft_strequ("radius", rt->read_b.buff[1])) == 0))
		kill_error("Invalid tag fot object", str_c);
}

static void check_inti_reflection(t_rt *rt, int str_c)
{
	if (rt->obj_cur->coef_refl < 0.0)
		kill_error("Wrong reflection coefficient" , str_c);
}

static void check_inti_radius(t_rt *rt, int str_c)
{
	if (!(rt->obj_cur->radius >= 0.1 && rt->obj_cur->radius <= 100.0))
		kill_error("Uncorrected radius" , str_c);
}

static void check_inti_texture(t_rt *rt, int str_c)
{
	int fd;

	fd = 0;
	//if (rt->obj_cur->text_on == 1 && (fd = open(rt->obj_cur->texture , O_RDWR)) < 0)
	//	kill_error(ft_strjoin("Can't open file ", rt->obj_cur->texture), str_c);
	//else if (rt->obj_cur->obj_on && (fd = open(rt->obj_cur->obj_name , O_RDWR)) < 0)
	//	kill_error(ft_strjoin("Can't open file ", rt->obj_cur->file_name), str_c);
	close(fd);
}

void check_inti_obj_type(t_rt *rt, int str_c)
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
	else
		kill_error("uncorrected object type" , str_c);
}

void object_parser(t_rt *rt, char *line, int str_c)
{
	while (*line && rt->read_b.str_c >= 1) {
		check_tag(rt, line, str_c);
		if (rt->read_b.str_c == 2 && (ft_strequ("reflect", rt->read_b.buff[1])) == 1 && *line == '{') {
			line = take_refl(line, rt->obj_cur, str_c);
			check_inti_reflection(rt, str_c);
			rt->obj_cur->check[5] += 1;
		}
		else if (rt->read_b.str_c == 2 && (ft_strequ("refract", rt->read_b.buff[1])) == 1 && *line == '{') {
			line = take_refraction(line, rt->obj_cur, str_c);
			rt->obj_cur->check[6] += 1;
		}
		else if (rt->read_b.str_c == 2 && (ft_strequ("type", rt->read_b.buff[1])) == 1 && *line == '{') {
			line = take_word(line, &(rt->obj_cur->obj_name), str_c);
			check_inti_obj_type(rt, str_c);
			rt->obj_cur->check[0] += 1;
		}
		else if (rt->read_b.str_c == 2 && (ft_strequ("dir", rt->read_b.buff[1])) == 1 && *line == '{') {
			line = take_vector(line, &rt->obj_cur->dir, str_c);
			rt->obj_cur->check[2] += 1;
		}
		else if (rt->read_b.str_c == 2 && (ft_strequ("pos", rt->read_b.buff[1])) == 1 && *line == '{') {
			line = take_vector(line, &rt->obj_cur->pos, str_c);
			rt->obj_cur->check[1] += 1;
		}
		else if (rt->read_b.str_c == 2 && (ft_strequ("rgb", rt->read_b.buff[1])) == 1 && *line == '{') {
			line = take_rgb(line, &rt->obj_cur->rgb, str_c);
			check_inti_rgb(rt, str_c);
			rt->obj_cur->check[3] += 1;
		}
		else if (rt->read_b.str_c == 2 && (ft_strequ("radius", rt->read_b.buff[1])) == 1 && *line == '{') {
			line = take_double(line, &rt->obj_cur->radius, str_c);
			check_inti_radius(rt, str_c);
			rt->obj_cur->check[4] += 1;
		}
		else if (rt->read_b.str_c == 2 && (ft_strequ("spec", rt->read_b.buff[1])) == 1 && *line == '{') {
			line = take_on_off(line, &rt->obj_cur->spec, str_c);
			rt->obj_cur->check[7] += 1;
		}
		else if (rt->read_b.str_c == 2 && (ft_strequ("limit", rt->read_b.buff[1])) == 1 && *line == '{') {
			line = take_double(line, &rt->obj_cur->limit, str_c);
			rt->obj_cur->check[9] += 1;
		}
		else if (rt->read_b.str_c == 2 && (ft_strequ("texture", rt->read_b.buff[1])) == 1 && *line == '{') {
			line = take_texture(line, rt->obj_cur, "img", str_c);
			check_inti_texture(rt, str_c);
			rt->obj_cur->check[8] += 1;
		}
		else if (rt->read_b.str_c == 2 && (ft_strequ("file_addr", rt->read_b.buff[1])) == 1 && *line == '{') {
			line = take_texture(line, rt->obj_cur, "obj", str_c);
			check_inti_texture(rt, str_c);
			rt->obj_cur->check[10] += 1;
		}
		test_object(rt, str_c);
		line++;
	}
	rt->scene.check[3] = 1;
}