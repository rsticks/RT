/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 18:53:55 by rsticks           #+#    #+#             */
/*   Updated: 2020/02/26 17:57:43 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "pars_obj.h"

static int		ftft_isdigit(int c)
{
	if ((c >= '0' && c <= '9') || c == '-')
		return (1);
	return (0);
}

static void		counter(t_parse_obj *data, char *str, u_int32_t *count)
{
	char		i;
	char		j;

	j = 1;
	i = 0;
	while (ft_strstr(data->line, str) && data->gnl)
	{
		(*count)++;
		data->gnl = get_next_line(data->fd, &data->line);
	}
}

char			*while_not_digit(char *c)
{
	while (!(ftft_isdigit(*c)) && *c != '\0')
		c++;
	if (*c == '\0')
		kill_all("Error: .obj error");
	return (c);
}

static char		*next_digit(char *c)
{
	while (*c != ' ' && *c != '\0')
		c++;
	while (!(ftft_isdigit(*c)) && *c != '\0')
		c++;
	if (*c == '\0')
		kill_all("Error: .obj error");
	return (c);
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
			c = data->line;
			c = while_not_digit(c);
			v.x = ft_atof(c);
			c = next_digit(c);
			v.y = ft_atof(c);
			c = next_digit(c);
			v.z = ft_atof(c);
			data->d_obj[count].v = (cl_float3){{v.x, v.y, v.z}};
		}
		if (count != (data->count_v - 1))
			get_next_line(data->fd, &data->line);
		count++;
	}
		free(data->line);
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
			get_next_line(data->fd, &data->line);
		count++;
	}
		free(data->line);
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
			c = data->line;
			c = while_not_digit(c);
			vn.x = ft_atof(c);
			c = next_digit(c);
			vn.y = ft_atof(c);
			c = next_digit(c);
			vn.z = ft_atof(c);
			data->d_obj[count].vn = (cl_float3){{vn.x, vn.y, vn.z}};
		}
		if (count != (data->count_vn - 1))
			get_next_line(data->fd, &data->line);
		count++;
	}
		free(data->line);
}

char				*while_not_slash(char *c, int *i)
{
	while (*c != '/' && *c != ' ')
		c++;
	if (*c == '/')
	{
		c++;
		*i = 1;
	}
	else
		*i = 0;
	return (c);
}

char			*f_pars_x(t_parse_obj *data, char *c, u_int32_t count)
{
	t_int_vec	x;
	int i;


	x.x = 0;
	x.y = 0;
	x.z = 0;
	x.x = ft_atoi(c);
	c = while_not_slash(c, &i);
	if (!i)
		return (c);
	x.y = ft_atoi(c);
	c = while_not_slash(c, &i);
	if (!i)
		return (c);
	x.z = ft_atoi(c);
	data->d_obj[count].vf.x = x.x;
	data->d_obj[count].vtf.x = x.y;
	data->d_obj[count].vnf.x = x.z;
	return (c);
}

char			*f_pars_y(t_parse_obj *data, char *c, u_int32_t count)
{
	int i;
	t_int_vec	y;

	y.x = 0;
	y.y = 0;
	y.z = 0;
	y.x = ft_atoi(c);
	c = while_not_slash(c, &i);
	if (!i)
		return (c);
	y.y = ft_atoi(c);
	c = while_not_slash(c, &i);
	if (!i)
		return (c);
	y.z = ft_atoi(c);
	data->d_obj[count].vf.y = y.x;
	data->d_obj[count].vtf.y = y.y;
	data->d_obj[count].vnf.y = y.z;
	return (c);
}

char			*f_pars_z(t_parse_obj *data, char *c, u_int32_t count)
{
	int i;
	t_int_vec	z;

	z.x = 0;
	z.y = 0;
	z.z = 0;
	z.x = ft_atoi(c);
	c = while_not_slash(c, &i);
	if (!i)
		return (c);
	z.y = ft_atoi(c);
	c = while_not_slash(c, &i);
	if (!i)
		return (c);
	z.z = ft_atoi(c);
	data->d_obj[count].vf.z = z.x;
	data->d_obj[count].vtf.z = z.y;
	data->d_obj[count].vnf.z = z.z;
	return (c);
}

void			final_parse(t_parse_obj *data)
{
	char		*c;
	int			error;
	u_int32_t	count;

	error = 0;
	count = 0;
	if (!(data->f = (t_list_f*)malloc(sizeof(t_list_f) * data->count_f)))
		kill_all("Can't alloc memmory to data->obj\n");
	while (count != data->count_f)
	{
		if (ft_strstr(data->line, "f "))
		{
			c = data->line;
			c = while_not_digit(c);
			c = f_pars_x(data, c, count);
			c = next_digit(c);
			c = f_pars_y(data, c, count);
			c = next_digit(c);
			c = f_pars_z(data, c, count);
			while (*c != ' ' && *c != '\0')
				c++;
			while (!(ftft_isdigit(*c)) && *c != '\0')
				c++;
			if (*c != '\0')
				kill_all("Error: .obj not triangulate");
		}
		if (count != (data->count_f - 1))
			get_next_line(data->fd, &data->line);
		count++;
	}
	free(data->line);
}

static void		init_data(t_parse_obj *data, int num)
{
	data->num_obj = num;
	data->count_vt = 0;
	data->count_v = 0;
	data->count_vn = 0;
	data->count_f = 0;
}

size_t			compare_counters(u_int32_t v1, u_int32_t v2, u_int32_t v3, u_int32_t v4)
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

t_parse_obj			*parsing_obj(char *path, int num)
{
	t_parse_obj 	*data;

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
			data->gnl = get_next_line(data->fd, &data->line);
	}
	data->max_c = compare_counters(data->count_v, data->count_vn, data->count_vt, data->count_f);
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
	}
	close(data->fd);

	printf("Not in Kernel obj data\n");
	for (size_t i = 0; i < data->count_v; i++)
		printf("v %f %f %f\n", data->d_obj[i].v.x, data->d_obj[i].v.y, data->d_obj[i].v.z);
	for (size_t i = 0; i < data->count_vn; i++)
	{
		printf("vn %f %f %f\n", data->d_obj[i].vn.x, data->d_obj[i].vn.y, data->d_obj[i].vn.z);
	}
	for (size_t i = 0; i < data->count_f; i++)
	{
		printf("f %d/%d/%d %d/%d/%d %d/%d/%d\n",
		data->d_obj[i].vf.x, data->d_obj[i].vtf.x, data->d_obj[i].vnf.x,
		data->d_obj[i].vf.y, data->d_obj[i].vtf.y, data->d_obj[i].vnf.y,
		data->d_obj[i].vf.z, data->d_obj[i].vtf.z, data->d_obj[i].vnf.z);
	}
	
	return (data);
}


