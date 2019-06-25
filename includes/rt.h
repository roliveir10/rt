/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 10:58:12 by roliveir          #+#    #+#             */
/*   Updated: 2019/06/24 13:59:20 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _RT_H
# define _RT_H

# include "libft.h"

# define SCREENX 2080
# define SCREENY 1170
# define SCREEN SCREENX * SCREENY

# define NBR_FORM 4
# define NBR_THREAD 4
# define NBR_MATERIAL 2
# define NBR_KEY 13
# define NBR_KEY_REPEAT 11
# define NBR_MKEY 2
# define PIX 32

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

typedef struct			s_lum
{
	t_vector			pos;
	t_vector			dir;
	t_vector			color;
	t_ltype				type;
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

typedef struct			s_form
{
	t_ftype				ftype;
	t_vector			center;
	t_vector			point;
	t_vector			direct;
	double				r;
	double				h;
	double				angle;
	t_vector			color;
	t_vector			rotation;
	t_material			material;
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

int						rt_main(t_env *env);
void					rt_delenv(t_env *env);

/*
**	shapes
*/

t_vector				rt_viewdir_inter(t_env *env, t_ray ray);
double					rt_sphere(t_ray ray, t_form form);
double					rt_plan(t_ray ray, t_form form);
double					rt_cylindre(t_ray ray, t_form form);
double					rt_cone(t_ray ray, t_form form);

/*
**	print
*/

int						rt_print(void *param);
void					rt_thread(void *env, void *(func)(void*));
void					rt_add_pixel(t_env *env, t_vector color, int pos);
int						rt_antialiasing(t_env *env);

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

/*
** color
*/

void					rt_attribute_color(int color, t_vector *s_color);
t_vector				rt_get_color(t_lum lum, t_inter inter,
		t_material mat);
t_vector				rt_ambient_only(t_lum lum, t_material mat,
		t_inter inter);

/*
**	calc
*/

t_vector				rt_get_vecdir(t_cam cam, double x, double y);
t_vector				rt_get_posinter(t_ray ray, double dist);
t_vector				rt_get_normal(t_vector v, t_form form);
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

void					rt_initialize_rotation(t_form **form, t_cam *cam,
		int nbr_form);
void					rt_set_ref(t_ray *ray, t_form form);
void					rt_reset_point(t_form form, t_vector *inte);

/*
**	materials
*/

t_material				rt_get_material(t_ematerial emat, t_scene scene);

#endif
