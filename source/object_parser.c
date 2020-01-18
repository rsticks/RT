/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 14:51:17 by daron             #+#    #+#             */
/*   Updated: 2019/11/28 16:28:15 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			ft_add_plane(t_sdl *sdl, int *k, int ind)
{
	t_object	*link;

	if (!(link = (t_object*)malloc(sizeof(t_object))))
		kill_all("Can't create object <ft_add_cyl_cone>");
	if (ft_strcmp(sdl->scene[*k + 1], "	{") != 0 ||
	ft_strcmp(sdl->scene[*k + 6], "	}") != 0)
		kill_all("Plane not in well format 1 <ft_add_cyl_cone>");
	ft_col_n_pos(sdl, link, *k);
	if (ft_strncmp(sdl->scene[*k + 4], "		rot(", 6) != 0)
		kill_all("Plane not in well format 2 <ft_add_cyl_cone>");
	link->rot.x = (float)ft_atoi_n(sdl->scene[*k + 4], &ind);
	link->rot.y = (float)ft_atoi_n(sdl->scene[*k + 4], &ind);
	link->rot.z = (float)ft_atoi_n(sdl->scene[*k + 4], &ind);
	if (sdl->scene[*k + 4][ind] != ')')
		kill_all("Plane not in well format 3 <ft_add_cyl_cone>");
	ind = 6;
	if (ft_strncmp(sdl->scene[*k + 5], "		spc(", 6) != 0)
		kill_all("Cone not in well format 7 <ft_add_cyl_cone>");
	link->specular = ft_atoi_n(sdl->scene[*k + 5], &ind);
	if (sdl->scene[*k + 5][ind] != ')')
		kill_all("Cone not in well format 8 <ft_add_cyl_cone>");
	link->next = NULL;
	link->name = PLANE_ID;
	sdl->obj = ft_add_object_link(sdl, link);
	*k += 7;
}

void			ft_add_sphere(t_sdl *sdl, int *k, int ind)
{
	t_object	*link;

	if (!(link = (t_object*)malloc(sizeof(t_object))))
		kill_all("Can't create object <ft_add_sphere>");
	if (ft_strcmp(sdl->scene[*k + 1], "	{") != 0 ||
	ft_strcmp(sdl->scene[*k + 6], "	}") != 0)
		kill_all("Sphere not in well format 1 <ft_add_sphere>");
	ft_col_n_pos(sdl, link, *k);
	if (ft_strncmp(sdl->scene[*k + 4], "		size(", 7) != 0)
		kill_all("Sphere not in well format 2 <ft_add_sphere>");
	link->r = (double)ft_atoi_n(sdl->scene[*k + 4], &ind);
	if (sdl->scene[*k + 4][ind] != ')')
		kill_all("Sphere not in well format 3 <ft_add_sphere>");
	ind = 6;
	if (ft_strncmp(sdl->scene[*k + 5], "		spc(", 6) != 0)
		kill_all("Cone not in well format 4 <ft_add_sphere>");
	link->specular = ft_atoi_n(sdl->scene[*k + 5], &ind);
	if (sdl->scene[*k + 5][ind] != ')')
		kill_all("Cone not in well format 5 <ft_add_sphere>");
	link->name = SPHERE_ID;
	link->next = NULL;
	sdl->obj = ft_add_object_link(sdl, link);
	*k += 7;
}

static void		ft_add_cyl_cone_1(t_sdl *sdl, int *k, int name, t_object *link)
{
	int			ind;

	ind = 6;
	if (ft_strncmp(sdl->scene[*k + 6], "		spc(", 6) != 0)
		kill_all("Cone not in well format 7 <ft_add_cyl_cone>");
	link->specular = ft_atoi_n(sdl->scene[*k + 6], &ind);
	if (sdl->scene[*k + 6][ind] != ')')
		kill_all("Cone not in well format 8 <ft_add_cyl_cone>");
	link->name = name;
	link->next = NULL;
	sdl->obj = ft_add_object_link(sdl, link);
	*k += 8;
}

void			ft_add_cyl_cone(t_sdl *sdl, int *k, int name, int ind)
{
	t_object	*link;

	if (!(link = (t_object*)malloc(sizeof(t_object))))
		kill_all("Can't create object <ft_add_cyl_cone>");
	if (ft_strcmp(sdl->scene[*k + 1], "	{") != 0
		|| ft_strcmp(sdl->scene[*k + 7], "	}") != 0)
		kill_all("Cone not in well format 1 <ft_add_cyl_cone>");
	ft_col_n_pos(sdl, link, *k);
	if (ft_strncmp(sdl->scene[*k + 4], "		rot(", 6) != 0)
		kill_all("Cone not in well format 2 <ft_add_cyl_cone>");
	link->rot.x = (float)ft_atoi_n(sdl->scene[*k + 4], &ind);
	link->rot.y = (float)ft_atoi_n(sdl->scene[*k + 4], &ind);
	link->rot.z = (float)ft_atoi_n(sdl->scene[*k + 4], &ind);
	if (sdl->scene[*k + 4][ind] != ')')
		kill_all("Cone not in well format 3 <ft_add_cyl_cone>");
	if (ft_strncmp(sdl->scene[*k + 5], "		size(", 7) != 0)
		kill_all("Cone not in well format 4 <ft_add_cyl_cone>");
	ind = 7;
	link->r = (double)ft_atoi_n(sdl->scene[*k + 5], &ind);
	if (sdl->scene[*k + 5][ind] != ')')
		kill_all("Cone not in well format 5 <ft_add_cyl_cone>");
	ft_add_cyl_cone_1(sdl, k, name, link);
}
