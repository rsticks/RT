/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_scale.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 13:26:36 by daron             #+#    #+#             */
/*   Updated: 2020/02/18 14:14:00 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftvector.h"

t_vector	vec_scale(t_vector *v1, float factor)
{
	t_vector v;

	v.x = v1->x * factor;
	v.y = v1->y * factor;
	v.z = v1->z * factor;
	return (v);
}
