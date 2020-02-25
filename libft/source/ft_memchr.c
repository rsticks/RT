/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 17:31:06 by daron             #+#    #+#             */
/*   Updated: 2020/02/18 14:14:00 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memchr(const void *arr, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = (unsigned char*)arr;
	i = 0;
	while (i < n)
	{
		if (*ptr == (unsigned char)c)
			return (ptr);
		else
		{
			i++;
			ptr++;
		}
	}
	return (NULL);
}
