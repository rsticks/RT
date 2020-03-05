/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 19:24:30 by daron             #+#    #+#             */
/*   Updated: 2020/03/05 16:41:39 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strchr(const char *str, int ch)
{
	size_t i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ch)
			return ((char*)(str + i));
		i++;
	}
	if (str[i] == ch)
		return ((char*)(str + i));
	return (NULL);
}
