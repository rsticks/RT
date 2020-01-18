/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_function.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 15:54:57 by daron             #+#    #+#             */
/*   Updated: 2019/11/28 16:27:44 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int				ft_atoi_n(char *str, int *k)
{
	int			s;
	int			r;

	r = 0;
	s = 1;
	while (str[*k] >= 0 && str[*k] <= 32)
		(*k)++;
	if (str[*k] == '-')
		s = -1;
	if (str[*k] == '+' || str[*k] == '-')
		(*k)++;
	while (str[*k] && str[*k] >= '0' && str[*k] <= '9')
	{
		r = r * 10 + str[*k] - '0';
		(*k)++;
	}
	return (s * r);
}

t_object		*ft_add_object_link(t_sdl *sdl, t_object *link)
{
	t_object	*head;

	head = sdl->obj;
	if (sdl->obj == NULL)
		return (link);
	while (sdl->obj->next != NULL)
		sdl->obj = sdl->obj->next;
	sdl->obj->next = link;
	return (head);
}

t_light			*ft_add_light_link(t_sdl *sdl, t_light *link)
{
	t_light		*head;

	head = sdl->light;
	if (sdl->light == NULL)
		return (link);
	while (sdl->light->next != NULL)
		sdl->light = sdl->light->next;
	sdl->light->next = link;
	return (head);
}

static void		my_sdl_free(t_sdl *sdl)
{
	SDL_DestroyRenderer(sdl->render);
	SDL_DestroyWindow(sdl->window);
	SDL_Quit();
}

void			my_free(t_sdl *sdl)
{
	t_object	*obj;
	t_object	*obj_next;
	t_light		*light;
	t_light		*light_next;
	int			ind;

	obj = sdl->obj;
	while (obj)
	{
		obj_next = obj->next;
		free(obj);
		obj = obj_next;
	}
	light = sdl->light;
	while (light)
	{
		light_next = light->next;
		free(light);
		light = light_next;
	}
	ind = -1;
	my_sdl_free(sdl);
}
