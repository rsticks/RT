/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_funtion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 14:33:30 by daron             #+#    #+#             */
/*   Updated: 2020/03/02 16:35:01 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		take_file_name(char *line, t_obj *obj, char *type, int str_c)
{
	int		i;
	char	*tmp;

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

char		*take_texture(char *line, t_obj *obj, char *type, int str_c)
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

char		*take_construction(char *line, int *construction_id, int str_c)
{
	if (!(line = ft_strchr(line, '{')))
		kill_error("Not found '{'", str_c);
	if (ft_strchr(line, '}') == NULL)
		kill_error("Not found '}'", str_c);
	line++;
	if (ft_strnequ(line, "waves", 5))
		*construction_id = WAVES_ID;
	else if (ft_strnequ(line, "chech beard", 11))
		*construction_id = CHECH_BEARD_ID;
	else
		kill_error("You can't use this type of construction", str_c);
	return (ft_strchr(line, '}'));
}
