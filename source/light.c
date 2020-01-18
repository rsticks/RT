/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:31:50 by daron             #+#    #+#             */
/*   Updated: 2019/11/28 16:28:06 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		ft_add_light_two(t_sdl *sdl, int *k, int ind, t_light *link)
{
	ind = 6;
	link->pos.x = ft_atoi_n(sdl->scene[*k + 3], &ind);
	link->pos.y = ft_atoi_n(sdl->scene[*k + 3], &ind);
	link->pos.z = ft_atoi_n(sdl->scene[*k + 3], &ind);
	if (sdl->scene[*k + 3][ind] != ')')
		kill_all("Light not in well format 4 <ft_add_light>");
	ind = 6;
	link->inten = (double)ft_atoi_n(sdl->scene[*k + 4], &ind) / 100;
	if (sdl->scene[*k + 4][ind] != ')')
		kill_all("Light not in well format 5 <ft_add_light>");
	link->next = NULL;
	sdl->light = ft_add_light_link(sdl, link);
	*k += 6;
}

void			ft_add_light(t_sdl *sdl, int *k, int ind)
{
	t_light		*link;

	if (!(link = (t_light*)malloc(sizeof(t_light))))
		kill_all("Can't create light <ft_add_light>");
	if (ft_strcmp(sdl->scene[*k + 1], "	{") != 0
	|| ft_strcmp(sdl->scene[*k + 5], "	}") != 0)
		kill_all("Light not in well format 1 <ft_add_light>");
	if (ft_strncmp(sdl->scene[*k + 2], "		col(", 6) != 0 ||
		ft_strncmp(sdl->scene[*k + 3], "		pos(", 6) != 0 ||
		ft_strncmp(sdl->scene[*k + 4], "		int(", 6) != 0)
		kill_all("Light not in well format 2 <ft_add_light>");
	link->col.r = ft_atoi_n(sdl->scene[*k + 2], &ind);
	link->col.g = ft_atoi_n(sdl->scene[*k + 2], &ind);
	link->col.b = ft_atoi_n(sdl->scene[*k + 2], &ind);
	if (sdl->scene[*k + 2][ind] != ')')
		kill_all("Light not in well format 3 <ft_add_light>");
	ft_add_light_two(sdl, k, ind, link);
}
