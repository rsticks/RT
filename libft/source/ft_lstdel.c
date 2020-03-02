/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 11:05:20 by daron             #+#    #+#             */
/*   Updated: 2020/03/02 14:55:12 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *next;
	t_list *p_list;

	if (alst == NULL || *alst == NULL || !del)
		return ;
	p_list = *alst;
	while (p_list != NULL)
	{
		next = p_list->next;
		ft_lstdelone(&p_list, del);
		p_list = next;
	}
	*alst = NULL;
}
