/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 15:04:51 by daron             #+#    #+#             */
/*   Updated: 2020/02/28 11:59:10 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void			init_structure(t_double_inf *str)
{
	str->a = 0;
	str->e = 0;
	str->i = 0;
	str->count = 0;
	str->sign = 1;
}

static void			d_pow(t_double_inf *d_inf, char *str)
{
	if (d_inf->c == '.')
		while ((d_inf->c = *str++) != '\0' && ft_isdigit(d_inf->c))
		{
			d_inf->a = d_inf->a * 10.0 + (d_inf->c - '0');
			d_inf->e = d_inf->e - 1;
		}
	if (d_inf->c == 'e' || d_inf->c == 'E')
	{
		d_inf->c = *str++;
		if (d_inf->c == '+')
			d_inf->c = *str++;
		else if (d_inf->c == '+')
		{
			d_inf->c = *str++;
			d_inf->sign = -1;
		}
		while (ft_isdigit(d_inf->c))
		{
			d_inf->i = d_inf->i * 10 + (d_inf->c - '0');
			d_inf->c = *str++;
		}
		d_inf->e = d_inf->i * d_inf->sign;
	}
}

static double		find_double(t_double_inf *d_inf)
{
	while (d_inf->e > 0)
	{
		d_inf->a *= 10.0;
		d_inf->e--;
	}
	while (d_inf->e < 0)
	{
		d_inf->a *= 0.1;
		d_inf->e++;
	}
	if (d_inf->count == 1)
		d_inf->a = d_inf->a * -1;
	return (d_inf->a);
}

double				ft_atof(const char *str)
{
	t_double_inf	d_inf;

	init_structure(&d_inf);
	while (*str && (*str == ' ' || *str == '\n' || *str == '\t'\
				|| *str == '\r' || *str == '\v' || *str == '\f'))
		str++;
	if (*str == '-' && str++)
		d_inf.count = 1;
	while ((d_inf.c = *str++) != 0 && ft_isdigit(d_inf.c))
		d_inf.a = d_inf.a * 10.0 + (d_inf.c - '0');
	d_pow(&d_inf, (char*)str);
	return (find_double(&d_inf));
}
