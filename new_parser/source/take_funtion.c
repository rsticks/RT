/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_funtion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 14:33:30 by daron             #+#    #+#             */
/*   Updated: 2020/01/21 17:40:46 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char *take_int(char *line, int *put_s, int str_c)
{
	if (!(line = ft_strchr(line, '{')))
		kill_error("Not found '{'", str_c);
	if (ft_strchr(line, '}') == NULL)
		kill_error("Not found '}'", str_c);
	while ((*line < '0' || *line > '9') && (*line != '-' && *line))
		line++;
	if ((ft_isdigit((int)*line)) == 0) // возможны проблемы с отрицательными значениями
		kill_error("Uncorrected value. Expected number.", str_c);
	*put_s = ft_atoi(line);
	return (ft_strchr(line, '}'));
}

double get_double_value(char *str, int i)
{
	char *ptr;
	double res;

	if (!(ptr = ft_strsub(str, 0, i)))
		kill_all("ERROR: Can't allocate memory <get_double_value>");
	res = ft_atof(ptr);
	free(ptr);
	return (res);
}

double cheak_double(char *line, int str_c)
{
	int cheak[2];
	int i;

	ft_memset_int(cheak, 0, 2);
	i = 0;
	while (line[i] != ' ' && line[i] != '}')
	{
		if (ft_isdigit(line[i]) || line[i] == '-' || line[i] == '.')
		{
			if (line[i] == '-' && i > 0)
				kill_error("Invalid value.", str_c);
			else if ((line[i] == '.' && cheak[1] == 1) || (line[i] == '.' && cheak[0] == 0))
				kill_error("Invalid value.", str_c);
			else if (ft_isdigit(line[i]))
				cheak[0] = 1;
			else if (line[i] == '.')
				cheak[1]++;
		}
		i++;
	}
	if (line[i - 1] == '.')
		kill_error("Invalid value.", str_c);
	return (get_double_value(line, i));
}

char *take_double(char *line, float *put_s, int str_c)
{
	int j;

	j = 0;
	if (!(line = ft_strchr(line, '{')))
		kill_error("Not found '{'", str_c);
	if (ft_strchr(line, '}') == NULL)
		kill_error("Not found '}'", str_c);
	while (0 == (ft_isalpha(line[j])) && 0 == (ft_isdigit(line[j])) && line[j] != '-')
		j++;
	*put_s = (float)cheak_double((line + j), str_c);
	return (ft_strchr(line, '}'));
}

