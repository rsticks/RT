/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_rot_xyz.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 14:08:47 by daron             #+#    #+#             */
/*   Updated: 2019/10/19 14:08:47 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftvector.h"

t_vector	vec_rot_xyz(t_vector v1, t_vector alp)
{
	v1 = vec_rot_x(v1, RAD(alp.x));
	v1 = vec_rot_x(v1, RAD(alp.y));
	v1 = vec_rot_x(v1, RAD(alp.z));
	return (v1);
}
