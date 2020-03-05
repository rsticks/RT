/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 18:53:55 by rsticks           #+#    #+#             */
/*   Updated: 2020/03/05 18:35:38 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "pars_obj.h"

static char			*final_parse_2(t_parse_obj *data, u_int32_t count)
{
	char			*c;

	c = data->line;
	c = while_not_digit(c);
	c = f_pars_x(data, c, count);
	c = next_digit(c);
	c = f_pars_y(data, c, count);
	c = next_digit(c);
	c = f_pars_z(data, c, count);
	return (c);
}

void				final_parse(t_parse_obj *data)
{
	char			*c;
	int				error;
	u_int32_t		count;

	error = 0;
	count = 0;
	if (!(data->f = (t_list_f*)malloc(sizeof(t_list_f) * data->count_f)))
		kill_all("Can't alloc memmory to data->obj\n");
	while (count != data->count_f)
	{
		if (ft_strstr(data->line, "f "))
		{
			c = final_parse_2(data, count);
			while (*c != ' ' && *c != '\0')
				c++;
			while (!(ftft_isdigit(*c)) && *c != '\0')
				c++;
			if (*c != '\0')
				kill_all("Error: .obj not triangulate");
		}
		if (count != (data->count_f - 1))
		{
			free(data->line);
			get_next_line(data->fd, &data->line);
		}
		count++;
	}
	free(data->line);
}

static void			init_data(t_parse_obj *data, int num)
{
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
			free(data->line);
	}
	close(data->fd);
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
	while (data->gnl)
	{
		if (ft_strstr(data->line, "v "))
			counter(data, "v ", &data->count_v);
		else if (ft_strstr(data->line, "vn "))
			counter(data, "vn ", &data->count_vn);
		else if (ft_strstr(data->line, "vt "))
			counter(data, "vt ", &data->count_vt);
		else if (ft_strstr(data->line, "f "))
			counter(data, "f ", &data->count_f);
		else
		{
			free(data->line);
			data->gnl = get_next_line(data->fd, &data->line);
		}
	}
	the_end_of_pars_obj(data, path);
	return (data);
}
