/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MiniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvallhon <mvallhon@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:59:07 by mvallhon          #+#    #+#             */
/*   Updated: 2024/06/14 18:31:58 by mvallhon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include <stdbool.h>

# include "../libft/libft.h"
# include "get_next_line.h"
# include "../mlx_linux/mlx.h"

# define WIDTH	1920
# define HEIGHT	1080

enum	e_type
{
	SPHERE,
	PLANE,
	CYLINDER
};

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}			t_rgb;

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}				t_vector;

typedef struct s_camera
{
	t_vector	coords;
	t_vector	orientation;
	int			fov;
}				t_camera;

typedef struct s_light
{
	t_vector	coords;
	float		brightness;
	t_rgb		color;
}				t_light;

typedef struct s_ambient
{
	float		range;
	t_rgb		color;
}			t_ambient;

typedef struct s_object
{
	t_vector			coords;
	t_vector			normal;
	t_vector			n_rot;
	t_rgb				color;
	float				diameter;
	float				height;
	unsigned int		type;
}				t_object;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
}				t_mlx;

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bpp; //bits per pixel
	int		line_len;
	int		endian;
}				t_img;

typedef struct s_vars
{
	t_mlx		mlx;
	t_img		img;
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_object	*objs;
	int			obj_amount;
	int			obj_counter;
	float		a_ratio;
}			t_vars;

typedef struct s_data
{
	float	a;
	float	b;
	float	c;
	float	delta;
	float	t;
	float	t_pos;
	float	t_neg;
}				t_data;

//Rays
# define MIN_T 0.001f
# define MAX_T 1.0e30f

typedef struct s_ray
{
	t_vector	og;
	t_vector	dir;
	float		max_t;
	t_object	*colision;
	t_rgb		rgb;
}				t_ray;

//Structs for norme
typedef struct s_cyldata
{
	t_data		d;
	t_vector	to_cam;
	float		theta;
	t_object	cap;
	t_vector	neg_nrot;
	t_vector	c;
	t_vector	l;
	t_vector	x;
	double		m;
	t_vector	inter;
}				t_cyldata;

typedef struct s_iter
{
	float		h;
	float		w;
	int			i;
	int			j;
	float		radiant_fov;
	float		x;
	float		y;
	t_vector	upguide;
	t_vector	up;
	t_vector	right;
	t_ray		ray;
}				t_iter;

//Parse
void		parse_scene(t_vars *rt, char *arg);
void		parse_line(t_vars *rt, char *line);
t_ambient	parse_ambient(char *line, int i, t_vars *rt);
t_camera	parse_camera(char *line, int i, t_vars *rt);
t_light		parse_light(char *line, int i, t_vars *rt);
t_object	parse_sphere(t_vars *rt, char *line, int i);
t_object	parse_plane(t_vars *rt, char *line, int i);
t_object	parse_cylinder(t_vars *rt, char *line, int i);

//Parse Utils
void		ft_iterspace(char *line, int *i);
double		ft_atod(const char *str, int i, t_vars *rt);
void		atod_aux(char *str, double *res, int *i, int *decimal);
bool		check_identifier(char *line, int i, int type);
t_vector	parse_coords(char *line, int *i, t_vars *rt);
t_rgb		parse_colors(char *line, int *i);

//Checker
bool		check_ambient(char *line, int i);
bool		check_camera(char *line, int i);
bool		check_light_or_sphere(char *line, int i);
bool		check_plane(char *line, int i);
bool		check_cylinder(char *line, int i);
void		handle_line_error(t_vars *rt, const char *strerr);

//Checker Utils
bool		check_number(char *line, int i, int *trigger);
bool		check_double(char *line, int *i);
bool		check_coords(char *line, int *i);
bool		check_colors(char *line, int *i);
bool		check_colors_aux(char *line, int *i);

//Operations
t_vector	addition(t_vector vec1, t_vector vec2);
t_vector	subtraction(t_vector vec1, t_vector vec2);
t_vector	negative(t_vector vec);
t_vector	multiplication(float const_v, t_vector vec);
t_vector	division(float const_v, t_vector vec);
float		length(t_vector vec);
float		dot(t_vector vec1, t_vector vec2);
t_vector	cross(t_vector vec1, t_vector vec2);
t_vector	normalize(t_vector vec);

//Intersections
void		check_intersections(t_vars *rt, t_ray *ray);
void		plane_intersection(t_ray *ray, t_object *obj);
void		sphere_intersection(t_ray *ray, t_object *obj);
void		caps_intersection(t_ray *ray, t_object *obj, t_object *cap);
void		cylinder_intersection(t_ray *ray, t_object *obj);
void		set_cyl_colision(t_ray *ray, t_object *obj, t_cyldata *data);
void		cylinder_aux(t_ray *ray, t_object *obj, t_cyldata *data);

//MLX FUNCTIONAL
# define ESC_KEY 65307
/*hooks*/
int			key_hook(int keycode, t_vars *rt);
int			close_win_mouse(t_vars *rt);
/*colors*/
void		my_mlx_pixel_put(t_img *data, int x, int y, int color);
int			create_trgb(int t, int r, int g, int b);

//Colorize Ray

typedef struct s_myrgb
{
	float	r;
	float	g;
	float	b;
}			t_myrgb;

void		colorize(t_vars *rt, t_ray *ray);

//Rgb parse
t_myrgb		rgb_to_myrgb(t_rgb color);
t_rgb		myrgb_to_rgb(t_myrgb color);

//Rgb utils
t_myrgb		rgb_const_mult(float const_v, t_myrgb color);
t_myrgb		rgb_mult(t_myrgb color1, t_myrgb color2);
t_myrgb		rgb_add(t_myrgb color1, t_myrgb color2);

//Shadows
int			is_shadow(t_vars *rt, t_ray *past_ray, t_vector n_light);

#endif