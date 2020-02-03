/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_obj.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 15:36:04 by rsticks           #+#    #+#             */
/*   Updated: 2020/01/30 16:46:40 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARS_OBJ
# define PARS_OBJ

typedef struct 			s_list_vn
{
	int					xn;
	int					yn;
	int					zn;
}						t_list_vn;

typedef struct			s_list_v
{
	float				x;
	float				y;
	float				z;
}						t_list_v;

typedef struct 			s_parse_obj
{
	u_int32_t			count_v;
	u_int32_t			count_vn;
	u_int32_t			count_f;
	int					fd;
	char				*line;
	t_list_v			*v;
	t_list_vn			*vn;
	int					**f;
}						t_parse_obj;

void					parsing_obj(char *path);
void					parse_v(t_parse_obj *data);

#endif
