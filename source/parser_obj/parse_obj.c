/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 18:53:55 by rsticks           #+#    #+#             */
/*   Updated: 2020/02/05 16:12:26 by rsticks          ###   ########.fr       */
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
	while (j && get_next_line(data->fd, &data->line))
	{
		if (ft_strstr(data->line, str))
		{
			(*count)++;
			i = 1;
		}
		else if (i == 1)
		{
			j = 0;
		}
		free(data->line);
	}
}

char			*while_not_digit(char *c, int *error)
{
	while (!(ftft_isdigit(*c)) && *c != '\0')
		c++;
	if (*c == '\0')
		*error = 1;
	return (c);
}

static char		*next_digit(char *c, int *error)
{
	while (*c != ' ' && *c != '\0')
		c++;
	while (!(ftft_isdigit(*c)) && *c != '\0')
		c++;
	if (*c == '\0')
		*error = 1;
	return (c);
}


void			parse_v(t_parse_obj *data)
{
	char		*c;
	u_int32_t	count;
	int			error;
	t_vector	v;

	error = 0;
	count = 0;
	if (!(data->v = (cl_float3*)malloc(sizeof(cl_float3) * data->count_v)))
		kill_all("Can't alloc memmory to data->v\n");
	while (count != data->count_v)
	{
		if (ft_strstr(data->line, "v "))
		{
			c = data->line;
			c = while_not_digit(c, &error);
			v.x = ft_atof(c);
			c = next_digit(c, &error);
			v.y = ft_atof(c);
			c = next_digit(c, &error);
			v.z = ft_atof(c);
			data->v[count] = (cl_float3){{v.x, v.y, v.z}};
			if (error)
				kill_all(ft_strjoin("Wrong file: ", data->name));
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
	int			error;

	error = 0;
	count = 0;
	if (!(data->vt = (t_list_vt*)malloc(sizeof(t_list_vt) * data->count_vt)))
		kill_all("Can't alloc memmory to data->vn\n");
	while (count != data->count_vt)
	{
		if (ft_strstr(data->line, "vt "))
		{
			c = data->line;
			c = while_not_digit(c, &error);
			data->vt[count].u = ft_atof(c);
			c = next_digit(c, &error);
			data->vt[count].v = ft_atof(c);
			if (error)
				kill_all(ft_strjoin("Wrong file: ", data->name));
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
	int			error;
	t_vector	vn;

	error = 0;
	count = 0;
	if (!(data->vn = (cl_float3*)malloc(sizeof(cl_float3) * data->count_vn)))
		kill_all("Can't alloc memmory to data->vn\n");
	while (count != data->count_vn)
	{
		if (ft_strstr(data->line, "vn "))
		{
			c = data->line;
			c = while_not_digit(c, &error);
			vn.x = ft_atof(c);
			c = next_digit(c, &error);
			vn.y = ft_atof(c);
			c = next_digit(c, &error);
			vn.z = ft_atof(c);
			data->vn[count] = (cl_float3){{vn.x, vn.y, vn.z}};
			if (error)
				kill_all(ft_strjoin("Wrong file: ", data->name));
		}
		if (count != (data->count_vn - 1))
			get_next_line(data->fd, &data->line);
		count++;
	}
		free(data->line);
}

int				while_not_slash(char *c)
{
	while (*c != '/' && *c != ' ')
		c++;
	if (*c == '/')
	{
		c++;
		return (1);
	}
	else
		return (0);
}

char			*f_pars_x(t_parse_obj *data, char *c, u_int32_t count)
{
	t_int_vec	x;

	x.x = 0;
	x.y = 0;
	x.z = 0;
	x.x = ft_atoi(c);
	if (!while_not_slash(c))
		return (c);
	x.y = ft_atoi(c);
	if (!while_not_slash(c))
		return (c);
	x.z = ft_atoi(c);
	data->f[count].v.x = x.x;
	data->f[count].vt.x = x.y;
	data->f[count].vn.x = x.z;
	return (c);
}

char			*f_pars_y(t_parse_obj *data, char *c, u_int32_t count)
{
	t_int_vec	y;

	y.x = 0;
	y.y = 0;
	y.z = 0;
	y.x = ft_atoi(c);
	if (!while_not_slash(c))
		return (c);
	y.y = ft_atoi(c);
	if (!while_not_slash(c))
		return (c);
	y.z = ft_atoi(c);
	data->f[count].v.y = y.x;
	data->f[count].vt.y = y.y;
	data->f[count].vn.y = y.z;
	return (c);
}

char			*f_pars_z(t_parse_obj *data, char *c, u_int32_t count)
{
	t_int_vec	z;

	z.x = 0;
	z.y = 0;
	z.z = 0;
	z.x = ft_atoi(c);
	if (!while_not_slash(c))
		return (c);
	z.y = ft_atoi(c);
	if (!while_not_slash(c))
		return (c);
	z.z = ft_atoi(c);
	data->f[count].v.z = z.x;
	data->f[count].vt.z = z.y;
	data->f[count].vn.z = z.z;
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
			c = while_not_digit(c, &error);
			c = f_pars_x(data, c, count);
			c = next_digit(c, &error);
			c = f_pars_y(data, c, count);
			c = next_digit(c, &error);
			c = f_pars_z(data, c, count);
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

void			parsing_obj(char *path, int num)
{
	t_parse_obj *data;
	int			gnl;

	gnl = 1;
	if (!(data = (t_parse_obj*)malloc(sizeof(t_parse_obj))))
		kill_all("Can't initialize obj_data\n");
	init_data(data, num);
	data->name = path;
	if (!(data->fd = open(path, O_RDONLY)))
		kill_all("Can't open obj file\n");
	counter(data, "v ", &data->count_v);
	while (gnl)
	{
		if (ft_strstr(data->line, "vn "))
			counter(data, "vn ", &data->count_vn);
		else if (ft_strstr(data->line, "vt "))
			counter(data, "vt ", &data->count_vt);
		else if (ft_strstr(data->line, "f "))
			counter(data, "f ", &data->count_f);
		else
			gnl = get_next_line(data->fd, &data->line);
	}
	close(data->fd);
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
	printf("f || %d %d %d \n", data->f[0].v.x, data->f[0].v.y, data->f[0].v.z);
}
