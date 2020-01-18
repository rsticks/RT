/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 19:21:43 by daron             #+#    #+#             */
/*   Updated: 2019/11/16 14:19:40 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strncat(char *destination, const char *append, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (destination[i])
		i++;
	j = 0;
	while (append[j] != '\0' && j < n)
	{
		destination[i] = append[j];
		i++;
		j++;
	}
	destination[i] = '\0';
	return (destination);
}
