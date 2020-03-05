/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliary.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzina <kzina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 12:15:38 by kzina             #+#    #+#             */
/*   Updated: 2020/03/01 15:58:07 by kzina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

inline void swap(char *x, char *y)
{
	char t = *x; *x = *y; *y = t;
}

char		*reverse(char *buffer, int i, int j)
{
	while (i < j)
		swap(&buffer[i++], &buffer[j--]);

	return buffer;
}

char		*itoa(int value, char* buffer)
{
	int base;
	int n = abs(value);

	base = 10;
	int i = 0;
	while (n)
	{
		int r = n % base;

		if (r >= 10) 
			buffer[i++] = 65 + (r - 10);
		else
			buffer[i++] = 48 + r;

		n = n / base;
	}
	if (i == 0)
		buffer[i++] = '0';
	if (value < 0 && base == 10)
		buffer[i++] = '-';

	buffer[i] = '\0';
	return reverse(buffer, 0, i - 1);
}

void		calc_shift(int comp, t_rt *rt)
{
	int		count;

	count = 0;
	if(comp < 0)
		count++;
	comp = abs(comp);
	while(comp >= 10)
	{
		comp /= 10;
		count++;
	}
	rt->ui.shift = count * 5;
}