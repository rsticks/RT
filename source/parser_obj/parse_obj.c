/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 18:53:55 by rsticks           #+#    #+#             */
/*   Updated: 2020/03/05 19:34:09 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "pars_obj.h"

static void			init_data(t_parse_obj *data, int num)
{
	data->error = 0;
	data->num_obj = num;
	data->count_vt = 0;
	data->count_v = 0;
	data->count_vn = 0;
	data->count_f = 0;
}

static void			the_end_of_pars_obj(t_parse_obj *data, char *path)
{
	data->max_c = compare_counters(data->count_v,
	data->count_vn, data->count_vt, data->count_f);
	data->d_obj = (t_cl_data_obj*)malloc(sizeof(t_cl_data_obj) * data->max_c);
	close(data->fd);
	data->d_obj[0].num = data->num_obj;
	data->fd = open(path, O_RDONLY);
	while (get_next_line(data->fd, &data->line))
	{
		if (ft_strstr(data->line, "v "))
			parse_v(data);
		else if (ft_strstr(data->line, "vn "))
			parse_vn(data);
		else if (ft_strstr(data->line, "vt "))
			parse_vt(data);
		else if (ft_strstr(data->line, "f "))
			final_parse(data);
		else
			ft_strdel(&data->line);
	}
	close(data->fd);
}

static void			exception_2(u_int32_t *count, t_parse_obj
					*data, char *pattern)
{
	if (*count != 0)
		kill_all("ERROR: wrong .obj file.\n");
	counter(data, pattern, count);
}

static void			exception_check(t_parse_obj *data)
{
	while (data->gnl)
	{
		if (ft_strstr(data->line, "v "))
			exception_2(&data->count_v, data, "v ");
		else if (ft_strstr(data->line, "vn "))
			exception_2(&data->count_vn, data, "vn ");
		else if (ft_strstr(data->line, "vt "))
			exception_2(&data->count_vt, data, "vt ");
		else if (ft_strstr(data->line, "f "))
			exception_2(&data->count_f, data, "f ");
		else
		{
			ft_strdel(&data->line);
			data->gnl = get_next_line(data->fd, &data->line);
		}
	}
}

t_parse_obj			*parsing_obj(char *path, int num)
{
	t_parse_obj		*data;

	if (!(data = (t_parse_obj*)malloc(sizeof(t_parse_obj))))
		kill_all("Can't initialize obj_data\n");
	init_data(data, num);
	data->name = path;
	if (0 > (data->fd = open(path, O_RDWR)))
		kill_all("Can't open obj file\n");
	data->gnl = get_next_line(data->fd, &data->line);
	exception_check(data);
	the_end_of_pars_obj(data, path);
	return (data);
}
