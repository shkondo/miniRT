/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkondo <shkondo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 00:00:00 by djspright         #+#    #+#             */
/*   Updated: 2026/07/15 15:23:07 by shkondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifdef __APPLE__
#  define KEY_ESC 53
# else
#  define KEY_ESC 65307
# endif

# define EVENT_KEYPRESS 2
# define EVENT_CLOSE 17
# define MASK_KEYPRESS 1L
# define MASK_NONE 0L

# define WIN_W 1280
# define WIN_H 720
# define WIN_TITLE "miniRT"
# define EPSILON 1e-6
# define SHADOW_BIAS 1e-4
# define INF 1e30
# define PI 3.14159265358979323846

typedef struct s_vec3
{
	double			x;
	double			y;
	double			z;
}					t_vec3;

typedef struct s_color
{
	int				r;
	int				g;
	int				b;
}					t_color;

typedef struct s_ray
{
	t_vec3			origin;
	t_vec3			dir;
}					t_ray;

typedef enum e_obj_type
{
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER
}					t_obj_type;

typedef struct s_object
{
	t_obj_type		type;
	t_vec3			pos;
	t_vec3			axis;
	double			radius;
	double			height;
	t_color			color;
	struct s_object	*next;
}					t_object;

typedef struct s_ambient
{
	double			ratio;
	t_color			color;
	int				set;
}					t_ambient;

typedef struct s_camera
{
	t_vec3			pos;
	t_vec3			dir;
	double			fov;
	t_vec3			right;
	t_vec3			up;
	double			half_w;
	double			half_h;
	int				set;
}					t_camera;

typedef struct s_light
{
	t_vec3			pos;
	double			ratio;
	t_color			color;
	int				set;
}					t_light;

typedef struct s_scene
{
	t_ambient		ambient;
	t_camera		camera;
	t_light			light;
	t_object		*objects;
}					t_scene;

typedef struct s_hit
{
	int				hit;
	double			t;
	t_vec3			point;
	t_vec3			normal;
	t_color			color;
}					t_hit;

typedef struct s_quad
{
	double			a;
	double			b;
	double			c;
	double			disc;
}					t_quad;

typedef struct s_cap
{
	t_vec3			center;
	t_vec3			normal;
	double			radius;
}					t_cap;

typedef struct s_img
{
	void			*ptr;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
}					t_img;

typedef struct s_app
{
	void			*mlx;
	void			*win;
	t_img			img;
	t_scene			scene;
}					t_app;

t_vec3				vec(double x, double y, double z);
t_vec3				vec_add(t_vec3 a, t_vec3 b);
t_vec3				vec_sub(t_vec3 a, t_vec3 b);
t_vec3				vec_scale(t_vec3 a, double s);
t_vec3				vec_mul(t_vec3 a, t_vec3 b);

double				vec_dot(t_vec3 a, t_vec3 b);
t_vec3				vec_cross(t_vec3 a, t_vec3 b);
double				vec_len(t_vec3 a);
double				vec_len2(t_vec3 a);
t_vec3				vec_norm(t_vec3 a);

t_vec3				vec_neg(t_vec3 a);
double				clampd(double v, double lo, double hi);
t_vec3				vec_at(t_ray ray, double t);
t_vec3				face_normal(t_vec3 n, t_vec3 dir);

t_color				color_new(int r, int g, int b);
t_vec3				color_to_vec(t_color c);
int					vec_to_rgb(t_vec3 c);

int					init_window(t_app *app);
void				put_pixel(t_img *img, int x, int y, int color);
int					close_app(t_app *app);
void				setup_hooks(t_app *app);
int					key_hook(int keycode, t_app *app);
void				platform_cleanup(void *mlx);

void				render_scene(t_app *app);
int					ray_color(t_scene *scene, t_ray ray);
void				setup_camera(t_camera *cam);
t_ray				make_ray(t_camera *cam, double px, double py);

t_hit				trace_ray(t_scene *scene, t_ray ray);
int					hit_object(t_object *obj, t_ray ray, t_hit *hit);
int					hit_sphere(t_object *obj, t_ray ray, t_hit *hit);
int					hit_plane(t_object *obj, t_ray ray, t_hit *hit);
int					hit_cylinder(t_object *obj, t_ray ray, t_hit *hit);
int					hit_cyl_body(t_object *obj, t_ray ray, t_hit *hit);
int					hit_cyl_caps(t_object *obj, t_ray ray, t_hit *hit);
int					solve_quad(t_quad *q, double *t);
int					solve_quad2(t_quad *q, double *t0, double *t1);

t_vec3				compute_lighting(t_scene *scene, t_hit hit);
int					in_shadow(t_scene *scene, t_hit hit, t_vec3 ldir,
						double ldist);

int					parse_scene(char *path, t_scene *scene);
int					parse_line(char *line, t_scene *scene);
int					parse_ambient(char **tok, t_scene *scene);
int					parse_camera(char **tok, t_scene *scene);
int					parse_light(char **tok, t_scene *scene);
int					parse_sphere(char **tok, t_scene *scene);
int					parse_plane(char **tok, t_scene *scene);
int					parse_cylinder(char **tok, t_scene *scene);

int					parse_double(char *s, double *out);
int					parse_vec3(char *s, t_vec3 *out);
int					parse_color(char *s, t_color *out);
int					parse_ratio(char *s, double *out);
int					parse_unit(char *s, t_vec3 *out);

void				init_scene(t_scene *scene);
int					add_object(t_scene *scene, t_object obj);
void				free_scene(t_scene *scene);
int					validate_scene(t_scene *scene);

int					error_msg(char *msg);
void				error_exit(t_app *app, char *msg);
size_t				ft_strlen(const char *s);
int					ft_strncmp(const char *a, const char *b, size_t n);
int					count_char(const char *s, int c);
char				**split_set(char *s, char *set);
void				free_split(char **tab);
int					count_tokens(char **tab);
char				*read_file(int fd);
int					ft_isspace(int c);
int					ft_atod(char *s, double *out);

#endif
