/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtruman <mtruman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 14:52:00 by vkuksa            #+#    #+#             */
/*   Updated: 2020/03/04 14:59:20 by mtruman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
# include <SDL_image.h>

void		write_tx(t_rt *rt)
{
	int		i;
	int 	h;
	int		j;
	SDL_Surface *surf;

	i = -1;
	while(++i < rt->scene.obj_c)
		if(rt->obj_mas[i].text_on)
		{
			h = -1;
			surf = IMG_Load(rt->obj_mas[i].texture);
			while (++h < surf->h)
			{
				j = -1;
				while (++j < surf->w)
					rt->txt_gpu.tx[h * surf->w + j + rt->txt_gpu.txdata[rt->obj_mas[i].texture_id].start] = ((unsigned int *)surf->pixels)[h * surf->w + j];
			}
		}
}
int			fill_txdata(t_txdata *txdata, SDL_Surface *surf, int tex_id, t_rt *rt)
{
	unsigned int	start;

	start = 0;

	txdata[tex_id].height = (unsigned int)surf->h;
	txdata[tex_id].width = (unsigned int)surf->w;
	if(tex_id == 0)
		txdata[tex_id].start = 0;
	else
		txdata[tex_id].start = rt->txt_gpu.total_size + 1;
	start = txdata[tex_id].width * txdata[tex_id].height;
	return (start);
}

void 	texture_init(t_rt *rt)
{
	int i;
	int text_id;
	SDL_Surface *surf;
	
	text_id = 0;
	i = -1;
	rt->txt_gpu.tx_count = 0;
	while(++i<rt->scene.obj_c)
		if(rt->obj_mas[i].text_on)
			rt->txt_gpu.tx_count +=1;
	rt->txt_gpu.txdata = (t_txdata*)malloc(sizeof(t_txdata) * rt->txt_gpu.tx_count);	
	i = -1;
	while(++i < rt->scene.obj_c)
		if(rt->obj_mas[i].text_on)
		{
			surf = IMG_Load(rt->obj_mas[i].texture);
			rt->txt_gpu.total_size += fill_txdata(rt->txt_gpu.txdata, surf, text_id, rt);
			rt->obj_mas[i].texture_id = text_id;
			text_id++;
		}
	rt->txt_gpu.tx = (int*)malloc(sizeof(int) * rt->txt_gpu.total_size);	
	write_tx(rt);	
}