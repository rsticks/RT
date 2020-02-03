/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 18:53:55 by rsticks           #+#    #+#             */
/*   Updated: 2020/02/03 19:56:53 by rsticks          ###   ########.fr       */
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

	error = 0;
	count = 0;
	if (!(data->v = (t_list_v*)malloc(sizeof(t_list_v) * data->count_v)))
		kill_all("Can't alloc memmory to data->v\n");
	get_next_line(data->fd, &data->line);
	while (!(ft_strstr(data->line, "v ")))
		get_next_line(data->fd, &data->line);
	while (count != data->count_v)
	{
		if (ft_strstr(data->line, "v "))
		{
			c = data->line;
			c = while_not_digit(c, &error);
			data->v[count].x = ft_atof(c);
			c = next_digit(c, &error);
			data->v[count].y = ft_atof(c);
			c = next_digit(c, &error);
			data->v[count].z = ft_atof(c);
			if (error)
				kill_all(ft_strjoin("Wrong file: ", data->name));
		}
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

	error = 1;
	count = 0;
	if (!(data->vn = (t_list_vn*)malloc(sizeof(t_list_vn) * data->count_vn)))
		kill_all("Can't alloc memmory to data->vn\n");
	while (!(ft_strstr(data->line, "vn ")))
		get_next_line(data->fd, &data->line);
	while (count != data->count_vn)
	{
		if (ft_strstr(data->line, "v "))
		{
			c = data->line;
			c = while_not_digit(c, &error);
			data->vn[count].x = ft_atoi(c);
			c = next_digit(c, &error);
			data->vn[count].y = ft_atoi(c);
			c = next_digit(c, &error);
			data->vn[count].z = ft_atoi(c);
			if (error)
				kill_all(ft_strjoin("Wrong file: ", data->name));
		}
		get_next_line(data->fd, &data->line);
		count++;
	}
		free(data->line);
}

void			final_parse(t_parse_obj *data)
{
	char		*c;
	int			error;
	u_int32_t	count;
	t_list_vn	f;

	error = 0;
	count = 0;
	if (!(data->obj = (t_cl_obj*)malloc(sizeof(t_cl_obj) * data->count_f)))
		kill_all("Can't alloc memmory to data->obj\n");
	while (!(ft_strstr(data->line, "f ")))
		get_next_line(data->fd, &data->line);
	while (count != data->count_f)
	{
		if (ft_strstr(data->line, "f "))
		{
			c = data->line;
			c = while_not_digit(c, &error);
			f.x = ft_atoi(c);
			c = next_digit(c, &error);
			f.y = ft_atoi(c);
			c = next_digit(c, &error);
			f.z = ft_atoi(c);
			data->obj[count].f = (cl_int3){{f.x, f.y, f.z}};
			data->obj[count].v1 = (cl_float3){{data->v[f.x - 1].x, data->v[f.x - 1].y, data->v[f.x - 1].z}};
			data->obj[count].v2 = (cl_float3){{data->v[f.y - 1].x, data->v[f.y - 1].y, data->v[f.y - 1].z}};
			data->obj[count].v3 = (cl_float3){{data->v[f.z - 1].x, data->v[f.z - 1].y, data->v[f.z - 1].z}};
			data->obj[count].num_obj = data->num_obj;
		}
		get_next_line(data->fd, &data->line);
		count++;
	}
		free(data->line);
}

static void		init_data(t_parse_obj *data, int num)
{
	data->num_obj = num;
	data->count_v = 0;
	data->count_vn = 0;
	data->count_f = 0;
}

void			parsing_obj(char *path, int num)
{
	t_parse_obj *data;

	if (!(data = (t_parse_obj*)malloc(sizeof(t_parse_obj))))
		kill_all("Can't initialize obj_data\n");
	init_data(data, num);
	data->name = path;
	if (!(data->fd = open(path, O_RDONLY)))
		kill_all("Can't open obj file\n");
	counter(data, "v ", &data->count_v);
	counter(data, "vn ", &data->count_vn);
	counter(data, "f ", &data->count_f);
	close(data->fd);
	data->fd = open(path, O_RDONLY);
	parse_v(data);
	final_parse(data);
	u_int32_t count;
	count = 0;

	while (count != data->count_f)
	{
		printf("f %d (x: %-10f y: %-10f z: %-10f) || %d (x: %-10f y: %-10f z: %-10f) || %d (x: %-10f y: %-10f z: %-10f)\n", 
			data->obj[count].f.x, data->obj[count].v1.x, data->obj[count].v1.y, data->obj[count].v1.z,
			data->obj[count].f.y, data->obj[count].v2.x, data->obj[count].v2.y, data->obj[count].v2.z,
			data->obj[count].f.z, data->obj[count].v3.x, data->obj[count].v3.y, data->obj[count].v3.z);
		count++;
	}	
}
