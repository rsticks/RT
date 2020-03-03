/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_function_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 16:31:24 by daron             #+#    #+#             */
/*   Updated: 2020/03/03 17:18:38 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float		take_coef(char *line, int str_c, char let)
{
	int		i;
	float	res;

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

char		*take_refl(char *line, t_obj *obj, int str_c)
{
	if (!(line = ft_strchr(line, '{')))
		kill_error("Not found '{'", str_c);
	if (ft_strchr(line, '}') == NULL)
		kill_error("Not found '}'", str_c);
	line++;
	while (*line != 'o' && *line != '}' && *line)
		line++;
	if ((obj->reflect = ft_strnequ(line, "on", 2)) == 1)
		obj->coef_refl = take_coef(line, str_c, 'c');
	else if ((ft_strnequ(line, "off", 3)) == 1)
		return (ft_strchr(line, '}'));
	else
		kill_error("You can use only off/on parameter", str_c);
	return (ft_strchr(line, '}'));
}

char		*take_refraction(char *line, t_obj *obj, int str_c)
{
	if (!(line = ft_strchr(line, '{')))
		kill_error("Not found '{'", str_c);
	if (ft_strchr(line, '}') == NULL)
		kill_error("Not found '}'", str_c);
	line++;
	while (*line != 'o' && *line != '}' && *line)
		line++;
	if ((obj->refr = ft_strnequ(line, "on", 2)) == 1)
	{
		obj->ind_refr = take_coef(line, str_c, 'r');
		obj->coef_refr = take_coef(line, str_c, 'c');
	}
	else if ((ft_strnequ(line, "off", 3)) == 1)
		return (ft_strchr(line, '}'));
	else
		kill_error("You can use only off/on parameter", str_c);
	return (ft_strchr(line, '}'));
}

char		*take_on_off(char *line, int *put_s, int str_c)
{
	if (!(line = ft_strchr(line, '{')))
		kill_error("Not found '{'", str_c);
	if (ft_strchr(line, '}') == NULL)
		kill_error("Not found '}'", str_c);
	line++;
	while (*line != 'o' && *line != '}' && *line)
		line++;
	if (ft_strnequ(line, "on", 2) == 1)
		*put_s = 1;
	else if ((ft_strnequ(line, "off", 3)) == 1)
		*put_s = 0;
	else
		kill_error("You can use only off/on parameter", str_c);
	return (ft_strchr(line, '}'));
}

char		*take_skybox(char *line, int *skybox_id, int str_c)
{
	if (!(line = ft_strchr(line, '{')))
		kill_error("Not found '{'", str_c);
	if (ft_strchr(line, '}') == NULL)
		kill_error("Not found '}'", str_c);
	line++;
	if (ft_strnequ(line, "brick", 5) == 1)
		*skybox_id = SB_BRICK_ID;
	else if ((ft_strnequ(line, "hernis_1", 8)) == 1)
		*skybox_id = SB_HERNIA_1_ID;
	else
		kill_error("You can use tis type of skybox", str_c);
	return (ft_strchr(line, '}'));
}