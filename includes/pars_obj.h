/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_obj.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 15:36:04 by rsticks           #+#    #+#             */
/*   Updated: 2020/02/06 15:57:54 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARS_OBJ
# define PARS_OBJ

typedef struct 			s_int_vec
{
	int					x;
	int					y;
	int					z;
}						t_int_vec;

typedef struct 			s_list_vt
{
	cl_float			u;
	cl_float			v;
}						t_list_vt;

typedef struct			s_list_v
{
	cl_float3			v;
}						t_list_v;

typedef struct			s_list_f
{
	cl_int3				v;
	cl_int3				vn;
	cl_int3				vt;
}						t_list_f;

typedef struct 			s_parse_obj
{
	int					num_obj;
	char				*name;
	u_int32_t			count_vt;
	u_int32_t			count_v;
	u_int32_t			count_vn;
	u_int32_t			count_f;
	int					fd;
	char				*line;
	cl_float3			*v;
	cl_float3			*vn;
	t_list_vt			*vt;
	t_list_f			*f;
	int					gnl;
}						t_parse_obj;

void					parsing_obj(char *path, int num);
void					parse_v(t_parse_obj *data);

#endif
