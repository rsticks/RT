/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 19:31:50 by daron             #+#    #+#             */
/*   Updated: 2019/11/16 14:19:40 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char		*ft_strnstr(const char *str_b, const char *str_a, size_t len)
{
	size_t	i;
	size_t	j;

	if (!*str_a)
		return ((char*)str_b);
	i = 0;
	while (str_b[i] && i < len)
	{
		if (str_b[i] == str_a[0])
		{
			j = 0;
			while (str_b[i + j] == str_a[j] &&\
					str_b[i + j] && str_a[j] && (j + i) < len)
				j++;
			if (str_a[j] == '\0')
				return ((char*)(str_b + i));
		}
		i++;
	}
	return (NULL);
}
