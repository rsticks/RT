/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliary.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzina <kzina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 12:15:38 by kzina             #+#    #+#             */
/*   Updated: 2020/03/05 21:17:11 by kzina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void				swap(char *x, char *y)
{
	char			t;

	t = *x;
	*x = *y;
	*y = t;
}

char				*reverse(char *buffer, int i, int j)
{
	while (i < j)
		swap(&buffer[i++], &buffer[j--]);
	return (buffer);
}

char				*itoa(int value, char *buffer)
{
	int				base;
	int				n;
	int				i;
	int				r;

	n = abs(value);
	base = 10;
	i = 0;
	while (n)
	{
		r = n % base;
		if (r >= 10)
			buffer[i++] = 65 + (r - 10);
		else
			buffer[i++] = 48 + r;
		n = n / base;
	}
	if (i == 0)
		buffer[i++] = '0';
	if (value < 0 && base == 10)
		buffer[i++] = '-';
	buffer[i] = '\0';
	return (reverse(buffer, 0, i - 1));
}

void				calc_shift(t_rt *rt)
{
	rt->ui.shift = (ft_strlen(rt->text) - 1) * 5;
}

void				draw_selected_2(t_rt *rt, t_obj *obj)
{
	vec_norm(&obj->dir);
	ftoa(obj->dir.x, rt->text, 3);
	calc_shift(rt);
	draw_text(rt, 5, 37 - rt->ui.shift, 155);
	ftoa(obj->dir.y, rt->text, 3);
	calc_shift(rt);
	draw_text(rt, 6, 103 - rt->ui.shift, 155);
	ftoa(obj->dir.z, rt->text, 3);
	calc_shift(rt);
	draw_text(rt, 7, 170 - rt->ui.shift, 155);
	itoa((int)obj->rgb.r, rt->text);
	calc_shift(rt);
	draw_text(rt, 8, 35 - rt->ui.shift, 212);
	itoa((int)obj->rgb.g, rt->text);
	calc_shift(rt);
	draw_text(rt, 9, 104 - rt->ui.shift, 212);
	itoa((int)obj->rgb.b, rt->text);
	calc_shift(rt);
	draw_text(rt, 10, 170 - rt->ui.shift, 212);
}
