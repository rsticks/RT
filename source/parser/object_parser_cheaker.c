/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_parser_cheaker.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 15:32:47 by daron             #+#    #+#             */
/*   Updated: 2020/03/02 15:45:40 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	check_inti_reflection(t_rt *rt, int str_c)
{
	if (rt->obj_cur->coef_refl < 0.0)
		kill_error("Wrong reflection coefficient", str_c);
}

void	check_inti_refraction(t_rt *rt, int str_c)
{
	if (rt->obj_cur->coef_refr < 0.0 || rt->obj_cur->ind_refr < 0.0)
		kill_error("Wrong refraction parametr", str_c);
}

void	check_inti_radius(t_rt *rt, int str_c)
{
	if (!(rt->obj_cur->radius >= 0.1 && rt->obj_cur->radius <= 100.0))
		kill_error("Uncorrected radius", str_c);
	if (rt->obj_cur->type == TORUS_ID && rt->obj_cur->torus_r < 0.1
			&& rt->obj_cur->torus_r > 100.0)
		kill_error("Uncorrected torus radius", str_c);
}

void	check_inti_dir_obj(t_rt *rt, int str_c)
{
	if (rt->obj_cur->type != SPHERE_ID && rt->obj_cur->dir.x == 0.
		&& rt->obj_cur->dir.y == 0. && rt->obj_cur->dir.z == 0.)
		kill_error("Set the direction vector", str_c);
}

void	check_inti_obj_rgb(t_rt *rt, int str_c)
{
	if (!(rt->obj_cur->rgb.r >= 0 && rt->obj_cur->rgb.r <= 255))
		kill_error("Wrong red color component", str_c);
	else if (!(rt->obj_cur->rgb.g >= 0 && rt->obj_cur->rgb.g <= 255))
		kill_error("Wrong green color component", str_c);
	else if (!(rt->obj_cur->rgb.b >= 0 && rt->obj_cur->rgb.b <= 255))
		kill_error("Wrong blue color component", str_c);
}
