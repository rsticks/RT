/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 10:23:46 by daron             #+#    #+#             */
/*   Updated: 2019/11/16 14:19:40 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int		ft_is_space(char c)
{
	return (c == '\n' || c == '\t' || c == ' ');
}

static size_t	ft_spaceswap(char *str, size_t i)
{
	while (ft_is_space(str[i]))
		i++;
	return (i);
}

static size_t	ft_space_len(char *str)
{
	size_t		i;
	size_t		len;

	i = ft_spaceswap(str, 0);
	len = 0;
	while (str[i])
	{
		i++;
		len++;
	}
	if (len)
	{
		while (ft_is_space(str[i - 1]))
		{
			i--;
			len--;
		}
	}
	return (len);
}

char			*ft_strtrim(char const *str)
{
	char		*ptr;
	size_t		i;
	size_t		len;
	size_t		j;

	if (!str)
		return (NULL);
	j = 0;
	len = ft_space_len((char*)str);
	if (!(ptr = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	else
	{
		i = ft_spaceswap((char*)str, 0);
		while (j < len)
		{
			ptr[j] = str[i + j];
			j++;
		}
	}
	ptr[j] = '\0';
	return (ptr);
}
