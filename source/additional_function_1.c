/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_function_1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:30:37 by daron             #+#    #+#             */
/*   Updated: 2019/11/28 16:27:41 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	scene_mas(t_sdl *sdl)
{
	int	ind;

	ind = -1;
	while (++ind < sdl->line_count)
		free(sdl->scene[ind]);
	free(sdl->scene);
}
