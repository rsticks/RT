/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 17:06:59 by daron             #+#    #+#             */
/*   Updated: 2020/01/20 14:33:12 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				kill_all(char *message)
{
	ft_putstr(message);
	exit(1);
}

void kill_error(char *message, int string_number)
{
	// Message: ERROR: {message}  String number {string_number}
	kill_all(ft_strjoin_del(ft_strjoin(
			ft_strjoin("ERROR: ", message),
			" String number "), ft_itoa(string_number), 'R'));
}

void init_struct(t_rt *rt)
{
	if (!(rt->read_b.buff = (char**)malloc(sizeof(char*) * 2)))
		kill_all("ERROR can't create buffer for reading file <init_struct>");
	rt->read_b.str_c = 0;

	rt->scene.spec = 0.0;
	rt->scene.reflection_c = 0;
	rt->scene.obj_c = 0;
	rt->scene.lgh_c = 0;

	rt->obj_head = NULL;
	rt->lgh_head = NULL;

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
		//printf("%d %s\n", str_c, line);
		free(line);
		str_c++;
	}
}

int main(int argc, char **argv)
{
	t_rt rt;

	if (argc != 2)
		ft_putendl("usage: ./RT input_file");
	else
		init_rt(&rt, argv[1], 1);
	return (0);
}