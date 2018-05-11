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

# define FIRST_WORD_LENGTH 15
# define SHORT_WORD_LENGTH 10

# define WIN_WIDTH 1000
# define WIN_HEIGHT 1000

typedef struct s_strlst	t_strlst;

typedef struct s_vector	t_vector;
typedef struct s_point	t_point;
typedef struct s_color	t_color;
typedef struct s_object	t_object;
typedef struct s_light	t_light;

typedef struct s_rtv	t_rtv;

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

	void		**mlx;
};

void		rtv_init(t_rtv *rtv);
int			get_scene(char *file, t_rtv *rtv);
int			scene_parse(t_rtv *rtv);
int			scene_parse_elems(t_rtv *rtv);
int			parse_camera(t_rtv *rtv, char *str);
int			parse_point(char *str, int *i, t_point *point);
int			parse_angles(char *str, int *i, double *angles);

void		skip_space_symbols(char *str, int *iter);
void		skip_nonspace_symbols(char *str, int *iter);

t_strlst	*new_str_lst_node();
int			str_lst_append_node(t_strlst **list);
void		del_str_lst(t_strlst **root);

int			graphic_window();

int			tracer(t_vector *ray_dir, t_rtv *rtv);
void		throw_rays(t_rtv *rtv);

int			close_win(void);
int			key_hook(int keycode, t_rtv *rtv);

void		*error_perror_null(const char *str);
int			error_perror_int(const char *str);
void		*error_str_null(const char *str);
int			error_str_int(const char *str);
void		usage_error(const char *name);

void		draw_line(float *p0, float *p1, int color, void **mlx);

double		vector_dot_prod(t_vector *vect_1, t_vector *vect_2);
double		vector_dot_point(t_vector *vect, t_point *p);
double		vector_length(t_vector *vector);
void		vector_normalize(t_vector *v, t_vector *v_res);
t_vector	vector_from_points(t_point *end, t_point *begin);
t_vector	vector_sum(t_vector *v_1, t_vector *v_2, char sign);
t_vector	vector_mult_scalar(t_vector *vect, double scalar);

t_point		inters_point(t_point *orig, double t, t_vector *vect);
t_vector 	rotate_cam_ray(double *trigon, t_vector *vect);

double		inters_distance(t_vector *ray, t_object *object, t_point *pos);
double		interSpher(t_vector *ray_dir, t_object *sphere, t_point *p);
int			intersect_shadow(t_point *p, t_vector *l, double min, double max, t_rtv *rtv);
t_vector	get_object_normal(t_point *p, t_object *obj);
int			get_res_color(t_color color, float intense);
float		reflection(t_point *p, t_vector *n, t_vector v, int obj, t_rtv *rtv);
int			rgb(t_color color);

#endif