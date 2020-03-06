/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseings.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 15:38:37 by rsticks           #+#    #+#             */
/*   Updated: 2020/03/05 18:57:28 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "pars_obj.h"

static t_vector	pod_parser(t_parse_obj *data, char *c)
{
	t_vector	v;

	c = data->line;
	c = while_not_digit(c);
	v.x = ft_atof(c);
	c = next_digit(c);
	v.y = ft_atof(c);
	c = next_digit(c);
	v.z = ft_atof(c);
	return (v);
}

void			parse_v(t_parse_obj *data)
{
	char		*c;
	u_int32_t	count;
	t_vector	v;

	count = 0;
	if (!(data->v = (cl_float3*)malloc(sizeof(cl_float3) * data->count_v)))
		kill_all("Can't alloc memmory to data->v\n");
	while (count != data->count_v)
	{
		if (ft_strstr(data->line, "v "))
		{
			c = NULL;
			v = pod_parser(data, c);
			data->d_obj[count].v = (cl_float3){{v.x, v.y, v.z}};
		}
		if (count != (data->count_v - 1))
		{
			ft_strdel(&data->line);
			get_next_line(data->fd, &data->line);
		}
		count++;
	}
	ft_strdel(&data->line);
}

void			parse_vt(t_parse_obj *data)
{
	char		*c;
	u_int32_t	count;

	count = 0;
	if (!(data->vt = (t_list_vt*)malloc(sizeof(t_list_vt) * data->count_vt)))
		kill_all("Can't alloc memmory to data->vn\n");
	while (count != data->count_vt)
	{
		if (ft_strstr(data->line, "vt "))
		{
			c = data->line;
			c = while_not_digit(c);
			data->d_obj[count].u1 = ft_atof(c);
			c = next_digit(c);
			data->d_obj[count].v1 = ft_atof(c);
		}
		if (count != (data->count_vt - 1))
		{
			ft_strdel(&data->line);
			get_next_line(data->fd, &data->line);
		}
		count++;
	}
	ft_strdel(&data->line);
}

void			parse_vn(t_parse_obj *data)
{
	char		*c;
	u_int32_t	count;
	t_vector	vn;

	count = 0;
	if (!(data->vn = (cl_float3*)malloc(sizeof(cl_float3) * data->count_vn)))
		kill_all("Can't alloc memmory to data->vn\n");
	while (count != data->count_vn)
	{
		if (ft_strstr(data->line, "vn "))
		{
			c = NULL;
			vn = pod_parser(data, c);
			data->d_obj[count].vn = (cl_float3){{vn.x, vn.y, vn.z}};
		}
		if (count != (data->count_vn - 1))
		{
			ft_strdel(&data->line);
			get_next_line(data->fd, &data->line);
		}
		count++;
	}
	ft_strdel(&data->line);
}

size_t			compare_counters(u_int32_t v1,
u_int32_t v2, u_int32_t v3, u_int32_t v4)
{
	if (v1 >= v2 && v1 >= v3 && v1 >= v4)
		return (v1);
	else if (v2 >= v1 && v2 >= v3 && v2 >= v4)
		return (v2);
	else if (v3 >= v1 && v3 >= v2 && v3 >= v4)
		return (v3);
	else if (v4 >= v1 && v4 >= v2 && v4 >= v3)
		return (v4);
	return (0);
}
