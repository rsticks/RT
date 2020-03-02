/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap_space.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 12:58:32 by daron             #+#    #+#             */
/*   Updated: 2020/03/02 14:55:12 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_space_swap(const char *space, const char *str, int i)
{
	while (str[i] && ft_detect_space(space, str[i]))
		i++;
	return (i);
}
