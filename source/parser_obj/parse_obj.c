/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 18:53:55 by rsticks           #+#    #+#             */
/*   Updated: 2020/02/01 16:35:45 by rsticks          ###   ########.fr       */
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

static void		while_not_digit(char *c)
{
	while (!(ftft_isdigit(*c)))
		c++;
}

static void		next_digit(char *c)
{
	while (*c != ' ' || *c != '\0')
		c++;
	while (!(ftft_isdigit(*c)) || *c != '\0')
		c++;
	if (*c == '\0')
		kill_all(".obj error\n");
}

void			parse_v(t_parse_obj *data)
{
	char		*c;
	u_int32_t	count;

	count = 0;
	if (!(data->v = (t_list_v*)malloc(sizeof(t_list_v) * data->count_v)))
		kill_all("Can't alloc memmory to data->v\n");
	get_next_line(data->fd, &data->line);
	while (!(ft_strstr(data->line, "v ")))
		get_next_line(data->fd, &data->line);
	while (count != data->count_v)
	{
		get_next_line(data->fd, &data->line);
		if (ft_strstr(data->line, "v "))
		{
			c = data->line;
			while_not_digit(c);
			data->v[count].x = ft_atof(c);
			next_digit(c);
			data->v[count].y = ft_atof(c);
			next_digit(c);
			data->v[count].z = ft_atof(c);
		}
		count++;
		free(data->line);
	}	
}

static void		init_data(t_parse_obj *data)
{
	data->count_v = 0;
	data->count_vn = 0;
	data->count_f = 0;
}

void			parsing_obj(char *path)
{
	t_parse_obj *data;

	if (!(data = (t_parse_obj*)malloc(sizeof(t_parse_obj))))
		kill_all("Can't initialize obj_data\n");
	init_data(data);
	if (!(data->fd = open(path, O_RDONLY)))
		kill_all("Can't open obj file\n");
	counter(data, "v ", &data->count_v);
	counter(data, "vn ", &data->count_vn);
	counter(data, "f ", &data->count_f);
	close(data->fd);
	data->fd = open(path, O_RDONLY);
	parse_v(data);
}
