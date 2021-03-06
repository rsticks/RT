/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel.cl                                           :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:05:27 by rsticks           #+#    #+#             */
/*   Updated: 2019/11/06 14:05:27 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NULL ((void*)0)
/*
** Object name
*/

#define     EQN_EPS     1e-9
#define	    IsZero(x)	((x) > -EQN_EPS && (x) < EQN_EPS)

#ifdef NOCBRT
#define     cbrt(x)     ((x) > 0.0 ? pow((float)(x), 1.0/3.0) : ((x) < 0.0 ? -pow((float)-(x), 1.0/3.0) : 0.0))
#endif

# define FOV			2.0

/*
** Object id
*/
# define SPHERE_ID		1
# define PLANE_ID		2
# define CYLINDER_ID	3
# define CONE_ID		4
# define OBJ_FILE_ID	5
# define PARABOLOID_ID	6
# define DISK_ID		7
# define TORUS_ID		8

# define WAVES_ID		1
# define CHECH_BEARD_ID 2

# define SB_BRICK_ID	1
# define SB_HERNIA_1_ID 2
/*
** Help
*/
# define EPS 0.0001
__constant float EPSILON = 0.001;
__constant float PI = 3.14159265359f;
__constant float PI_2 = 6.28318530718f;
__constant int max_bounces = 20;
__constant int min_bounces = 5;
# define RED(color) (((int)color >> 16) & 0xFF)
# define GREEN(color) (((int)color >> 8) & 0xFF)
# define BLUE(color) ((int)color & 0xFF)

typedef struct		s_basis
{
	__float3		u;
	__float3		v;
	__float3		w;
}					t_basis;

typedef struct				s_cl_data_obj
{
	int						num;
	float3					v;
	float3					vn;
	float					u1;
	float					v1;
	int3					vf;
	int3					vnf;
	int3					vtf;
}							t_cl_data_obj;


typedef struct		s_cl_txdata
{
	uint			width;
	uint			height;
	uint			start;
}					t_cl_txdata;

typedef union		s_cl_txt_rgb
{
	int			c;
	uchar			bgra[4];
}					t_cl_txt_rgb;

typedef struct			    s_cl_object
{
	float3			        pos;
	float3			        rot;
	float3		    	    col;
	float			        r;
	float                   torus_r;
	int				        name;
	int				        specular;
    int                     contruction_id;
	int				        reflect;
	int						texture_id;
	float			        coef_refl;
	int				        refr; //если == 1 то этот объект будет преломлять свет
	float			        ind_refr; // Коэффициент преломления
	float			        coef_refr;
	float			        limit;
}						    t_cl_object;

typedef	struct				s_cl_light
{
	float3					pos;
	float					inten;
	float3					col;
}							t_cl_light;

typedef	struct				s_ray
{
	float3					orig;
	float3					dir;
}							t_ray;

typedef	struct				s_cam
{
	float3					pos;
	float3					rot;
}							t_cam;

typedef	struct				s_win
{
	int						size[2];
	int 					anti_alias;
}							t_win;

typedef	struct				s_scene
{
	float					spec; // Уровень блестящести
	int						obj_c; // Количество считанных объектов
	int						lgh_c; // Количество источников света

	int						maxref;
	float					ambient;
}							t_scene;

typedef struct				s_rt
{
	t_scene					scene;
	t_win 					window;
	t_cam 					cam;

	__global t_cl_object	*obj;
	__global t_cl_light		*light;
	__global t_cl_txt_rgb	*tx;
	__global t_cl_txdata	*txdata;
	__global t_cl_data_obj	*data_o;

	int						gid;
	float3					ray_dir;
	float					t;
	float3 					dist;
	float3					norm;
	float3					refpos;

	float3					ref;
	int 					pref;
	int 					cpt;
	int						prim;
	float					n1;
	float					n2;


	int						intr_obj;
	int						f_count;
	int						count_of_triangl;
}							t_rt;

float						get_triangle_intersection(float3 *ray_dir, float3 *cam_pos, int i, t_rt *rt);
void						ft_fzero(float *s, int n);
float						ft_clamp(float value, float min, float max);
float3						vec_sum(float3 v1, float3 v2);
float3						vec_sub(float3 v1, float3 v2);
float3						vec_scale(float3 v1, float factor);
float						vec_dot(float3 v1, float3 v2);
float						vec_len(float3 v1);
float3						vec_norm(float3 v1);
float3  					vec_cross(float3 v1, float3 v2);
float						get_quadratic_solution(float a, float b, float discriminant);
float 						get_sphere_intersection(float3 *ray_dir, float3 *cam_pos, int i, t_rt *rt);
float 						get_plane_intersection(float3 *ray_dir, float3 *cam_pos, int i, t_rt *rt);
float 						get_cone_intersection(float3 *ray_dir, float3 *cam_pos, int i, t_rt *rt);
float 						get_cylinder_intersection(float3 *ray_dir, float3 *cam_pos, int i, t_rt *rt);
float                       get_paraboloid_intersection(float3 *ray_dir, float3 *cam_pos, int i, t_rt *rt);
float                       get_torus_intersection(float3 *ray_dir, float3 *cam_pos, int i, t_rt *rt);
float                       get_disk_intersection(float3 *ray_dir, float3 *cam_pos, int i, t_rt *rt);
void						normalize_coord_for_texture(float2 uv, float *color,  t_rt *rt,  int texture_id);
void                        ft_tab_coef(float *tab, float coef, int size);
void 	                    calculate_light(t_rt *rt, float *tab);
void                        result_in_tab(t_rt *rt, int start_obj, float* tab, float* tab_refl, float* tab_refr);
void                        main_light(t_rt *rt, int i_obj, float *tab, float3 *pos);

int                         refr_init(t_rt *rt, int i_obj, float3 *pos);
int                         refr_inter(t_rt *rt, float3 *pos);

int                         SolveQuartic(float *c, float *s);
int                         SolveCubic(float *c, float *s);
int                         SolveQuadric(float *c, float *s);

int							intersection(t_rt *rt, float3 *ray_dir, float3 *cam_pos);
float3 						object_norm(t_rt *rt, int i, float3 pos);
int							shadow(t_rt *rt, int i_obj, int i_light, float3 pos);
void						transfer_light(int i_obj, int i_light, float *tab, float d, t_rt *rt);
void 						gloss(t_rt *rt, int i_obj, float *tab, float3 *dist, float d);
int 						ref_inter(t_rt *rt, int i_cur_obj , float3 pos);
int 						ref_init(t_rt *rt, int i_obj, float3 *pos);
int 						reflection(t_rt *rt, int i_obj, float3 *pos, float *tab);
void						ft_average(float *r, float *tab);
void 						create_ray(t_rt *rt, float x, float y);
void 						ft_tracing(float x, float y, t_rt *rt, __global int *data, int gid);
float2						uv_mapping_for_sphere(t_rt *rt, float3 *pos);
float2						uv_mapping_for_plane(t_rt *rt, float3 *pos);
float2 						uv_mapping_for_cone(t_rt *rt, float3 *pos,int i);
float2						uv_mapping_for_cylinder(t_rt *rt, float3 *pos, int i);
void						uv_mapping_for_skybox(t_rt *rt, float *tab);

static float3			vec_change(float3 n, float3 vec)
{
    float	cos_x,		cos_z;
    float3	new_vec,	new_n;
    float	alpha_x,	alpha_z;

    if (length((float2)(n.x, n.y)) < 1e-5f)
        return (vec);
    else
    {
        cos_x = n.x / length((float2)(n.x, n.y));
        if (n.y > 0.f)
            alpha_x = acos(cos_x);
        else
            alpha_x = -acos(cos_x);
    }

    float cos_alpha_x = cos(alpha_x);
	float sin_alpha_x = sin(alpha_x);
    new_vec.x = dot((float3)(cos_alpha_x, sin_alpha_x, 0.f), vec);
    new_vec.y = dot((float3)(-sin_alpha_x, cos_alpha_x, 0.f), vec);
    new_vec.z = dot((float3)(0.f, 0.f, 1.f), vec);

    new_n.x = dot((float3)(cos_alpha_x, sin_alpha_x, 0.f), n);
    new_n.y = dot((float3)(-sin_alpha_x, cos_alpha_x, 0.f), n);
    new_n.z = dot((float3)(0.f, 0.f, 1.f), n);


    cos_z = new_n.z / length(new_n);
    if (new_n.x > 0)
        alpha_z = acos(cos_z);
    else
        alpha_z = -acos(cos_z);

	float cos_alpha_z = cos(alpha_z);
	float sin_alpha_z = sin(alpha_z);
    vec.x = dot((float3)(cos_alpha_z, 0.f, -sin_alpha_z), new_vec);
    vec.y = dot((float3)(0.f, 1.f, 0.f), new_vec);
    vec.z = dot((float3)(sin_alpha_z, 0.f, cos_alpha_z), new_vec);

	new_vec.x = vec.y;
	new_vec.y = vec.z;
	new_vec.z = vec.x;
    return (new_vec);
}

void	normalize_coord_for_texture(float2 uv, float *color,  t_rt *rt,  int texture_id)
{
	int		coord;
	int		tex_width;
	int		tex_height;

	if (texture_id >= 0)
	{
		tex_width = rt->txdata[texture_id].width;
		tex_height = rt->txdata[texture_id].height;
		coord = (int)(uv.x * tex_width) + (int)(uv.y * tex_height) * tex_width;
		coord += rt->txdata[texture_id].start * 3;
		color[0] = (float)(RED(rt->tx[coord].c) * 0.00392156862f); 
		color[1] = (float)(GREEN(rt->tx[coord].c) * 0.00392156862f);
		color[2] = (float)(BLUE(rt->tx[coord].c) * 0.00392156862f);
	}
}

float2			uv_mapping_for_sphere(t_rt *rt, float3 *pos)
{
	float3	vec;
	float 	v;
	float 	u;

	vec = rt->norm;
	u = 0.5f + (atan2(vec.x, -vec.z) / (2.f * M_PI_F));
	v = 0.5f - (asin(vec.y) / M_PI_F);
	return ((float2){u, v});
}

float2			uv_mapping_for_plane(t_rt *rt, float3 *pos)
{
	float3 vec;
	float3 normvec;
	float3 crossvec;
	float v;
	float u;

    vec = *pos;

	if (rt->norm.x != 0.0f)
		normvec = normalize((float3) {0.0f, rt->norm.z, rt->norm.x});
	else
		normvec = (float3) {1.0f, 0.0f, 0.0f};
	
	if (rt->norm.z >= 0.0f)
		rt->norm.z *= -1;
	crossvec = vec_cross(
		rt->norm, normvec);
	u = 0.5f + fmod(dot(normvec, vec), 16.0f) / 32.f;
	v = 0.5f + fmod(dot(crossvec, vec), 16.0f) / 32.f;
	return ((float2){u, v});
}

float2 			uv_mapping_for_cone(t_rt *rt, float3 *pos,int i)
{
	float3	vec;
	float 	v;
	float 	u;
	float p;

	vec = vec_change(rt->obj[i].rot, *pos);
	p = (vec.x / vec.y) / tan(rt->obj[i].r);
	if (vec.z > 0.f)
		u = acos(p);
	else
		u = 2.f * M_PI - acos(p);
	u /= (2.f * M_PI);
	v = 0.5f - modf(vec.y * 100.f / 1024.f, &v) / 2.f;
	return ((float2) {u, v});
}

float2			uv_mapping_for_cylinder(t_rt *rt, float3 *pos, int i)
{
	float3	vec;
	float 	v;
	float 	u;

	vec = vec_change(rt->obj[i].rot, *pos);
	u = 0.5f + (atan2(vec.x, vec.z) / (2.f * M_PI_F));
    v = 0.5f - (modf(vec.y / rt->obj[i].r * 250.f / 1024.f, &v) / 2.f);
	return ((float2){u, v});
}

void ft_tab_coef(float *tab, float coef, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		tab[i] *= coef;
		i++;
	}
}

float   ft_clamp(float value, float min, float max)
{
	if (value < min)
		value = min;
	if (value > max)
		value = max;
	return (value);
}

void    ft_fzero(float *s, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		s[i] = 0.0f;
		i++;
	}
}

float3		vec_cross(float3 v1, float3 v2)
{
	float3	v;

	v.x = v1.y * v2.z - v1.z * v2.y;
	v.y = v1.z * v2.x - v1.x * v2.z;
	v.z = v1.x * v2.y - v1.y * v2.x;
	return (v);
}

float3		vec_sum(float3 v1, float3 v2)
{
	float3 v;

	v.x = v1.x + v2.x;
	v.y = v1.y + v2.y;
	v.z = v1.z + v2.z;;
	return (v);
}

float3	vec_sub(float3 v1, float3 v2)
{
	float3 v;

	v.x = v1.x - v2.x;
	v.y = v1.y - v2.y;
	v.z = v1.z - v2.z;
	return (v);
}

float3	vec_scale(float3 v1, float factor)
{
	float3 v;

	v.x = v1.x * factor;
	v.y = v1.y * factor;
	v.z = v1.z * factor;
	return (v);
}

float	vec_dot(float3 v1, float3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

float		vec_len(float3 v1)
{
	return (native_sqrt(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z));
}

float3	vec_norm(float3 v1)
{
	float	norm_k;

	norm_k = 1 / vec_len(v1);
	return (vec_scale(v1, norm_k));
}

float				get_quadratic_solution(float a, float b, float discriminant)
{
	float 			t1;
	float 			t2;

	t1 = (-b - native_sqrt(discriminant)) / (2 * a);
	t2 = (-b + native_sqrt(discriminant)) / (2 * a);
	if (t1 > t2 && t2 > 0.)
	    return (t2);
	else
	    return (t1);
}

int SolveQuadric(float *c, float *s)
{
    float p;
    float q;
    float D;

    p = c[ 1 ] / (2 * c[ 2 ]);
    q = c[ 0 ] / c[ 2 ];
    D = p * p - q;
    if (IsZero(D))
    {
        s[ 0 ] = - p;
        return 1;
    }
    else if (D < 0)
    {
        return 0;
    }
    else
    {
        float sqrt_D = sqrt(D);

        s[ 0 ] =   sqrt_D - p;
        s[ 1 ] = - sqrt_D - p;
        return 2;
    }
}


int SolveCubic(float *c, float *s)
{
    int     i, num;
    float  sub;
    float  A, B, C;
    float  sq_A, p, q;
    float  cb_p, D;

    A = c[ 2 ] / c[ 3 ];
    B = c[ 1 ] / c[ 3 ];
    C = c[ 0 ] / c[ 3 ];
    sq_A = A * A;
    p = 1.0 / 3 * (- 1.0 / 3 * sq_A + B);
    q = 1.0 / 2 * (2.0 / 27 * A * sq_A - 1.0 / 3 * A * B + C);
    cb_p = p * p * p;
    D = q * q + cb_p;
    if (IsZero(D))
    {
        if (IsZero(q))
        {
            s[ 0 ] = 0;
            num = 1;
        }
        else
        {
            float u = cbrt(-q);
            s[ 0 ] = 2 * u;
            s[ 1 ] = - u;
            num = 2;
        }
    }
    else if (D < 0)
    {
        float phi = 1.0/3 * acos(-q / sqrt(-cb_p));
        float t = 2 * sqrt(-p);

        s[ 0 ] =   t * cos(phi);
        s[ 1 ] = - t * cos(phi + M_PI / 3);
        s[ 2 ] = - t * cos(phi - M_PI / 3);
        num = 3;
    }
    else
    {
        float sqrt_D = sqrt(D);
        float u = cbrt(sqrt_D - q);
        float v = - cbrt(sqrt_D + q);

        s[ 0 ] = u + v;
        num = 1;
    }
    sub = 1.0/3 * A;
    for (i = 0; i < num; ++i)
        s[ i ] -= sub;
    return num;
}


int SolveQuartic(float *c, float *s)
{
    float  coeffs[4];
    float  z, u, v, sub;
    float  A, B, C, D;
    float  sq_A, p, q, r;
    int    i, num;

    A = c[ 3 ] / c[ 4 ];
    B = c[ 2 ] / c[ 4 ];
    C = c[ 1 ] / c[ 4 ];
    D = c[ 0 ] / c[ 4 ];
    sq_A = A * A;
    p = - 3.0 / 8 * sq_A + B;
    q = 1.0 / 8 * sq_A * A - 1.0/2 * A * B + C;
    r = - 3.0 / 256 * sq_A * sq_A + 1.0 / 16 * sq_A * B - 1.0 / 4 * A * C + D;
    if (IsZero(r))
    {
        coeffs[ 0 ] = q;
        coeffs[ 1 ] = p;
        coeffs[ 2 ] = 0;
        coeffs[ 3 ] = 1;
        num = SolveCubic(coeffs, s);
        s[num++] = 0;
    }
    else
    {
        coeffs[ 0 ] = 1.0 / 2 * r * p - 1.0 / 8 * q * q;
        coeffs[ 1 ] = - r;
        coeffs[ 2 ] = - 1.0 / 2 * p;
        coeffs[ 3 ] = 1;
        (void) SolveCubic(coeffs, s);
        z = s[ 0 ];
        u = z * z - r;
        v = 2 * z - p;
        if (IsZero(u))
            u = 0;
        else if (u > 0)
            u = sqrt(u);
        else
            return 0;
        if (IsZero(v))
            v = 0;
        else if (v > 0)
            v = sqrt(v);
        else
            return 0;
        coeffs[ 0 ] = z - u;
        coeffs[ 1 ] = q < 0 ? -v : v;
        coeffs[ 2 ] = 1;
        num = SolveQuadric(coeffs, s);
        coeffs[ 0 ]= z + u;
        coeffs[ 1 ] = q < 0 ? v : -v;
        coeffs[ 2 ] = 1;
        num += SolveQuadric(coeffs, s + num);
    }
    sub = 1.0 / 4 * A;
    for (i = 0; i < num; ++i)
        s[ i ] -= sub;
    return num;
}
//----------------------------End Math Module-----------------------------------
//----------------------Start Intersrction Module-------------------------------
float get_sphere_intersection(float3 *ray_dir, float3 *cam_pos, int i, t_rt *rt)
{
	float b;
	float c;
	float a;
	float discriminant;

	rt->dist = vec_sub(*cam_pos, rt->obj[i].pos);
	a = vec_dot(*ray_dir, *ray_dir);
	b = 2 * vec_dot(*ray_dir, rt->dist);
	c = vec_dot(rt->dist, rt->dist) - pow(rt->obj[i].r, 2);
	discriminant = pow(b, 2) - 4 * a * c;
	if (discriminant < 0)
		return (-1);
	return (get_quadratic_solution(a, b , discriminant));
}






float				get_triangle_intersection(float3 *ray_dir, float3 *cam_pos, int i, t_rt *rt)
{
	float	dist;
	float 	g;
	float	prev;
	float3 	p;
	float3 	temp;
	float3	v0, v1, v2;
	float3	norm;

	g = -1;
	i = 0;
	prev = 90000.0;
	rt->count_of_triangl = rt->f_count;
	while (i < rt->f_count)
	{	
		norm = vec_sum(rt->data_o[rt->data_o[i].vnf.x - 1].vn, rt->data_o[rt->data_o[i].vnf.y - 1].vn);
		norm = (vec_sum(norm, rt->data_o[rt->data_o[i].vnf.z - 1].vn));
		dist = ((vec_dot(norm, rt->data_o[rt->data_o[i].vf.x - 1].v) -  vec_dot(norm, *cam_pos)) / vec_dot(norm, *ray_dir));
		if (dist >= EPS)
		{
			temp = vec_scale(*ray_dir, dist);
			p = vec_sum(*cam_pos, temp);
			v0 = rt->data_o[rt->data_o[i].vf.x - 1].v;
			v1 = rt->data_o[rt->data_o[i].vf.y - 1].v;
			v2 = rt->data_o[rt->data_o[i].vf.z - 1].v;
			if (!((vec_dot(vec_cross(vec_sub(v1, v0), vec_sub(p, v0)), norm) < 0) ||
				(vec_dot(vec_cross(vec_sub(v2, v1), vec_sub(p, v1)), norm) < 0) ||
				(vec_dot(vec_cross(vec_sub(v0, v2), vec_sub(p, v2)), norm) < 0)))
			{
				if (dist < prev)
				{
					rt->count_of_triangl = i;
					g = dist;
					prev = dist;
				}		
			}
		}
		i++;
	}
	return (g);
}




float get_plane_intersection(float3 *ray_dir, float3 *cam_pos, int i, t_rt *rt)
{
	float dist;
	
	dist = ((vec_dot(rt->obj[i].rot, rt->obj[i].pos) - vec_dot(rt->obj[i].rot,
	*cam_pos)) / vec_dot(rt->obj[i].rot, *ray_dir));
	if (dist < EPS)
		return (-1);
	return (dist);
}




float get_cone_intersection(float3 *ray_dir, float3 *cam_pos, int i, t_rt *rt)
{
	float	b;
	float	c;
	float	a;
	float	discriminant;

	rt->dist = vec_sub(*cam_pos, rt->obj[i].pos);
	rt->obj[i].rot = vec_norm(rt->obj[i].rot);
	a = vec_dot(*ray_dir, *ray_dir) - (1 + pow(tan(rt->obj[i].r), 2))
	* pow(vec_dot(*ray_dir, rt->obj[i].rot), 2);
	b = 2 * (vec_dot(*ray_dir, rt->dist) - (1 + pow(tan(rt->obj[i].r), 2))
	* vec_dot(*ray_dir, rt->obj[i].rot) * vec_dot(rt->dist, rt->obj[i].rot));
	c = vec_dot(rt->dist, rt->dist) - (1 + pow(tan(rt->obj[i].r), 2))
	* pow(vec_dot(rt->dist, rt->obj[i].rot), 2);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1);
	return (get_quadratic_solution(a, b, discriminant));
}

float get_cylinder_intersection(float3 *ray_dir, float3 *cam_pos, int i, t_rt *rt)
{
	float b;
	float c;
	float a;
	float discriminant;

	rt->dist = vec_sub(*cam_pos, rt->obj[i].pos);
	rt->obj[i].rot = vec_norm(rt->obj[i].rot);
	a = vec_dot(*ray_dir, *ray_dir) - pow(vec_dot(*ray_dir, rt->obj[i].rot), 2);
	b = 2 * (vec_dot(*ray_dir, rt->dist) - (vec_dot(*ray_dir, rt->obj[i].rot)
	* vec_dot(rt->dist, rt->obj[i].rot)));
	c = vec_dot(rt->dist, rt->dist) - pow(vec_dot(rt->dist, rt->obj[i].rot), 2)
	- pow(rt->obj[i].r, 2);
	discriminant = pow(b, 2) - 4 * a * c;
	if (discriminant < 0)
		return (-1);
	return (get_quadratic_solution(a, b, discriminant));
}

float get_paraboloid_intersection(float3 *ray_dir, float3 *cam_pos, int i, t_rt *rt)
{
	float b;
	float c;
	float a;
	float discriminant;

	rt->dist = vec_sub(*cam_pos, rt->obj[i].pos);
	a = vec_dot(*ray_dir, *ray_dir) - pow(vec_dot(*ray_dir, rt->obj[i].rot), 2);
	b = 2 * (vec_dot(*ray_dir, rt->dist) - vec_dot(*ray_dir, rt->obj[i].rot) * (vec_dot(rt->dist, rt->obj[i].rot) + 2 * rt->obj[i].r));
	c = vec_dot(rt->dist, rt->dist) - vec_dot(rt->dist, rt->obj[i].rot) * (vec_dot(rt->dist, rt->obj[i].rot) + 4 * rt->obj[i].r);
	discriminant = pow(b, 2) - 4 * a * c;
	if (discriminant < 0)
		return (-1);
	return (get_quadratic_solution(a, b , discriminant));
}

float get_disk_intersection(float3 *ray_dir, float3 *cam_pos, int i, t_rt *rt)
{
	float dist;

	dist = ((vec_dot(rt->obj[i].rot, rt->obj[i].pos) - vec_dot(rt->obj[i].rot, *cam_pos)) / vec_dot(rt->obj[i].rot, *ray_dir));
	if (dist > EPS  && vec_len(vec_sub(vec_sum(*cam_pos, vec_scale(*ray_dir, dist)), rt->obj[i].pos)) <= rt->obj[i].r)
		return dist;
	else
		return (-1);
}

float get_torus_intersection(float3 *ray_dir, float3 *cam_pos, int i, t_rt *rt)
{
    float c[5];
    float root[4];
    int count_root;

    rt->dist = vec_sub(*cam_pos, rt->obj[i].pos);

    c[4] = pow(vec_dot(*ray_dir, *ray_dir),2);
    c[3] = 4 * vec_dot(*ray_dir, *ray_dir) * vec_dot(*cam_pos, *ray_dir);
    c[2] = 2 * vec_dot(*ray_dir, *ray_dir) * (vec_dot(*cam_pos, *cam_pos) - (pow(rt->obj[i].r,2) + pow(rt->obj[i].torus_r,2))) + 4 * pow(vec_dot(*cam_pos, *ray_dir),2) + 4*pow(rt->obj[i].torus_r,2) * pow(ray_dir->y, 2);
    c[1] = 4 * (vec_dot(*cam_pos, *cam_pos) - (pow(rt->obj[i].r,2) + pow(rt->obj[i].torus_r,2))) * vec_dot(*cam_pos, *ray_dir) + 8*pow(rt->obj[i].torus_r,2) * ray_dir->y * cam_pos->y;
    c[0] =  pow((vec_dot(*cam_pos, *cam_pos) - (pow(rt->obj[i].r,2) + pow(rt->obj[i].torus_r,2))),2) - 4 * pow(rt->obj[i].torus_r,2) * (pow(rt->obj[i].r,2) - pow(cam_pos->y,2));

    count_root = SolveQuartic(c, root);

    int ind;
    float min_root;

    if (count_root == 0)
        return (-1);
    ind = -1;
    while (++ind < count_root)
        if (root[ind] >= 0.) {
            min_root = root[ind];
            break;
        }
    if (ind == count_root)
        return (-1);
    while (++ind < count_root)
        if (root[ind] < min_root)
            min_root = root[ind];
    return (min_root);
}
//------------------------End Intersrction Module-------------------------------

int     intersection(t_rt *rt, float3 *ray_dir, float3 *cam_pos)
{
	float dist;
	int i;
	int f;

	i = 0;
	f = -1;
	rt->t = 90000.0;
	dist = 0.01;
	while (i < rt->scene.obj_c)
	{
		if (rt->obj[i].name == SPHERE_ID)
			dist = get_sphere_intersection(ray_dir, cam_pos, i, rt);
		else if (rt->obj[i].name == CYLINDER_ID)
			dist = get_cylinder_intersection(ray_dir, cam_pos, i, rt);
		else if (rt->obj[i].name == CONE_ID)
			dist = get_cone_intersection(ray_dir, cam_pos, i, rt);
		else if (rt->obj[i].name == PLANE_ID)
			dist = get_plane_intersection(ray_dir, cam_pos, i, rt);
		else if (rt->obj[i].name == PARABOLOID_ID)
			dist = get_paraboloid_intersection(ray_dir, cam_pos, i, rt);
		else if (rt->obj[i].name == DISK_ID)
			dist = get_disk_intersection(ray_dir, cam_pos, i, rt);
        else if (rt->obj[i].name == TORUS_ID)
            dist = get_torus_intersection(ray_dir, cam_pos, i, rt);
		else if (rt->obj[i].name == OBJ_FILE_ID)
			dist = get_triangle_intersection(ray_dir, cam_pos, i, rt);
		if (dist > EPS && dist < rt->t)
		{
			f = i;
			rt->t = dist;
		}
		i++;
	}
	return (f);
}

float3 object_norm(t_rt *rt, int i, float3 pos)
{
	float3 norm;
	float3 tmp;
	float3 tmp2;
	float m, k;

	if (rt->obj[i].name == CONE_ID || rt->obj[i].name == CYLINDER_ID)
	{
		tmp = vec_scale(rt->obj[i].rot, (vec_dot(rt->ray_dir, rt->obj[i].rot) * rt->t
		+ vec_dot(rt->dist, rt->obj[i].rot)));
		if (rt->obj[i].name == CONE_ID)
			tmp = vec_scale(tmp, (1 + pow(tan(rt->obj[i].r), 2)));
		tmp2 = vec_sub(pos, rt->obj[i].pos);
		norm = vec_sub(tmp2, tmp);
	}
    else if (rt->obj[i].name == TORUS_ID)
    {
        k = vec_dot(vec_sub(pos, rt->obj[i].pos), rt->obj[i].rot);
        tmp = vec_sub(pos, vec_scale(rt->obj[i].rot,k));
        m = native_sqrt(pow(rt->obj[i].r, 2) - pow(k, 2));
        norm = vec_sub(pos, vec_sub(tmp, vec_scale(vec_sub(rt->obj[i].pos, tmp), (m / (m + rt->obj[i].torus_r)))));
    }
	else if (rt->obj[i].name == PLANE_ID || rt->obj[i].name == DISK_ID)
		norm = rt->obj[i].rot;
	else if (rt->obj[i].name == PARABOLOID_ID)
		norm = vec_sub( vec_sub(pos, rt->obj[i].pos), vec_scale(rt->obj[i].rot, (vec_dot(vec_sub(pos, rt->obj[i].pos), rt->obj[i].rot) + rt->obj[i].r)));
	else if (rt->obj[i].name == OBJ_FILE_ID)
		norm = rt->data_o[rt->data_o[rt->count_of_triangl].vnf.x - 1].vn;
	else if (rt->obj[i].name == SPHERE_ID)
		norm = vec_sub(pos, rt->obj[i].pos);
	return (vec_norm(norm));
}


void	transfer_light(int i_obj, int i_light, float *tab, float d, t_rt *rt)
{
	tab[3] = ft_clamp(tab[3] * 4.0 * d, 0.0, 1.0);
	tab[0] += tab[3] * (rt->obj[i_obj].col.x / 255) * (rt->light[i_light].col.x / 255);
	tab[1] += tab[3] * (rt->obj[i_obj].col.y / 255) * (rt->light[i_light].col.y / 255);
	tab[2] += tab[3] * (rt->obj[i_obj].col.z / 255) * (rt->light[i_light].col.z / 255);
}

int shadow(t_rt *rt, int i_obj, int i_light, float3 pos)
{
	float3	dist;
	float 	d;
	int 	i;

	i = 0;
	dist = vec_sub(rt->light[i_light].pos, pos);
	rt->t = native_sqrt(vec_dot(dist, dist));
	dist = vec_norm(dist);
	while (i < rt->scene.obj_c)
	{
		if (i != i_obj)
		{
			if (rt->obj[i].name == SPHERE_ID)
				d = get_sphere_intersection(&dist, &pos, i, rt);
			else if (rt->obj[i].name == CYLINDER_ID)
				d = get_cylinder_intersection(&dist, &pos, i, rt);
			else if (rt->obj[i].name == CONE_ID)
				d = get_cone_intersection(&dist, &pos, i, rt);
			else if (rt->obj[i].name == PLANE_ID)
				d = get_plane_intersection(&dist, &pos, i, rt);
			else if (rt->obj[i].name == PARABOLOID_ID)
				d = get_paraboloid_intersection(&dist, &pos, i, rt);
			else if (rt->obj[i].name == DISK_ID)
				d = get_disk_intersection(&dist, &pos, i, rt);
            else if (rt->obj[i].name == TORUS_ID)
                d = get_torus_intersection(&dist, &pos, i, rt);
			else if (rt->obj[i].name == OBJ_FILE_ID)
                d = get_triangle_intersection(&dist, &pos, i, rt);
			if (d > EPS && d < rt->t)
				return (i);
		}
		i++;
	}
	return (0);
}

void gloss(t_rt *rt, int i_obj, float *tab, float3 *dist, float d)
{
	float	spec;
	float	tmp;
	float3	ref;

	if (rt->obj[i_obj].name != PLANE_ID && rt->obj[i_obj].specular == 1)
	{
		spec = 0.0;
		ref = vec_scale(rt->norm, (2.0 * vec_dot(rt->norm, *dist)));
		ref = vec_sub(*dist, ref);
		tmp = vec_dot(ref, rt->ray_dir);
		if (tmp > 0.0 && tab[3] > rt->scene.ambient)
		{
			spec = native_powr(tmp, 20) * 4 * d;
			spec = ft_clamp(spec, 0.0, 1.0);
		}
		tab[1] += spec;
		tab[2] += spec;
		tab[3] += spec;
	}
}

int ref_inter(t_rt *rt, int i_cur_obj , float3 pos)
{
	double	dist;
	int i;
	char f;

	i = 0;
	f = -1;
	while (i < rt->scene.obj_c)
	{
		if (i_cur_obj != i)
		{
			if (rt->obj[i].name == SPHERE_ID)
				dist = get_sphere_intersection(&rt->ref, &pos, i, rt);
			else if (rt->obj[i].name == CYLINDER_ID)
				dist = get_cylinder_intersection(&rt->ref, &pos, i, rt);
			else if (rt->obj[i].name == CONE_ID)
				dist = get_cone_intersection(&rt->ref, &pos, i, rt);
			else if (rt->obj[i].name == PLANE_ID)
				dist = get_plane_intersection(&rt->ref, &pos, i, rt);
			else if (rt->obj[i].name == PARABOLOID_ID)
				dist = get_paraboloid_intersection(&rt->ref, &pos, i, rt);
			else if (rt->obj[i].name == DISK_ID)
				dist = get_disk_intersection(&rt->ref, &pos, i, rt);
            else if (rt->obj[i].name == TORUS_ID)
                dist = get_torus_intersection(&rt->ref, &pos, i, rt);
			else if (rt->obj[i].name == OBJ_FILE_ID)
                dist = get_triangle_intersection(&rt->ref, &pos, i, rt);
			if (dist > EPS && dist < rt->t)
			{
				f = i;
				rt->t = dist;
			}
		}
		i++;
	}
	return (f);
}

int ref_init(t_rt *rt, int i_obj, float3 *pos)
{
	int	new_inter;

	rt->t = 8000.0;
	rt->ref = vec_scale(rt->norm, (2 * vec_dot(rt->ray_dir, rt->norm)));
	rt->ref = vec_sub(rt->ray_dir, rt->ref);
	rt->ref = vec_norm(rt->ref);
	if ((new_inter = ref_inter(rt, i_obj, *pos)) == -1)
		return (-1);
    if (rt->obj[new_inter].refr == 1.0)
        rt->prim = 0;
	*pos = (float3){pos->x + rt->t * rt->ref.x,
					pos->y + rt->t * rt->ref.y,
					pos->z + rt->t * rt->ref.z};
	rt->ray_dir = (float3){rt->ref.x, rt->ref.y, rt->ref.z};
	return (new_inter);
}

int refr_inter(t_rt *rt, float3 *pos)
{
	double	dist;
	int i;
	char f;

	i = 0;
	f = -1;
	while (i < rt->scene.obj_c)
	{
        if (rt->obj[i].name == SPHERE_ID)
            dist = get_sphere_intersection(&rt->ref, pos, i, rt);
        else if (rt->obj[i].name == CYLINDER_ID)
            dist = get_cylinder_intersection(&rt->ref, pos, i, rt);
        else if (rt->obj[i].name == CONE_ID)
            dist = get_cone_intersection(&rt->ref, pos, i, rt);
        else if (rt->obj[i].name == PLANE_ID)
            dist = get_plane_intersection(&rt->ref, pos, i, rt);
        else if (rt->obj[i].name == PARABOLOID_ID)
            dist = get_paraboloid_intersection(&rt->ref, pos, i, rt);
        else if (rt->obj[i].name == DISK_ID)
            dist = get_disk_intersection(&rt->ref, pos, i, rt);
        else if (rt->obj[i].name == TORUS_ID)
            dist = get_torus_intersection(&rt->ref, pos, i, rt);
		else if (rt->obj[i].name == OBJ_FILE_ID)
            dist = get_triangle_intersection(&rt->ref, pos, i, rt);
		if (dist > EPS && dist < rt->t)
		{
			f = i;
			rt->t = dist;
		}
		i++;
	}
	return (f);
}

int refr_init(t_rt *rt, int i_obj, float3 *pos)
{
	int	new_inter;
	float3 new_pos_inter;
	float d_dot = 0.001;

    new_inter = -1;
	if (rt->cpt == 0 || rt->prim == 0)
	{
		rt->n1 = 1.0;
		rt->n2 = rt->obj[rt->intr_obj].ind_refr;
	}
	else
	{
		rt->n1 = rt->obj[rt->intr_obj].ind_refr;
		rt->n2 = 1.0;
        rt->norm = vec_scale(rt->norm, -1);
		rt->prim = 0;
	}
	rt->t = 8000.0;
	rt->ref = vec_sum(vec_scale(rt->ray_dir, rt->n1 / rt->n2), vec_scale(rt->norm, (rt->n1 / rt->n2) * vec_dot(rt->norm, rt->ray_dir) - native_sqrt(1 - (pow((rt->n1 / rt->n2), 2) * (1 - pow(vec_dot(rt->ray_dir, rt->norm), 2))))));
    rt->ref = vec_norm(rt->ref);
	new_pos_inter = (float3){pos->x + d_dot * rt->ref.x, pos->y + d_dot * rt->ref.y, pos->z + d_dot * rt->ref.z};
	if ((new_inter = refr_inter(rt, &new_pos_inter)) == -1)
		return (-1);
	if (rt->intr_obj == new_inter)
		rt->prim = 1;
	*pos = (float3){pos->x + rt->ref.x * rt->t, pos->y + rt->ref.y * rt->t, pos->z + rt->ref.z * rt->t};
	rt->ray_dir = (float3){rt->ref.x, rt->ref.y, rt->ref.z};
	return (new_inter);
}

void	uv_mapping_for_skybox(t_rt *rt, float *tab)
{
	float3	vec;
	float 	v;
	float 	u;
	int		coord;
	uint		tex_width;
	uint		tex_height;


	vec = vec_scale(rt->ray_dir, -1);
	tex_width = rt->txdata[0].width;
	tex_height = rt->txdata[0].height;
	u = 0.5f + (atan2(vec.x, vec.z) / (2.f * M_PI_F));
	v = 0.5f + (asin(vec.y) / M_PI_F);
	coord = (int)(u * tex_width) + (int)(v * tex_height) * tex_width;
	tab[0] += (float)(RED(rt->tx[coord].c) * 0.00392156862f); 
	tab[1] += (float)(GREEN(rt->tx[coord].c) * 0.00392156862f);
	tab[2] += (float)(BLUE(rt->tx[coord].c) * 0.00392156862f);

}

void main_light(t_rt *rt, int i_obj, float *tab, float3 *pos)
{
	float3 dist;
	float d;
	int ind, obj_num;

	ind = 0;
	while (ind < rt->scene.lgh_c)
	{
		tab[3] = rt->scene.ambient;
		dist = vec_sub(rt->light[ind].pos, *pos);
		d = ft_clamp((1.0 / native_sqrt(native_sqrt(vec_dot(dist, dist)))), 0.0, 1.0);
		dist = vec_norm(dist);
		if ((obj_num = shadow(rt, i_obj, ind, *pos)) == 0)
			tab[3] += ft_clamp(vec_dot(dist, rt->norm), 0.0, 1.0);
		else if (rt->obj[obj_num].refr == 1.0)
			tab[3] += rt->obj[obj_num].coef_refr * ft_clamp(vec_dot(dist, rt->norm), 0.0, 1.0);
		if (rt->obj[i_obj].texture_id != -1)
		{
			if(rt->obj[i_obj].name == SPHERE_ID)
				normalize_coord_for_texture(uv_mapping_for_sphere(rt, pos),tab,rt,rt->obj[i_obj].texture_id );
			else if (rt->obj[i_obj].name == CYLINDER_ID)
				normalize_coord_for_texture(uv_mapping_for_cylinder(rt, pos, i_obj),tab,rt,rt->obj[i_obj].texture_id );
			else if (rt->obj[i_obj].name == CONE_ID)
				normalize_coord_for_texture(uv_mapping_for_cone(rt, pos, i_obj),tab,rt,rt->obj[i_obj].texture_id );
			else if (rt->obj[i_obj].name == PLANE_ID)
				normalize_coord_for_texture(uv_mapping_for_plane(rt, pos),tab,rt,rt->obj[i_obj].texture_id );
		}
		transfer_light(i_obj, ind, tab, d, rt);
		gloss(rt, i_obj, tab, &dist , d);
		ind++;
	}
}

void result_in_tab(t_rt *rt, int start_obj, float* tab, float* tab_refl, float* tab_refr)
{
	int i;

	ft_tab_coef(tab, 1 - (rt->obj[start_obj].coef_refl + rt->obj[start_obj].coef_refr), 3);
	ft_tab_coef(tab_refl, rt->obj[start_obj].coef_refl, 3);
	ft_tab_coef(tab_refr, rt->obj[start_obj].coef_refr, 3);
	i = -1;
	while(++i < 3)
		tab[i] += tab_refl[i] + tab_refr[i];
}

void 	calculate_light(t_rt *rt, float *tab)
{
	float3 pos;
	float	tab_refl[4];
	float	tab_refr[4];
	int start_obj;

	pos = (float3){rt->cam.pos.x + rt->t * rt->ray_dir.x,
                rt->cam.pos.y + rt->t * rt->ray_dir.y,
                rt->cam.pos.z + rt->t * rt->ray_dir.z};
	start_obj = rt->intr_obj;

	ft_fzero(tab_refl, 4);
	ft_fzero(tab_refr, 4);

	rt->norm = object_norm(rt, rt->intr_obj, pos);
	main_light(rt, rt->intr_obj, tab, &pos);
	while (rt->obj[rt->intr_obj].reflect && rt->cpt < rt->scene.maxref && rt->obj[rt->intr_obj].coef_refl > 0.0)
	{
		if ((rt->intr_obj = ref_init(rt, rt->intr_obj, &pos)) != -1)
		{
			rt->norm = object_norm(rt, rt->intr_obj, pos);
			main_light(rt, rt->intr_obj, tab_refl, &pos);
			rt->cpt += 1;
		}
		else
		{
			uv_mapping_for_skybox(rt, tab);
			break ;
		}
	}
	rt->cpt = 0;
	while (rt->obj[rt->intr_obj].refr && rt->cpt < rt->scene.maxref && rt->obj[rt->intr_obj].coef_refr > 0.0)
	{
		if ((rt->intr_obj = refr_init(rt, rt->intr_obj, &pos)) != -1)
		{
			rt->norm = object_norm(rt, rt->intr_obj, pos);
			main_light(rt, rt->intr_obj, tab_refr, &pos);
			rt->cpt += 1;
		}
		else
		{
			uv_mapping_for_skybox(rt, tab);
			break ;
		}
	}
	result_in_tab(rt, start_obj, tab, tab_refl, tab_refr);
}

void	ft_average(float *r, float *tab)
{
	r[0] += ft_clamp(tab[0], 0.0, 1.0);
	r[1] += ft_clamp(tab[1], 0.0, 1.0);
	r[2] += ft_clamp(tab[2], 0.0, 1.0);
}

void create_ray(t_rt *rt, float x, float y)
{
	float u, v;
	float3 i, j, k;

	u = (rt->window.size[0] - (float)x * FOV) / rt->window.size[1];
	v = (rt->window.size[1] - (float)y * FOV) / rt->window.size[0];
	k = vec_sub(rt->cam.rot, rt->cam.pos);
	k = vec_norm(k);
	i = vec_cross(k, (float3){0.0, 1.0, 0.0});
	i = vec_norm(i);
	j = vec_cross(i, k);
	rt->ray_dir = (float3){u * i.x + v * j.x + FOV * k.x, u * i.y + v * j.y + FOV * k.y, u * i.z + v * j.z + FOV * k.z};
	rt->ray_dir = vec_norm(rt->ray_dir);
	rt->cpt = 0;
	rt->prim = 0;
}

void ft_tracing(float x, float y, t_rt *rt, __global int *data, int gid)
{
	float	tab[4];
	float	r[3];
	int x_next = (int)x + 1, y_next = (int)y + 1; 
	float p;


	ft_fzero(r, 3);
	p = 0.0;
	while (y < y_next)
	{
		while (x < x_next)
		{
			p += 1;
			create_ray(rt, x, y);
			ft_fzero(tab, 4);
			if((rt->intr_obj = intersection(rt, &rt->ray_dir, &rt->cam.pos)) >= 0)
				calculate_light(rt, tab);
			//else 
				//uv_mapping_for_skybox(rt, &tab);
            ft_average(r, tab);
			x = x + (1.0 / rt->window.anti_alias);
		}
		y = y + (1.0 / rt->window.anti_alias);
	}
	data[gid] = (((int)(r[0] / p * 255.0) & 0xff) << 16) + (((int)(r[1] / p * 255.0) & 0xff) << 8) + (((int)(r[2] / p * 255.0) & 0xff));
}


__kernel void 		start(__global t_cl_object *obj,
							__global t_cl_light *light,
							__global int *out_data,
							__global int *i_mem,
							__global float *d_mem,
							__global t_cl_txt_rgb *tx,
							__global t_cl_txdata *txdata,
							__global t_cl_data_obj *d_obj)
{
	int				gid, x, y;
	t_rt			rt;

	
	gid = get_global_id(0);
	rt.window.size[0] = i_mem[0];
	rt.window.size[1] = i_mem[1];
	rt.window.anti_alias = i_mem[2];
	rt.scene.obj_c = i_mem[3];
	rt.scene.lgh_c = i_mem[4];
	rt.scene.maxref = i_mem[5];
	rt.f_count = i_mem[6];
	rt.cam.pos = (float3){d_mem[0], d_mem[1], d_mem[2]};
	rt.scene.ambient = d_mem[3];
	rt.cam.rot = (float3){d_mem[4], d_mem[5], d_mem[6]};
	rt.obj = obj;
	rt.light = light;
	rt.tx = tx;
	rt.txdata = txdata;
	rt.gid = gid;
	rt.data_o = d_obj;
	int i = 0;
	//rt.obj[0].name = OBJ_FILE_ID;
	// if (gid >= 1 && gid <= 3)
	// {
	// 	//printf("IN KERNEL\n");
	// 	printf("f || %d/%d/%d %d/%d/%d %d/%d/%d\n f_count = %d\n", 
	// 	d_obj[rt.f_count - 1].vf.x, d_obj[rt.f_count - 1].vtf.x, d_obj[rt.f_count - 1].vnf.x,
	// 	d_obj[rt.f_count - 1].vf.y, d_obj[rt.f_count - 1].vtf.y, d_obj[rt.f_count - 1].vnf.y,
	// 	d_obj[rt.f_count - 1].vf.z, d_obj[rt.f_count - 1].vtf.z, d_obj[rt.f_count - 1].vnf.z,
	// 	rt.f_count);
	// 	for (size_t i = 0; i < 3; i++)
	// 	{
	// 		printf("v [%d] %f %f %f\n", (gid - 1), d_obj[gid - 1].v.x, d_obj[gid - 1].v.y, d_obj[gid - 1].v.z);
	// 	}
	// 	printf("vn %f %f %f\n", d_obj[i].vn.x, d_obj[i].vn.y, d_obj[i].vn.z);
	// }

	x = gid % rt.window.size[0];
	y = gid / rt.window.size[1];
	//if (gid == 1)
	//	printf("\nIN KERNEL txdata = [%d]\n", tx[0].c);
	ft_tracing(x, y, &rt, out_data, gid);
}
