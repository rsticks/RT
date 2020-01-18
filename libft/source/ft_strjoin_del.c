/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_del.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 15:42:55 by daron             #+#    #+#             */
/*   Updated: 2019/11/28 16:29:45 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

static void	ft_free(char *s1, char *s2, int type)
{
	if (type == 'L')
		free(s1);
	else if (type == 'R')
		free(s2);
	else if (type == 'B')
	{
		free(s1);
		free(s2);
	}
}

char		*ft_strjoin_del(char *s1, char *s2, char type)
{
	char	*new_str;
	int		i[2];

	i[0] = 0;
	while (s1[i[0]])
		i[0]++;
	i[1] = 0;
	while (s2[i[1]])
		i[1]++;
	new_str = (char *)malloc(sizeof(char) * (i[0] + i[1] + 1));
	i[0] = 0;
	while (s1[i[0]])
	{
		new_str[i[0]] = s1[i[0]];
		i[0]++;
	}
	i[1] = 0;
	while (s2[i[1]])
	{
		new_str[i[0] + i[1]] = s2[i[1]];
		i[1]++;
	}
	ft_free(s1, s2, type);
	new_str[i[0] + i[1]] = '\0';
	return (new_str);
}
