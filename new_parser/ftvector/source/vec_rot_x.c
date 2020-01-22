/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_rot_x.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 13:46:39 by daron             #+#    #+#             */
/*   Updated: 2019/10/19 13:50:24 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftvector.h"

t_vector		vec_rot_x(t_vector v1, double alpha)
{
	t_vector	rot_vec;

	rot_vec.x = v1.x;
	rot_vec.y = v1.y * cos(alpha) - v1.z * sin(alpha);
	rot_vec.z = v1.y * sin(alpha) + v1.z * cos(alpha);
	return (rot_vec);
}
