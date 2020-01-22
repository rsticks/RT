/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 17:49:06 by daron             #+#    #+#             */
/*   Updated: 2019/11/16 14:19:40 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strncpy(char *destination, const char *source, size_t n)
{
	size_t	i;

	i = 0;
	while (source[i] && i < n)
	{
		destination[i] = source[i];
		i++;
	}
	while (i < n)
	{
		destination[i] = '\0';
		i++;
	}
	return (destination);
}
