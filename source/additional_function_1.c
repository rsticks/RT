/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_function_1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:30:37 by daron             #+#    #+#             */
/*   Updated: 2020/01/30 13:57:47 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			ft_fzero(float *s, int n)
{
	int			i;

	i = 0;
	while (i < n)
	{
		s[i] = 0.0f;
		i++;
	}
}

double			get_quadratic_solution(double a, double b, double discriminant)
{
	double		t1;
	double		t2;

	t1 = (-b - sqrt(discriminant)) / (2 * a);
	t2 = (-b + sqrt(discriminant)) / (2 * a);
	if ((t1 <= t2 && t1 >= 0) || (t1 >= 0 && t2 < 0))
		return (t1);
	else if ((t2 <= t1 && t2 >= 0) || (t1 < 0 && t2 >= 0))
		return (t2);
	return (-1);
}