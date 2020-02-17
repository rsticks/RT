/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_islowcase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 19:41:28 by daron             #+#    #+#             */
/*   Updated: 2020/02/11 13:15:09 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_islowcase(char c)
{
	if (((c) >= 0x61) && ((c) <= 0x7A))
		return (1);
	return (0);
}
