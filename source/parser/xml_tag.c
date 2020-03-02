/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_tag.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 14:09:27 by daron             #+#    #+#             */
/*   Updated: 2020/03/02 14:55:12 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void open_tag(t_rt *rt, char *line, int str_c)
{
	int len;

	if ((ft_strchr(line, '>')) == NULL)
		kill_error("Uncorrected tag.", str_c);
	len = 0;
	while(line[len] != '>')
		len++;
	rt->read_b.buff[rt->read_b.str_c] = ft_strsub(line, 0, len);
	create_list(rt, rt->read_b.buff[rt->read_b.str_c]);
	rt->read_b.str_c++;
	if (rt->read_b.str_c > 2)
		kill_error("Too many tags.", str_c);
}

static void close_tag(t_rt *rt, char *line, int str_c)
{
	if ((ft_strchr(line, '>')) == NULL)
		kill_error("Uncomplited tag.", str_c);
	if (ft_strnequ(line, rt->read_b.buff[rt->read_b.str_c - 1], ft_strlen(rt->read_b.buff[rt->read_b.str_c - 1])) == 0)
		kill_error("Сlosing tag does not match opening.", str_c);
	//нужно поставить сюда проверки не забудь про ето

	free(rt->read_b.buff[rt->read_b.str_c - 1]);
	rt->read_b.str_c--;
}

void check_tag(t_rt *rt, char *line, int str_c)
{
	if (rt->read_b.str_c == 0)
		if (!(line = ft_strchr(line, '<')))
			kill_error("Uncorrected scene.", str_c);

	if (*line == '<')
	{
		line++;
		if (*line == '/')
		{
			if (rt->read_b.str_c == 0)
				kill_error("Uncorrected tag.", str_c);
			line++;
			close_tag(rt, line, str_c);
		}
		else
			open_tag(rt, line, str_c);
	}
}
