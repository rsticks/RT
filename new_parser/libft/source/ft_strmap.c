/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 10:08:58 by daron             #+#    #+#             */
/*   Updated: 2019/11/16 14:19:40 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char		*ft_strmap(char const *s, char (*f)(char))
{
	size_t	i;
	size_t	len;
	char	*ptr;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	if (!f || !(ptr = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	ft_bzero(ptr, (size_t)(len + 1));
	i = -1;
	while (s[++i])
		ptr[i] = f(s[i]);
	return (ptr);
}
