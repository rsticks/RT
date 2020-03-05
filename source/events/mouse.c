/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzina <kzina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 14:34:47 by daron             #+#    #+#             */
/*   Updated: 2020/03/01 18:52:51 by kzina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	mouse_intersection(double u, double v,
		t_vector *pos, t_rt *rt)
{
	t_vector	i;
	t_vector	j;
	t_vector	k;
	t_vector	ray_dir;

	k = vec_sub(&rt->cam.dir, pos);
	k = vec_norm(&k);
	i = vec_cross(&k, &(t_vector){0.0, 1.0, 0.0});
	i = vec_norm(&i);
	j = vec_cross(&i, &k);
	ray_dir = (t_vector){u * i.x + v * j.x + FOV * k.x,
						u * i.y + v * j.y + FOV * k.y,
						u * i.z + v * j.z + FOV * k.z};
	ray_dir = vec_norm(&ray_dir);
	return (intersection(rt, &ray_dir, pos));
}

void		m_down_menu(t_rt *rt)
{
	int			x;
	int			y;
	//t_vector	pos;

	if (SDL_BUTTON_LEFT == rt->event.button.button)
	{
		SDL_GetMouseState(&x, &y);	
		//refresh_menu(rt);
	}
}

void		mouse_down(t_rt *rt)
{
	int			x;
	int			y;
	double		u;
	double		v;
	t_vector	pos;

	if (SDL_BUTTON_LEFT == rt->event.button.button)
	{
		SDL_GetMouseState(&x, &y);
		u = (rt->window.size[0] - (double)x * 2.0) / rt->window.size[1];
		v = (rt->window.size[1] - (double)y * 2.0) / rt->window.size[0];
		pos = (t_vector){rt->cam.pos.x + u, rt->cam.pos.y + v, rt->cam.pos.z};
		rt->select_obj = mouse_intersection(u, v, &pos, rt);
		refresh_menu(rt);
	}
}
