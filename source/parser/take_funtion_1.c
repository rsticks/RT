/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_funtion_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 15:56:06 by daron             #+#    #+#             */
/*   Updated: 2020/03/05 16:41:39 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_vector	get_vector_value_d(char *str, int str_c, int *cheak)
{
	t_vector	vec;

	ft_memset_int(cheak, 0, 3);
	while (*str != '}' && *str)
	{
		if (*str == 'x')
		{
			vec.x = cheak_double(++str, str_c);
			cheak[0]++;
		}
		else if (*str == 'y')
		{
			vec.y = cheak_double(++str, str_c);
			cheak[1]++;
		}
		else if (*str == 'z')
		{
			vec.z = cheak_double(++str, str_c);
			cheak[2]++;
		}
		str++;
	}
	if (!(cheak[0] == 1 && cheak[1] == 1 && cheak[2] == 1))
		kill_error("Invalid vector format", str_c);
	return (vec);
}

static t_rgb2	get_vector_value_rgb(char *str, int str_c, int *cheak)
{
	t_rgb2		vec;

	ft_memset_int(cheak, 0, 3);
	while (*str != '}' && *str)
	{
		if (*str == 'r')
		{
			vec.r = (float)ft_atoi(++str);
			cheak[0]++;
		}
		else if (*str == 'g')
		{
			vec.g = (float)ft_atoi(++str);
			cheak[1]++;
		}
		else if (*str == 'b')
		{
			vec.b = (float)ft_atoi(++str);
			cheak[2]++;
		}
		str++;
	}
	if (!(cheak[0] == 1 && cheak[1] == 1 && cheak[2] == 1))
		kill_error("Invalid color format", str_c);
	return (vec);
}

char			*take_vector(char *line, t_vector *put_s, int str_c)
{
	int			cheak[3];

	if (!(line = ft_strchr(line, '{')))
		kill_error("Not found '{'", str_c);
	if (ft_strchr(line, '}') == NULL)
		kill_error("Not found '}'", str_c);
	*put_s = get_vector_value_d(line, str_c, &(cheak[0]));
	return (ft_strchr(line, '}'));
}

char			*take_rgb(char *line, t_rgb2 *put_s, int str_c)
{
	int			cheak[3];

	if (!(line = ft_strchr(line, '{')))
		kill_error("Not found '{'", str_c);
	if (ft_strchr(line, '}') == NULL)
		kill_error("Not found '}'", str_c);
	*put_s = get_vector_value_rgb(line, str_c, &(cheak[0]));
	return (ft_strchr(line, '}'));
}

char			*take_res(char *line, int *put_s, int str_c)
{
	if (!(line = ft_strchr(line, '{')))
		kill_error("Not found '{'", str_c);
	if (ft_strchr(line, '}') == NULL)
		kill_error("Not found '}'", str_c);
	while (0 == (ft_isalpha((*line)) && *line)
			&& 0 == (ft_isdigit(*line)) && *line != '-')
		line++;
	put_s[0] = ft_atoi(line);
	while (ft_isdigit(*line))
		line++;
	if (*line != ' ')
		kill_error("Wrong format", str_c);
	line++;
	put_s[1] = ft_atoi(line);
	return (ft_strchr(line, '}'));
}
