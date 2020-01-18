/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 19:38:16 by daron             #+#    #+#             */
/*   Updated: 2019/11/16 14:19:40 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_is_valid(const char *nbr, int flag)
{
	size_t			len;

	len = 0;
	while (nbr[len] >= '0' && nbr[len] <= '9')
		len++;
	if (flag == -1)
	{
		if ((len == 19 && ft_strcmp(nbr, "9223372036854775808") > 0) \
				|| len > 19)
			return (0);
	}
	else
	{
		if ((len == 19 && ft_strcmp(nbr, "9223372036854775807") > 0) \
				|| len > 19)
			return (-1);
	}
	return (1);
}

int					ft_atoi(const char *str)
{
	unsigned int	res;
	int				negative;

	negative = 1;
	res = 0;
	while (*str && (*str == ' ' || *str == '\n' || *str == '\t'\
				|| *str == '\r' || *str == '\v' || *str == '\f'))
		++str;
	if (*str == '-')
		negative = -1;
	if (*str == '-' || *str == '+')
		++str;
	if (ft_is_valid(str, negative) < 1)
		return (ft_is_valid(str, negative));
	while (*str && *str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - 48);
		++str;
	}
	return (res * negative);
}
