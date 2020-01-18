/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 14:34:47 by daron             #+#    #+#             */
/*   Updated: 2019/11/28 16:28:13 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_object	*mouse_intersection(double u, double v,
		t_vector *pos, t_sdl *sdl)
{
	t_vector	i;
	t_vector	j;
	t_vector	k;
	t_vector	ray_dir;

	k = vec_sub(&SC.rot, pos);
	k = vec_norm(&k);
	i = vec_cross(&k, &(t_vector){0.0, 1.0, 0.0});
	i = vec_norm(&i);
	j = vec_cross(&i, &k);
	ray_dir = (t_vector){u * i.x + v * j.x + FOV * k.x,
						u * i.y + v * j.y + FOV * k.y,
						u * i.z + v * j.z + FOV * k.z};
	ray_dir = vec_norm(&ray_dir);
	return (intersection(sdl, &ray_dir, pos));
}

void			mouse_down(t_sdl *sdl)
{
	int			x;
	int			y;
	double		u;
	double		v;
	t_vector	pos;

	if (SDL_BUTTON_LEFT == sdl->event.button.button)
	{
		SDL_GetMouseState(&x, &y);
		u = (W_WIDTH - (double)x * 2.0) / W_HEIGHT;
		v = (W_HEIGHT - (double)y * 2.0) / W_WIDTH;
		pos = (t_vector){SC.pos.x + u, SC.pos.y + v, SC.pos.z};
		SSO = mouse_intersection(u, v, &pos, sdl);
	}
}
