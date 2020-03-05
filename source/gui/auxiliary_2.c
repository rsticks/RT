/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliary_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzina <kzina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 17:29:38 by kzina             #+#    #+#             */
/*   Updated: 2020/03/05 18:42:47 by kzina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		revers(char *str, int len)
{
	int		i;
	int		j;
	int		temp;

	i = 0;
	j = len - 1;
	while (i < j)
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}
}

int			inttostr(int x, char *str, int d)
{
	int		i;

	i = 0;
	while (x)
	{
		str[i++] = (x % 10) + '0';
		x = x / 10;
	}
	while (i < d)
		str[i++] = '0';
	revers(str, i);
	str[i] = '\0';
	return (i);
}

void		ftoa(float n, char *res, int afterpoint)
{
	int		ipart;
	float	fpart;
	int		i;
	int		flag;

	flag = 1;
	if (n < 0)
	{
		n = fabs(n);
		flag = -1;
	}
	ipart = (int)n;
	fpart = n - (float)ipart;
	i = inttostr(ipart, res, 0);
	if (afterpoint != 0)
	{
		if (flag == -1)
			res[i++] = '-';
		res[i] = '.';
		fpart = fpart * pow(10, afterpoint);
		inttostr((int)fpart, res + i + (flag == -1 ? 2 : 1), afterpoint);
	}
}
