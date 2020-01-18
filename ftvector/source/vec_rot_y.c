/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_rot_y.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 13:50:26 by daron             #+#    #+#             */
/*   Updated: 2019/10/19 14:08:29 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftvector.h"

t_vector		vec_rot_y(t_vector v1, double betta)
{
	t_vector	rot_vec;

	rot_vec.x = v1.x * cos(betta) + v1.z * sin(betta);
	rot_vec.y = v1.y;
	rot_vec.z = v1.z * cos(betta) - v1.x * sin(betta);
	return (rot_vec);
}
