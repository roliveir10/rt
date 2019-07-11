/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 10:58:12 by roliveir          #+#    #+#             */
/*   Updated: 2019/07/11 14:29:58 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _RT_H
# define _RT_H

# include "libft.h"

# define SCREENX 2080
# define SCREENY 1170
# define SCREEN SCREENX * SCREENY

# define NBR_TEXT 14
# define NBR_FORM 7
# define NBR_THREAD 4
# define NBR_MATERIAL 12
# define NBR_KEY 13
# define NBR_KEY_REPEAT 11
# define NBR_MKEY 2
# define PIX 32
# define DEPTH_MAX 5

/*
** ENUM
*/

typedef enum			e_event
{
	KEYPRESS = 2,
	REDBUTTON = 17,
	MOUSEPRESS = 4,
	KEYRELEASE = 3
}						t_event;

typedef enum			e_key
{
	KESCAP = 53,
	KLEFT = 123,
	KRIGHT = 124,
	KUP = 126,
	KDOWN = 125,
	KRXUP = 115,
	KRXDOWN = 119,
	KRYRIGHT = 117,
	KRYLEFT = 121,
	KRZRIGHT = 279,
	KRZLEFT = 116,
	KAA = 0,
	KBLINN = 11
}						t_key;

typedef enum			e_mkey
{
	MDOWN = 4,
	MUP
}						t_mkey;

typedef enum			e_ftype
{
	SPHERE,
	PLAN,
	CYLINDRE,
	CONE,
	TORUS,
	HYPER,
	CUBET,
	NOTAFORM
}						t_ftype;

typedef enum			e_ltype
{
	LSPOT,
	LCAST,
	LPOINT
}						t_ltype;

typedef enum			e_ematerial
{
	NOTHING,
	JADE
}						t_ematerial;

typedef enum			e_etexture
{
	TNOTHING,
	TCHECKER,
	TDEARTH,
	TNEARTH,
	TBRICK,
	TMARBLE,
	TJUPITER,
	TSTARS,
	TSNOW,
	TROCK,
	TWOOD,
	TPLOT,
	TBLUR,
	TPERLIN
}						t_etexture;

/*
**	STRUCT
*/

typedef struct			s_mlx
{
	void				*mlx;
	void				*image;
	void				*id;
	unsigned int		*mem_image;
	int					pix;
	int					size_line;
	int					endian;
}						t_mlx;

typedef struct			s_inter
{
	t_vector			pos;
	t_vector			color;
	t_vector			norm;
	t_vector			viewdir;
	t_vector			lightdir;
	t_vector			refdir;
	t_vector			refrdir;
	double				kr;
	char				blinn;
	int					id;
}						t_inter;

typedef struct			s_material
{
	t_vector			ambient;
	t_vector			diffuse;
	t_vector			specular;
	float				shininess;
}						t_material;

# define NB_FIELDS_LUM 7

typedef struct			s_texture
{
	t_vector			color;
	double				atexture;
	int					scale;
	int					type;
	double				x;
	double				y;
}						t_texture;

typedef struct			s_timage
{
	int					height;
	int					width;
	void				*buffer;
	char				*buffer_ptr;
}						t_timage;

// #define NB_FIELDS_LUM 5

typedef struct			s_lum
{
	t_vector			pos;
	t_vector			dir;
	t_vector			color;
	t_ltype				type;
	char				fields[NB_FIELDS_LUM];
	double				cutoff;
	double				outercutoff;
	double				constant;
	double				linear;
	double				quadratic;
}						t_lum;

typedef	struct			s_ray
{
	t_vector			o;
	t_vector			dir;
}						t_ray;

typedef struct			s_cam
{
	t_vector			pos;
	t_vector			vec_dir[3];
	t_vector			vp_upleft;
	t_vector			rotation;
	double				vp_width;
	double				vp_height;
	double				vp_dist;
}						t_cam;

# define NB_FIELDS 18
# define NBR_VECTOR_FORM 5

typedef struct			s_form
{
	t_ftype				ftype;
	t_vector			center;
	t_vector			point;
	t_vector			direct;
	t_vector			max;
	t_vector			min;
	double				r;
	double				h;
	double				angle;
	t_vector			color;
	t_vector			rotation;
	t_texture			texture;
	t_timage			timage;
	t_material			material;
	double				iref;
	double				itpy;
	double				irefr;
	char				fields[NB_FIELDS];
	double				mat[3][3][3];
	double				mati[3][3][3];
}						t_form;

typedef struct			s_scene
{
	float				ambient;
	float				spec;
	char				aa;
	char				blinn;
	t_material			material[NBR_MATERIAL];
}						t_scene;

typedef struct			s_env
{
	t_mlx				mlx;
	t_scene				scene;
	t_cam				cam;
	int					nbr_form;
	int					nbr_lum;
	t_form				*form;
	t_lum				*lum;
	t_vector			color;
	char				key_repeat;
	int					offset;
	int					line_id;
}						t_env;

/*
** perlin var
*/

typedef struct			s_perlin
{
	int					ix0;
	int					iy0;
	int					iz0;
	int					ix1;
	int					iy1;
	int					iz1;
	float				fx0;
	float				fy0;
	float				fz0;
	float				fx1;
	float				fy1;
	float				fz1;
	float				s;
	float				t;
	float				r;
	float				nxy0;
	float				nxy1;
	float				nx0;
	float				nx1;
	float				n0;
	float				n1;
}						t_perlin;

int						rt_main(t_env *env);
void					rt_delenv(t_env *env);

/*
**	shapes
*/

t_vector				rt_no_inter(void);
double					rt_first_inter(t_env *env, t_ray ray_o, t_inter *inter);
int						rt_shape_inter(t_env *env, int *indsh, t_ray *ray,
		double *min);
t_vector				rt_viewdir_inter(t_env *env, t_ray ray, int depth);
double					rt_sphere(t_ray ray, t_form form);
double					rt_torus(t_ray ray, t_form form);
double					rt_plan(t_ray ray, t_form form);
double					rt_cylindre(t_ray ray, t_form form);
double					rt_cone(t_ray ray, t_form form);
double					rt_hyperbol(t_ray ray, t_form form);
double					rt_cubet(t_ray ray, t_form form);

t_vector				rt_norm_torus(t_vector pos, t_form form);
t_vector				rt_norm_hyper(t_vector pos, t_form form);
t_vector				rt_norm_cubet(t_vector pos, t_form form);

double					rt_limit(double res, t_ftype ftype, t_ray *ray,
		t_form form);
double					rt_selectf(t_ftype ftype, t_ray *ray, t_form form);

/*
**	print
*/

int						rt_print(void *param);
void					rt_thread(void *env, void *(func)(void*));
void					rt_add_pixel(t_env *env, t_vector color, int pos);
t_vector				rt_reflection(t_env *env, t_inter inter, int depth);
t_vector				rt_refraction(t_env *env, t_inter inter, int depth);

/*
**	light
*/

t_vector				rt_light_manager(t_env *env, t_inter inter);
t_vector				rt_spec(t_vector light, t_inter inter,
		t_material mat, double attenuation);
t_vector				rt_diffuse(t_vector light, double angle,
		t_material mat, double attenuation);
t_vector				rt_ambient(t_vector light, t_material mat,
		double attenuation);
double					rt_attenuation(t_lum lum, double dist);
t_vector				rt_get_lightdir(t_vector o, t_lum lum);
double					rt_spotlight(t_vector pos, t_lum lum);
t_vector				rt_get_refdir(t_vector normal, t_vector dir,
		double ndoti);
t_vector				rt_get_refrdir(double n2, t_inter inter, double ndoti,
		t_vector vdir);
double					rt_fresnel(double idir, double n2);

/*
** color
*/

t_vector				rt_attribute_color(int color);
t_vector				rt_get_color(t_lum lum, t_inter inter,
		t_material mat);
t_vector				rt_ambient_only(t_lum lum, t_material mat,
		t_inter inter);

/*
**	calc
*/

double					ft_4th_degree(double var[5]);
t_vector				rt_get_vecdir(t_cam cam, double x, double y);
t_vector				rt_get_posinter(t_ray ray, double dist);
t_vector				rt_get_normal(t_vector v, t_form form, t_vector vdir);
double					rt_inter(t_ftype ftype, t_ray *ray, t_form form);

/*
**	key_handler
*/

int						rt_keypress(int keycode, void *param);
int						rt_keyrelease(int keycode, void *param);
int						rt_close(void *param);
void					rt_escap(t_env *env, int keycode);
void					rt_aa_blinn(t_env *env, int keycode);

/*
**	mouse_handler
*/

int						rt_mousepress(int keycode, int x, int y, void *param);

/*
**	camera
*/

void					rt_update_campos(t_cam *cam);
void					rt_update_camrot(t_cam *cam, double mat[3][3][3]);
void					rt_movecam_pos(t_env *env, int keycode);
void					rt_movecam_rot(t_env *env, int keycode);
void					rt_mmovecam_pos(t_env *env, int keycode);

/*
**	rotation
*/

void					rt_initialize_rotation(t_env *env);
void					rt_set_ref(t_ray *ray, t_form form);
void					rt_reset_point(t_form form, t_vector *inte);

/*
**	materials
*/

t_material				rt_get_material(t_ematerial emat, t_scene scene);
int						rt_material_diffuse(double mat[3], int type);
int						rt_material_specular(double mat[3], int type);
int						rt_material_ambient(double mat[3], int type);
double					rt_material_shininess(int type);

/*
**	texture
*/

void					rt_init_texture(t_env *env);
void					rt_get_texture(t_env *env, t_texture texture,
		t_vector normal, t_inter *inter);
t_vector				rt_tchecker(t_vector normal, t_vector intercolor,
		t_env *env,	t_inter *inter);
t_vector				rt_tmap(t_vector normal, t_vector intercolor,
		t_env *env, t_inter *inter);
t_vector				rt_tperlin(t_vector normal, t_vector intercolor,
		t_env *env, t_inter *inter);

/*
**	Perlin
*/

unsigned char			rt_perm(int i);
double					rt_fade(double t);
double					rt_fastfloor(double x);
double					rt_lerp(double t, double a, double b);
float					rt_perlin2d(float x, float y, float freq, int depth);
float					rt_noise3(float x, float y, float z);
t_vector				rt_perlin_marble(float u, float v, t_texture text);
t_vector				rt_perlin_lava(float u, float v, t_texture text);
t_vector				rt_perlin_sand(float u, float v, t_texture text);
t_vector				rt_perlin_wood(float u, float v, t_texture text);

/*
** bump mapping
*/

void					rt_bump_idk(t_vector *bump, t_vector pos);
void					rt_bump_water(t_vector *bump, t_vector pos);
void					rt_bump_cos(t_vector *bump, t_vector pos);

#endif
