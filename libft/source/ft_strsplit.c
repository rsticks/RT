/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 12:59:02 by daron             #+#    #+#             */
/*   Updated: 2019/11/16 14:19:40 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static unsigned int	ft_swap_space(char *str, unsigned int i, char space)
{
	while (str[i] == space && str[i])
		i++;
	return (i);
}

static unsigned int	ft_word_count(char *str, char delim)
{
	unsigned int	i;
	unsigned int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != delim)
		{
			count++;
			while (str[i] != delim && str[i])
				i++;
		}
		else
			i++;
	}
	return (count);
}

static char			*ft_new_word(char *str, char delim)
{
	unsigned int	i;
	unsigned int	w_len;
	char			*ptr;

	i = 0;
	w_len = 0;
	while (str[w_len] != delim && str[w_len])
		w_len++;
	if (!(ptr = (char*)malloc(sizeof(char) * (w_len + 1))))
		return (NULL);
	while (i < w_len)
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

static	char		**free_list(char **list)
{
	unsigned int	i;

	i = 0;
	while (list[i])
		free(list[i++]);
	free(list);
	return (NULL);
}

char				**ft_strsplit(char const *str, char c)
{
	unsigned int	i;
	unsigned int	j;
	char			**mas;
	unsigned int	count;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	count = ft_word_count((char*)str, c);
	if (!(mas = (char**)malloc(sizeof(char*) * (count + 1))))
		return (NULL);
	while (i < count)
	{
		j = ft_swap_space((char*)str, j, c);
		if (!(mas[i] = ft_new_word((char*)&str[j], c)))
			return (free_list(mas));
		j = j + (unsigned int)ft_strlen(mas[i]);
		i++;
	}
	mas[i] = NULL;
	return (mas);
}
