/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 17:25:04 by daron             #+#    #+#             */
/*   Updated: 2019/11/16 14:19:40 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_memccpy(void *destination, const void *source, int c, size_t n)
{
	size_t			i;
	unsigned char	*dest;
	unsigned char	*sors;

	dest = (unsigned char*)destination;
	sors = (unsigned char*)source;
	i = 0;
	while (i < n)
	{
		dest[i] = sors[i];
		if (sors[i] == (unsigned char)c)
			return ((void*)(destination + i + 1));
		i++;
	}
	return (NULL);
}
