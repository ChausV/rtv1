/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 18:01:53 by vchaus            #+#    #+#             */
/*   Updated: 2018/04/23 18:02:19 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV_H
# define RTV_H

/*
**	open(2)
*/
# include <fcntl.h>

/*
**	read(2), write(2), close(2)
*/
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

/*
**	malloc(), free(), exit(3)
*/
# include <stdlib.h>

/*
**	perror()
*/
# include <stdio.h>

/*
**	strerror()
*/
# include <string.h>

/*
**	math library
*/
# include <math.h>

/*
**	MinilibX library
*/
# include "mlx.h"

/*
**	LibFT library
*/
# include "libft.h"

/*
**	thread functions
*/
# include "pthread.h"

# define FIRST_WORD_LENGTH 15
# define SHORT_WORD_LENGTH 10

# define WIN_WIDTH 900
# define WIN_HEIGHT 700

# define IMG_WIDTH 800
# define IMG_HEIGHT 600
# define FRAME_WIDTH 2.0
// # define FRAME_HEIGHT
# define FRAME_DISTANCE 2.0

# define THR_NUM 40

typedef struct s_strlst	t_strlst;

typedef struct s_vector	t_vector;
typedef struct s_point	t_point;
typedef struct s_color	t_color;
typedef struct s_object	t_object;
typedef struct s_light	t_light;

typedef struct s_rtv	t_rtv;
typedef struct s_thread	t_thread;

struct	s_strlst
{
	char		*str;
	char		type;
	t_strlst	*next;
};

struct	s_point
{
	double	x;
	double	y;
	double	z;
};
struct	s_vector
{
	double	x;
	double	y;
	double	z;
};
struct	s_color
{
	int	r;
	int	g;
	int	b;
};
struct	s_object
{
	char		type;
	t_point		point;
	t_vector	vect;
	double		r;
	t_color		color;
	int			specular;
	double		to_w[4][4];
	double		to_o[4][4];
};
struct	s_light
{
	char		type;
	float		intens;
	t_point		position;
	t_vector	direction;
};

struct	s_rtv
{
	t_strlst	*inplst;
	int			num_obj;
	int			num_lig;
	int			num_cam;
	int			num_gla;
	int			num_sha;

	t_point		cam_pos;
	double		cam_ang[3];
	double		cam_tri[6];

	int			shadow;
	int			glare;

	t_object	**objects;
	t_light		**lights;

	void		*mlx[3];

	double		frame_h;
	double		half_frame_w;
	double		half_frame_h;
	double		step;

	double		x_start;
	double		y_start;
	int			lines_per_thr;

	char		*img;

	int			bg_color;
};
struct		s_thread
{
	t_rtv	*rtv;
	double	y_start;
	double	y_end;
	char	*image;
};

void		*error_perror_null(const char *str);
int			error_perror_int(const char *str);
void		*error_str_null(const char *str);
int			error_str_int(const char *str);
void		usage_error(const char *name);

void		rtv_init(t_rtv *rtv);
int			get_scene(char *file, t_rtv *rtv);
int			scene_parse(t_rtv *rtv);
int			scene_count_and_validation(t_rtv *rtv);
void		get_first_word(char *str, char **word);

t_strlst	*new_str_lst_node();
int			str_lst_append_node(t_strlst **list);
void		del_str_lst(t_strlst **root);

int			scene_memory_alloc(t_rtv *rtv);
void		scene_memory_free(t_rtv *rtv);

int			scene_parse_elems(t_rtv *rtv);
void		skip_space_symbols(char *str, int *iter);
void		skip_nonspace_symbols(char *str, int *iter);
int			word_equ(char *str, int *i, char *word);
int			parse_integer(char *str, int *i, int *target);
int			parse_double(char *str, int *i, double *res);
int			parse_point(char *str, int *i, t_point *point);
int			parse_vector(char *str, int *i, t_vector *vector);
int			parse_angles(char *str, int *i, double *angles);
int			parse_color(char *str, int *i, t_color *target);
int			parse_specularity(char *str, int *i, int *specul);

int			parse_glare(t_rtv *rtv, char *str);
int			parse_shadow(t_rtv *rtv, char *str);
int			parse_camera(t_rtv *rtv, char *str);
int			parse_light(t_rtv *rtv, char *str, int *curr);
int			parse_object(t_rtv *rtv, char *str, int *curr);
int			parse_obj_sphere(char *str, t_rtv *rtv, int *curr);
int			parse_obj_cylinder(char *str, t_rtv *rtv, int *curr);
int			parse_obj_cone(char *str, t_rtv *rtv, int *curr);

int			matrix_create(t_vector *v, t_point *p, t_object *obj);
void		matr_copy(double dest[4][4], double src[4][4]);
double		matr_determinant(double m[4][4]);
int			matrix_inverse(double m[4][4], double w[4][4]);
void		columns_to_zero(double tmp[4][4], double to_o[4][4]);
t_point		point_mult_matr(t_point *p, double m[4][4]);
t_vector	vect_mult_matr(t_vector *v, double m[4][4]);
t_vector	normal_mult_tr_matr(t_vector *v, double m[4][4]);



//void	set_camera_trigonometry(t_rtv *rtv);	//??????????????????????



int			graphic_window();
void		draw_line(float *p0, float *p1, int color, void **mlx);
int			close_win(t_rtv *rtv);
int			key_hook(int keycode, t_rtv *rtv);
void		destroy_and_exit(t_rtv *rtv);

double		inters_distance(t_vector *ray, t_object *object, t_point *pos);



int			tracer(t_vector *ray_dir, t_rtv *rtv);
void		*throw_rays(void *arg);
void		throw_rays_threads(t_rtv *rtv);

double		vector_dot_prod(t_vector *vect_1, t_vector *vect_2);
double		vector_dot_point(t_vector *vect, t_point *p);
double		vector_length(t_vector *vector);
void		vector_normalize(t_vector *v, t_vector *v_res);
t_vector	vector_from_points(t_point *end, t_point *begin);
t_vector	vector_sum(t_vector *v_1, t_vector *v_2, char sign);
t_vector	vector_mult_scalar(t_vector *vect, double scalar);
void		vector_cross_prod(t_vector *vect_1, t_vector *vect_2, t_vector *res);

t_point		inters_point(t_point *orig, double t, t_vector *vect);
t_vector 	rotate_cam_ray(double *trigon, t_vector *vect);


int			intersect_shadow(t_point *p, t_vector *l, double min, double max, t_rtv *rtv);
t_vector	get_object_normal(t_point *p, t_object *obj);
int			get_res_color(t_color color, float intense);
float		reflection(t_point *p, t_vector *n, t_vector v, int obj, t_rtv *rtv);
int			rgb(t_color color);

#endif
