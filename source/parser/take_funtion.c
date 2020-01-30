/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_funtion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 14:33:30 by daron             #+#    #+#             */
/*   Updated: 2020/01/27 14:07:05 by daron            ###   ########.fr       */
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
	float res;

	if (!(ptr = ft_strsub(str, 0, i)))
		kill_all("ERROR: Can't allocate memory <get_double_value>");
	res = (float)ft_atof(ptr);
	free(ptr);
	return (res);
}

double cheak_double(char *line, int str_c)
{
	int cheak[2];
	int i;

	ft_memset_int(cheak, 0, 2);
	i = 0;
	while (line[i] != ' ' && line[i] != '}' && (ft_isdigit(line[i]) || line[i] == '.' || line[i] == '-'))
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
	if (line[i - 1] == '.' || cheak[0] == 0 || cheak[1] == 0)
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

char *take_word(char *line, char **put_s, int str_c)
{
	size_t len_w;

	len_w = 0;
	if (!(line = ft_strchr(line, '{')))
		kill_error("Not found '{'", str_c);
	if (ft_strchr(line, '}') == NULL)
		kill_error("Not found '}'", str_c);
	line++;
	while (line[len_w] != '}')
		len_w++;
	if (len_w != 0)
		(*put_s) = ft_strsub(line, 0, len_w);
	return (ft_strchr(line, '}'));
}

char *take_res(char *line, int *put_s, int str_c)
{
	if (!(line = ft_strchr(line, '{')))
		kill_error("Not found '{'", str_c);
	if (ft_strchr(line, '}') == NULL)
		kill_error("Not found '}'", str_c);
	while (0 == (ft_isalpha((*line)) && *line) && 0 == (ft_isdigit(*line)) && *line != '-')
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

t_vector get_vector_value_d(char *str, int str_c)
{
	int cheak[3];
	t_vector vec;

	ft_memset_int(cheak, 0 ,3);
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

char *take_vector(char *line, t_vector *put_s, int str_c)
{
	if (!(line = ft_strchr(line, '{')))
		kill_error("Not found '{'", str_c);
	if (ft_strchr(line, '}') == NULL)
		kill_error("Not found '}'", str_c);
	*put_s = get_vector_value_d(line, str_c);
	return (ft_strchr(line, '}'));
}

t_rgb2 get_vector_value_rgb(char *str, int str_c)
{
	int cheak[3];
	t_rgb2 vec;

	ft_memset_int(cheak, 0 ,3);
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

char *take_rgb(char *line, t_rgb2 *put_s, int str_c)
{
	if (!(line = ft_strchr(line, '{')))
		kill_error("Not found '{'", str_c);
	if (ft_strchr(line, '}') == NULL)
		kill_error("Not found '}'", str_c);
	*put_s = get_vector_value_rgb(line, str_c);
	return (ft_strchr(line, '}'));
}

float take_coef(char *line, int str_c, char let)
{
	int i;
	float res;

	i = 0;
	res = 0;
	while (line[i] != let && line[i])
		i++;
	if (line[i] != let)
		kill_error("Problem with coefficient", str_c);
	else
	{
		i++;
		res = cheak_double((line + i), str_c);
	}
	return (res);
}

char *take_refl(char *line, t_obj *obj, int str_c)
{
	char *tmp;
	int j;

	j = 0;
	if (!(line = ft_strchr(line, '{')))
		kill_error("Not found '{'", str_c);
	if (ft_strchr(line, '}') == NULL)
		kill_error("Not found '}'", str_c);
	line++;
	while (line[j] != '}' && line[j])
		j++;
	if (!(tmp = ft_strsub(line, 0, j + 1)))
		kill_all("Problem with allocated memory <take_refl>");
	j = 0;
	while (0 == (ft_isalpha((tmp[j])) && tmp[j]) && 0 == (ft_isdigit(tmp[j])))
		j++;
	if ((obj->reflect = ft_strnequ("on", (tmp + j), 2)) == 1)
		j += 2;
	else if ((ft_strnequ("off", (tmp + j), 3)) == 1)
	{
		free(tmp);
		return (ft_strchr(line, '}'));
	}
	else
		kill_error("You can use only off/on parameter", str_c);
	if (obj->reflect == 1)
		obj->coef_refl =  take_coef((tmp + j), str_c, 'c');
	free(tmp);
	return (ft_strchr(line, '}'));
}

char *take_refraction(char *line, t_obj *obj, int str_c)
{
	char *tmp;
	int j;

	j = 0;
	if (!(line = ft_strchr(line, '{')))
		kill_error("Not found '{'", str_c);
	if (ft_strchr(line, '}') == NULL)
		kill_error("Not found '}'", str_c);
	line++;
	while (line[j] != '}' && line[j])
		j++;
	if (!(tmp = ft_strsub(line, 0, j + 1)))
		kill_all("Problem with allocated memory <take_refraction>");
	j = 0;
	if ((obj->refr = ft_strnequ("on", tmp, 2)) == 1)
		j += 2;
	else if (ft_strnequ("off", tmp, 3) == 1)
	{
		free(tmp);
		return (ft_strchr(line, '}'));
	}
	else
		kill_error("You can use only off/on parameter", str_c);
	if (obj->reflect == 1)
	{
		obj->ind_refr = take_coef(tmp, str_c, 'r');
		obj->coef_refr = take_coef(tmp, str_c, 'c');
	}
	free(tmp);
	return (ft_strchr(line, '}'));
}

char *take_on_off(char *line, int *put_s, int str_c)
{
	int i;
	char *tmp;

	i = 0;
	if (!(line = ft_strchr(line, '{')))
		kill_error("Not found '{'", str_c);
	if (ft_strchr(line, '}') == NULL)
		kill_error("Not found '}'", str_c);
	line++;
	while (line[i] != '}')
		i++;
	if (!(tmp = ft_strsub(line, 0, (size_t)i)))
		kill_all("Problem with allocated memory <take_on_off>");
	while (0 == (ft_isalpha((*tmp)) && *tmp) && 0 == (ft_isdigit(*tmp)))
		tmp++;
	if (ft_strnequ("on", tmp, 2) == 1)
		*put_s = 1;
	else if (ft_strnequ("off", tmp, 3) == 1)
		*put_s = 0;
	else
		kill_error("You can use only off/on parameter", str_c);
	free(tmp);
	return (ft_strchr(line, '}'));
}

void take_file_name(char *line, t_obj *obj, char *type, int str_c)
{
	int i;
	char *tmp;

	i = 0;
	if (!(line = ft_strchr(line, '"')) || ft_strchr((line + 1), '"') == NULL)
		kill_error("Not found bmp name", str_c);
	line++;
	while (line[i] != '"')
		i++;
	if (!(tmp = ft_strsub(line, 0, (size_t)i)))
		kill_error("Can't allocate memory", str_c);
	if (ft_strequ("img", type))
	{
		obj->text_on = 1;
		obj->texture = tmp;
	}
	else if (ft_strequ("obj", type))
	{
		obj->obj_on = 1;
		obj->file_name = tmp;
	}
	else
		kill_error("Bad type", str_c);
}

char *take_texture(char *line, t_obj *obj, char *type,int str_c)
{
	if (!(line = ft_strchr(line, '{')))
		kill_error("Not found '{'", str_c);
	if (ft_strchr(line, '}') == NULL)
		kill_error("Not found '}'", str_c);
	line++;
	while ((*line == ' ') && *line)
		line++;
	if ((ft_strnequ(type, line, 3)) == 1)
		take_file_name(line, obj, type, str_c);
	else
		kill_error("You can't use this type of texture", str_c);
	return (ft_strchr(line, '}'));
}

