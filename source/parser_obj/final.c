/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 19:35:11 by rsticks           #+#    #+#             */
/*   Updated: 2020/03/05 19:37:46 by rsticks          ###   ########.fr       */
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

static void			final_parse_3(u_int32_t count, t_parse_obj *data)
{
	if (count != (data->count_f - 1))
	{
		ft_strdel(&data->line);
		get_next_line(data->fd, &data->line);
	}
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
		final_parse_3(count, data);
		count++;
	}
	ft_strdel(&data->line);
}
