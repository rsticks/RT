/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 17:22:32 by daron             #+#    #+#             */
/*   Updated: 2020/03/06 13:46:26 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memcpy(void *destination, const void *source, size_t n)
{
	size_t			i;
	unsigned char	*dest;
	unsigned char	*sors;

	if (destination == NULL && source == NULL)
		return (NULL);
	dest = (unsigned char*)destination;
	sors = (unsigned char*)source;
	i = 0;
	while (i < n)
	{
		dest[i] = sors[i];
		i++;
	}
	return (destination);
}
