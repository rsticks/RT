/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 10:38:06 by daron             #+#    #+#             */
/*   Updated: 2019/11/16 14:19:40 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	ft_nbr_out_fd(int nbr, int fd)
{
	if (nbr / 10)
		ft_nbr_out_fd(nbr / 10, fd);
	ft_putchar_fd((unsigned char)(nbr % 10 + '0'), fd);
}

void			ft_putnbr_fd(int nbr, int fd)
{
	if (nbr == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else
	{
		if (nbr < 0)
		{
			nbr = -nbr;
			ft_putchar_fd('-', fd);
		}
		ft_nbr_out_fd(nbr, fd);
	}
}
