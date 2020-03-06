/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parser_cheker.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 15:23:53 by daron             #+#    #+#             */
/*   Updated: 2020/03/06 13:46:27 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	check_inti_alias(int anti_alias, int str_c)
{
	if ((anti_alias != 1 && anti_alias != 2 && anti_alias != 4 &&
			anti_alias != 8 && anti_alias != 16) || anti_alias < 0)
		kill_error("Wrong format for AntiAliasing", str_c);
}

void	check_inti_maxref(int maxref, int str_c)
{
	if (!(maxref >= 0 && maxref < 15))
		kill_error("Wrong format for reflection count", str_c);
}

void	check_inti_ambiant(float ambiant, int str_c)
{
	if (!(ambiant >= 0.0 && ambiant <= 100.0))
		kill_error("Wrong format for ambiant count", str_c);
}

void	check_inti_effect(t_rt *rt, int str_c)
{
	if ((ft_strnequ("black and white", rt->window.effecr_name, 15)) == 1)
		rt->window.effect_on = 1;
	else if (rt->window.effecr_name != NULL)
		kill_error("Program don't have this effect type", str_c);
}

void	check_inti_res(t_rt *rt, int str_c)
{
	if (rt->window.size[0] <= 0 || rt->window.size[1] <= 0)
		kill_error("Wrong format of window size", str_c);
}
