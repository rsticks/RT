/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtruman <mtruman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 14:52:00 by vkuksa            #+#    #+#             */
/*   Updated: 2020/03/05 18:22:38 by mtruman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		write_tx(t_rt *rt)
{
	int			i;
	int			h;
	int			j;
	SDL_Surface	*surf;

	i = -1;
	while (++i < rt->scene.obj_c)
		if (rt->obj_mas[i].text_on && (surf = IMG_Load(rt->obj_mas[i].texture)))
		{
			h = -1;
			while (++h < surf->h)
			{
				j = -1;
				while (++j < surf->w)
					rt->txt_gpu.tx[h * surf->w + j +
					rt->txt_gpu.txdata[rt->obj_mas[i].texture_id].start] =
							((unsigned int *)surf->pixels)[h * surf->w + j];
			}
			SDL_FreeSurface(surf);
		}
}

int			fill_txdata(t_txdata *txdata, SDL_Surface *surf,
		int tex_id, t_rt *rt)
{
	unsigned int	start;

	start = 0;
	txdata[tex_id].height = (unsigned int)surf->h;
	txdata[tex_id].width = (unsigned int)surf->w;
	if (tex_id == 0)
		txdata[tex_id].start = 0;
	else
		txdata[tex_id].start = rt->txt_gpu.total_size + 1;
	start = txdata[tex_id].width * txdata[tex_id].height;
	return (start);
}

static void	count_pict(t_rt *rt)
{
	int				i;
	SDL_Surface		*surf;

	i = -1;
	rt->txt_gpu.tx_count = 0;
	while (++i < rt->scene.obj_c)
		if (rt->obj_mas[i].text_on &&
		(surf = IMG_Load(rt->obj_mas[i].texture)))
		{
			rt->txt_gpu.tx_count += 1;
			SDL_FreeSurface(surf);
		}
	if (!(rt->txt_gpu.txdata = (t_txdata*)malloc(sizeof(t_txdata) *
			rt->txt_gpu.tx_count)))
		kill_all("COUNT_PICT FUCKED UP WITH MALLOC");
}

void		texture_init(t_rt *rt)
{
	int				i;
	int				text_id;
	SDL_Surface		*surf;

	count_pict(rt);
	text_id = 0;
	i = -1;
	while (++i < rt->scene.obj_c)
		if (rt->obj_mas[i].text_on && (surf = IMG_Load(rt->obj_mas[i].texture)))
		{
			rt->txt_gpu.total_size +=
					fill_txdata(rt->txt_gpu.txdata, surf, text_id, rt);
			rt->obj_mas[i].texture_id = text_id;
			text_id++;
			SDL_FreeSurface(surf);
		}
	if (!(rt->txt_gpu.tx = (int*)malloc(sizeof(int) * rt->txt_gpu.total_size)))
		kill_all("TEXTURE_INIT FUCKED UP WITH MALLOC");
	write_tx(rt);
}
