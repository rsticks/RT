/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main_f.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 15:49:21 by daron             #+#    #+#             */
/*   Updated: 2020/01/31 15:50:08 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void init_struct(t_rt *rt)
{
	if (!(rt->read_b.buff = (char**)malloc(sizeof(char*) * 2)))
		kill_all("ERROR can't create buffer for reading file <init_struct>");
	rt->read_b.str_c = 0;

	rt->scene.spec = 0.0;
	rt->scene.obj_c = 0;
	rt->scene.lgh_c = 0;
	rt->select_obj = -1;

	rt->obj_head = NULL;
	rt->lgh_head = NULL;

	rt->window.windname = NULL;
	rt->window.effecr_name = NULL;
	rt->window.effect_on = 0;

	ft_memset_int(rt->scene.check, 0, 4);
	ft_memset_int(rt->window.check, 0, 6);
	ft_memset_int(rt->cam.check, 0, 2);
}

void parse_line(t_rt *rt, char *line, int str_c)
{
	if (*line)
	{
		if (rt->read_b.str_c >= 1)
		{
			if (rt->read_b.str_c >= 1 && (ft_strequ(rt->read_b.buff[0], "scene")) > 0)
				scene_parser(rt, line, str_c);
			else if (rt->read_b.str_c >= 1 && (ft_strequ(rt->read_b.buff[0], "camera")) > 0)
				camera_parser(rt, line, str_c);
			else if (rt->read_b.str_c >= 1 && (ft_strequ(rt->read_b.buff[0], "light")) > 0)
				light_parser(rt, line, str_c);
			else if (rt->read_b.str_c >= 1 && (ft_strequ(rt->read_b.buff[0], "object")) > 0)
				object_parser(rt, line, str_c);
			else
				kill_error("Uncorrected object tag" , str_c - 1);
		}
		else
			check_tag(rt, line, str_c);
	}
}

void init_rt(t_rt *rt, char *filename, int str_c)
{
	int fd;
	int read_count;
	char *line;

	if ((fd = open(filename, O_RDWR)) < 0)
		kill_all(ft_strjoin("ERROR: Can't open file ", filename));
	init_struct(rt);
	while ((read_count = get_next_line(fd, &line)) > 0)
	{
		parse_line(rt, line, str_c);
		free(line);
		str_c++;
	}
	close(fd);
	free(rt->read_b.buff);
	cheak_camera(rt);
	cheak_scene(rt);
	cheak_object(rt);
	if (rt->lgh_head != NULL)
		cheak_light(rt);
	cheak_part(rt);






	list_to_mas(rt);
}