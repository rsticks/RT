/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 10:27:08 by daron             #+#    #+#             */
/*   Updated: 2019/11/16 14:19:40 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbrlen(int n)
{
	int		i;

	i = 0;
	if (n < 0)
	{
		n = n * -1;
		i++;
	}
	while (n / 10)
	{
		n = n / 10;
		i++;
	}
	return (i + 1);
}

static char	*ft_min_int(void)
{
	char	*ptr;

	ptr = ft_memalloc(12);
	ptr[0] = '-';
	ptr[1] = '2';
	ptr[2] = '1';
	ptr[3] = '4';
	ptr[4] = '7';
	ptr[5] = '4';
	ptr[6] = '8';
	ptr[7] = '3';
	ptr[8] = '6';
	ptr[9] = '4';
	ptr[10] = '8';
	return (ptr);
}

char		*ft_itoa(int n)
{
	char	*ptr;
	int		len;
	int		i;
	int		nn;

	if (n == -2147483648)
		return (ft_min_int());
	len = ft_nbrlen(n);
	if (!(ptr = ft_memalloc(len + 1)))
		return (NULL);
	i = 1;
	nn = n;
	if (nn < 0)
		nn = -n;
	while (nn > 0)
	{
		ptr[len - i] = nn % 10 + '0';
		nn = nn / 10;
		i++;
	}
	ptr[len - i] = nn % 10 + '0';
	if (n < 0)
		ptr[0] = '-';
	return (ptr);
}
