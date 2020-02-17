/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_sum.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 13:07:32 by daron             #+#    #+#             */
/*   Updated: 2020/02/11 13:15:09 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftvector.h"

t_vector		vec_sum(t_vector *v1, t_vector *v2)
{
	t_vector v;

	v.x = v1->x + v2->x;
	v.y = v1->y + v2->y;
	v.z = v1->z + v2->z;
	return (v);
}
