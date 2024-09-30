/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_intersections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvallhon <mvallhon@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:59:07 by mvallhon          #+#    #+#             */
/*   Updated: 2024/06/14 18:31:58 by mvallhon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/MiniRT.h"

static void	operations_aux(t_data *d, t_ray *ray, t_object *obj)
{
	d->a = dot(ray->dir, ray->dir);
	d->b = dot(multiplication(2.f, ray->dir), \
		subtraction(ray->og, obj->coords));
	d->c = dot(subtraction(ray->og, obj->coords), \
		subtraction(ray->og, obj->coords)) - powf(obj->diameter / 2, 2);
	d->delta = powf(d->b, 2) - 4.0f * d->a * d->c;
	d->t = ray->max_t;
}

void	plane_intersection(t_ray *ray, t_object *obj)
{
	float	dot_dn;
	float	t;

	dot_dn = dot(ray->dir, obj->normal);
	if (dot_dn == 0.0000f)
		return ;
	t = dot(subtraction(obj->coords, ray->og), obj->normal) / dot_dn;
	if (t <= MIN_T || t >= ray->max_t)
	{
		return ;
	}
	ray->max_t = t;
	ray->colision = obj;
}

void	sphere_intersection(t_ray *ray, t_object *obj)
{
	t_data	d;

	operations_aux(&d, ray, obj);
	if (d.delta < 0.0000f)
		return ;
	else if (d.delta == 0.0000f)
		d.t = d.b / 2.0f * d.a;
	else
	{
		d.t_pos = ((-1 * d.b) + sqrtf(d.delta)) / (2.0f * d.a);
		d.t_neg = ((-1 * d.b) - sqrtf(d.delta)) / (2.0f * d.a);
		if (d.t_neg > MIN_T && d.t_neg < d.t)
			d.t = d.t_neg;
		else if (d.t_pos > MIN_T && d.t_pos < d.t)
			d.t = d.t_pos;
	}
	if (d.t <= MIN_T || d.t >= ray->max_t)
		return ;
	ray->max_t = d.t;
	ray->colision = obj;
	obj->normal = normalize(subtraction(addition(ray->og, \
		multiplication(d.t, ray->dir)), obj->coords));
}

//maybe dont work new supercode
void	caps_intersection(t_ray *ray, t_object *obj, t_object *cap)
{
	float	dot_dn;
	float	t;

	dot_dn = dot(ray->dir, cap->normal);
	if (dot_dn == 0.0000f)
		return ;
	t = dot(subtraction(cap->coords, ray->og), cap->normal) / dot_dn;
	if (t <= MIN_T || t >= ray->max_t)
	{
		return ;
	}
	if (length(subtraction(addition(ray->og, multiplication(t, ray->dir)), \
		cap->coords)) > obj->diameter / 2.0f)
	{
		return ;
	}
	ray->max_t = t;
	ray->colision = obj;
	obj->normal = cap->normal;
}

void	cylinder_intersection(t_ray *ray, t_object *obj)
{
	t_cyldata	data;

	cylinder_aux(ray, obj, &data);
	if (data.d.delta < 0.0000f)
		return ;
	else if (data.d.delta == 0.0000f)
		data.d.t = data.d.b / 2.0f * data.d.a;
	else
	{
		data.d.t_pos = ((-1 * data.d.b) + sqrtf(data.d.delta))
			/ (2.0f * data.d.a);
		data.d.t_neg = ((-1 * data.d.b) - sqrtf(data.d.delta))
			/ (2.0f * data.d.a);
	}
	if (data.d.t_neg > MIN_T && data.d.t_neg < data.d.t)
		data.d.t = data.d.t_neg;
	else if (data.d.t_pos > MIN_T && data.d.t_pos < data.d.t)
		data.d.t = data.d.t_pos;
	if (data.d.t <= MIN_T || data.d.t >= ray->max_t)
		return ;
	data.m = dot(ray->dir, obj->n_rot) * data.d.t + dot(data.x, obj->n_rot);
	if (data.m > obj->height / 2 || data.m < (obj->height / 2.0f * -1.0f))
		return ;
	set_cyl_colision(ray, obj, &data);
}
