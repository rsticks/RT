/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 17:40:31 by daron             #+#    #+#             */
/*   Updated: 2020/02/09 15:36:22 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t				ft_strlen(const char *str)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = (unsigned char*)str;
	i = 0;
	while (ptr[i] != '\0')
		i++;
	return (i);
}
