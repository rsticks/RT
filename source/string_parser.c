/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:03:44 by daron             #+#    #+#             */
/*   Updated: 2019/11/28 16:28:21 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		ft_checkscene_1(t_sdl *sdl, int ind)
{
	if (ft_strncmp(sdl->scene[4], "	ambient(", 9) != 0)
		kill_all("Error in scene 7 <ft_checkscene>");
	ind = 9;
	sdl->ambient = (float)ft_atoi_n(sdl->scene[4], &ind) / 100;
	if (sdl->scene[4][ind] != ')')
		kill_all("Error in scene 8 <ft_checkscene>");
	if (ft_strlen(sdl->scene[6]) != 0)
		kill_all("Error in scene 9 <ft_checkscene>");
}

static void		ft_checkscene(t_sdl *sdl, int ind)
{
	if (ft_strcmp(sdl->scene[0], "scene") != 0)
		kill_all("Error in scene 1 <ft_checkscene>");
	if (ft_strcmp(sdl->scene[1], "{") != 0 ||
	ft_strcmp(sdl->scene[5], "}") != 0)
		kill_all("Error in scene 2 <ft_checkscene>");
	if (ft_strncmp(sdl->scene[2], "	cam_pos(", 9) != 0)
		kill_all("Error in scene 3 <ft_checkscene>");
	sdl->cam.pos.x = (float)ft_atoi_n(sdl->scene[2], &ind);
	sdl->cam.pos.y = (float)ft_atoi_n(sdl->scene[2], &ind);
	sdl->cam.pos.z = (float)ft_atoi_n(sdl->scene[2], &ind);
	if (sdl->scene[2][ind] != ')')
		kill_all("Error in scene 4 <ft_checkscene>");
	if (ft_strncmp(sdl->scene[3], "	cam_dir(", 9) != 0)
		kill_all("Error in scene 5 <ft_checkscene>");
	ind = 9;
	sdl->cam.rot.x = (float)ft_atoi_n(sdl->scene[3], &ind);
	sdl->cam.rot.y = (float)ft_atoi_n(sdl->scene[3], &ind);
	sdl->cam.rot.z = (float)ft_atoi_n(sdl->scene[3], &ind);
	if (sdl->scene[3][ind] != ')')
		kill_all("Error in scene 6 <ft_checkscene>");
	ft_checkscene_1(sdl, ind);
}

static void		ft_parse_objects(t_sdl *sdl, int k)
{
	while (k < sdl->line_count - 1)
	{
		if (ft_strcmp(sdl->scene[k], "	object(light)") == 0)
			ft_add_light(sdl, &k, 6);
		else if (ft_strcmp(sdl->scene[k], "	object(cone)") == 0)
			ft_add_cyl_cone(sdl, &k, CONE_ID, 6);
		else if (ft_strcmp(sdl->scene[k], "	object(cylinder)") == 0)
			ft_add_cyl_cone(sdl, &k, CYLINDER_ID, 6);
		else if (ft_strcmp(sdl->scene[k], "	object(plane)") == 0)
			ft_add_plane(sdl, &k, 6);
		else if (ft_strcmp(sdl->scene[k], "	object(sphere)") == 0)
			ft_add_sphere(sdl, &k, 7);
		else
			kill_all("Use forbidden object type <ft_parse_objects>");
	}
}

void			ft_col_n_pos(t_sdl *sdl, t_object *link, int k)
{
	int			ind;

	ind = 6;
	if (ft_strncmp(sdl->scene[k + 2], "		col(", 6) != 0 ||
		ft_strncmp(sdl->scene[k + 3], "		pos(", 6) != 0)
		kill_all("Problem with col or pos <ft_col_n_pos>");
	link->col.r = ft_atoi_n(sdl->scene[k + 2], &ind);
	link->col.g = ft_atoi_n(sdl->scene[k + 2], &ind);
	link->col.b = ft_atoi_n(sdl->scene[k + 2], &ind);
	if (sdl->scene[k + 2][ind] != ')')
		kill_all("Problem col <ft_col_n_pos>");
	ind = 6;
	link->pos.x = ft_atoi_n(sdl->scene[k + 3], &ind);
	link->pos.y = ft_atoi_n(sdl->scene[k + 3], &ind);
	link->pos.z = ft_atoi_n(sdl->scene[k + 3], &ind);
	if (sdl->scene[k + 3][ind] != ')')
		kill_all("Problem pos <ft_col_n_pos>");
}

void			string_parser(t_sdl *sdl)
{
	ft_checkscene(sdl, 9);
	if (ft_strcmp(sdl->scene[7], "content") != 0 ||
			ft_strcmp(sdl->scene[8], "{") != 0 ||
			ft_strcmp(sdl->scene[sdl->line_count - 1], "}") != 0)
		kill_all("Can't find content <string_parser>");
	ft_parse_objects(sdl, 9);
	scene_mas(sdl);
	check_object(sdl);
}
