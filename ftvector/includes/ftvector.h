/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftvector.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 13:00:53 by daron             #+#    #+#             */
/*   Updated: 2020/03/06 13:46:27 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTVECTOR_H
# define FTVECTOR_H

# include <math.h>

# define RAD(alpha) ((double)alpha * (M_PI / 180))

typedef struct	s_vector
{
	float		x;
	float		y;
	float		z;
}				t_vector;

/*
** vec_scale - Multiplies all three numbers of the vector by the given factor.
** vec_sub - Subtracts the second vector from the first, and copies the
** difference to the first.
*/

t_vector		vec_sum(t_vector *v1, t_vector *v2);
float			vec_len(t_vector *v1);
t_vector		vec_scale(t_vector *v1, float factor);
t_vector		vec_norm(t_vector *v1);
t_vector		vec_sub(t_vector *v1, t_vector *v2);
float			vec_dot(t_vector *v1, t_vector *v2);
t_vector		vec_rot_x(t_vector v1, double alpha);
t_vector		vec_rot_y(t_vector v1, double betta);
t_vector		vec_rot_z(t_vector v1, double gamma);
t_vector		vec_rot_xyz(t_vector v1, t_vector alp);
t_vector		vec_cross(t_vector *v1, t_vector *v2);

#endif
