/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_rot_z.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 14:03:24 by daron             #+#    #+#             */
/*   Updated: 2019/10/19 14:08:29 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftvector.h"

t_vector		vec_rot_z(t_vector v1, double gamma)
{
	t_vector	rot_vec;

	rot_vec.x = v1.x * cos(gamma) - v1.y * sin(gamma);
	rot_vec.y = v1.x * sin(gamma) + v1.y * cos(gamma);
	rot_vec.z = v1.z;
	return (rot_vec);
}
