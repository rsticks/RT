/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 15:30:02 by rsticks           #+#    #+#             */
/*   Updated: 2020/03/05 16:03:57 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "pars_obj.h"

int				ftft_isdigit(int c)
{
	if ((c >= '0' && c <= '9') || c == '-')
		return (1);
	return (0);
}

void			counter(t_parse_obj *data, char *str, u_int32_t *count)
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

char			*next_digit(char *c)
{
	while (*c != ' ' && *c != '\0')
		c++;
	while (!(ftft_isdigit(*c)) && *c != '\0')
		c++;
	if (*c == '\0')
		kill_all("Error: .obj error");
	return (c);
}

char			*while_not_slash(char *c, int *i)
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
