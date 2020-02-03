/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_obj.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 15:36:04 by rsticks           #+#    #+#             */
/*   Updated: 2020/02/03 20:01:15 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARS_OBJ
# define PARS_OBJ

typedef struct 			s_list_vn
{
	int					x;
	int					y;
	int					z;
}						t_list_vn;

typedef struct			s_list_v
{
	float				x;
	float				y;
	float				z;
}						t_list_v;

typedef struct			s_cl_obj
{
	cl_int3				f;
	cl_float3			v1;
	cl_float3			v2;
	cl_float3			v3;
	cl_int				num_obj;		
}						t_cl_obj;

typedef struct 			s_parse_obj
{
	int					num_obj;
	char				*name;
	u_int32_t			count_v;
	u_int32_t			count_vn;
	u_int32_t			count_f;
	int					fd;
	char				*line;
	t_list_v			*v;
	t_list_vn			*vn;
	int					**f;
	t_cl_obj			*obj;
}						t_parse_obj;

void					parsing_obj(char *path, int num);
void					parse_v(t_parse_obj *data);

#endif
