/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 17:44:58 by daron             #+#    #+#             */
/*   Updated: 2020/03/06 13:46:26 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strcpy(char *destination, const char *source)
{
	size_t	i;

	i = 0;
	while (source[i])
	{
		destination[i] = source[i];
		i++;
	}
	destination[i] = '\0';
	return (destination);
}
