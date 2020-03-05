/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cheaker_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 17:05:57 by daron             #+#    #+#             */
/*   Updated: 2020/03/05 17:06:30 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		cheak_part(t_rt *rt)
{
	if (rt->scene.check[0] == 0)
		kill_all("ERROR: You must create camera");
	else if (rt->scene.check[2] == 0)
		kill_all("ERROR: You must create scene");
	else if (rt->scene.check[3] == 0)
		kill_all("ERROR: You must create at least one object");
}
