/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_obj.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 15:36:04 by rsticks           #+#    #+#             */
/*   Updated: 2020/03/05 19:33:20 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARS_OBJ_H
# define PARS_OBJ_H

# include "rt.h"

typedef struct			s_int_vec
{
	int					x;
	int					y;
	int					z;
}						t_int_vec;

typedef struct			s_list_vt
{
	cl_float			u;
	cl_float			v;
}						t_list_vt;

typedef struct			s_cl_data_obj
{
	cl_int				num;
	cl_float3			v;
	cl_float3			vn;
	cl_float			u1;
	cl_float			v1;
	cl_int3				vf;
	cl_int3				vnf;
	cl_int3				vtf;
}						t_cl_data_obj;

typedef struct			s_list_f
{
	cl_int3				v;
	cl_int3				vn;
	cl_int3				vt;
}						t_list_f;

typedef struct			s_parse_obj
{
	int					error;
	size_t				max_c;
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
	t_cl_data_obj		*d_obj;
}						t_parse_obj;

void					final_parse(t_parse_obj *data);
int						ftft_isdigit(int c);
char					*while_not_slash(char *c, int *i);
void					counter(t_parse_obj *data, char *str, u_int32_t *count);
char					*while_not_digit(char *c);
char					*next_digit(char *c);
t_parse_obj				*parsing_obj(char *path, int num);
void					parse_v(t_parse_obj *data);
void					parse_vt(t_parse_obj *data);
void					parse_vn(t_parse_obj *data);
char					*f_pars_x(t_parse_obj *data, char *c, u_int32_t count);
char					*f_pars_y(t_parse_obj *data, char *c, u_int32_t count);
char					*f_pars_z(t_parse_obj *data, char *c, u_int32_t count);
size_t					compare_counters(u_int32_t v1,
						u_int32_t v2, u_int32_t v3, u_int32_t v4);

#endif
