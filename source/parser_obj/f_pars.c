/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_pars.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 15:42:46 by rsticks           #+#    #+#             */
/*   Updated: 2020/03/06 13:46:27 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "pars_obj.h"

char			*f_pars_x(t_parse_obj *data, char *c, u_int32_t count)
{
	t_int_vec	x;
	int			i;

	x.x = 0;
	x.y = 0;
	x.z = 0;
	x.x = ft_atoi(c);
	c = while_not_slash(c, &i);
	if (!i)
		return (c);
	x.y = ft_atoi(c);
	c = while_not_slash(c, &i);
	if (!i)
		return (c);
	x.z = ft_atoi(c);
	data->d_obj[count].vf.x = x.x;
	data->d_obj[count].vtf.x = x.y;
	data->d_obj[count].vnf.x = x.z;
	return (c);
}

char			*f_pars_y(t_parse_obj *data, char *c, u_int32_t count)
{
	int			i;
	t_int_vec	y;

	y.x = 0;
	y.y = 0;
	y.z = 0;
	y.x = ft_atoi(c);
	c = while_not_slash(c, &i);
	if (!i)
		return (c);
	y.y = ft_atoi(c);
	c = while_not_slash(c, &i);
	if (!i)
		return (c);
	y.z = ft_atoi(c);
	data->d_obj[count].vf.y = y.x;
	data->d_obj[count].vtf.y = y.y;
	data->d_obj[count].vnf.y = y.z;
	return (c);
}

char			*f_pars_z(t_parse_obj *data, char *c, u_int32_t count)
{
	int			i;
	t_int_vec	z;

	z.x = 0;
	z.y = 0;
	z.z = 0;
	z.x = ft_atoi(c);
	c = while_not_slash(c, &i);
	if (!i)
		return (c);
	z.y = ft_atoi(c);
	c = while_not_slash(c, &i);
	if (!i)
		return (c);
	z.z = ft_atoi(c);
	data->d_obj[count].vf.z = z.x;
	data->d_obj[count].vtf.z = z.y;
	data->d_obj[count].vnf.z = z.z;
	return (c);
}
