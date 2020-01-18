/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 17:42:32 by daron             #+#    #+#             */
/*   Updated: 2019/11/16 14:19:40 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char		*ft_strdup(const char *str)
{
	char	*newstr;
	size_t	count;
	size_t	i;

	count = 0;
	count = ft_strlen(str);
	if (!(newstr = (char*)malloc(sizeof(char) * (count + 1))))
		return (NULL);
	i = 0;
	while (i < count)
	{
		newstr[i] = str[i];
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}
