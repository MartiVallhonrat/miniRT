/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvallhon <mvallhon@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:59:07 by mvallhon          #+#    #+#             */
/*   Updated: 2024/06/14 18:31:58 by mvallhon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/MiniRT.h"

void	set_cyl_colision(t_ray *ray, t_object *obj, t_cyldata *data)
{
	data->inter = addition(ray->og, multiplication(data->d.t, ray->dir));
	obj->normal = normalize(subtraction(data->inter, subtraction(obj->coords,
					multiplication(data->m, obj->n_rot))));
	ray->max_t = data->d.t;
	ray->colision = obj;
}

static void	calculate_equation(t_ray *ray, t_object *obj, t_cyldata *data)
{
	data->d.a = dot(ray->dir, ray->dir) - powf(dot(ray->dir, obj->n_rot), 2);
	data->d.b = 2 * (dot(ray->dir, data->x) - dot(ray->dir, obj->n_rot)
			* dot(data->x, obj->n_rot));
	data->d.c = dot(data->x, data->x) - powf(dot(data->x, obj->n_rot), 2)
		- powf(obj->diameter / 2, 2);
	data->d.delta = powf(data->d.b, 2.0f) - 4.0f * data->d.a * data->d.c;
}

void	cylinder_aux(t_ray *ray, t_object *obj, t_cyldata *data)
{
	data->to_cam = subtraction(ray->og, obj->coords);
	data->theta = dot(data->to_cam, obj->n_rot);
	obj->n_rot = normalize(obj->n_rot);
	data->neg_nrot = negative(obj->n_rot);
	data->c = addition(obj->coords,
			multiplication(obj->height / 2.0f, data->neg_nrot));
	data->l = addition(data->c, multiplication(obj->height, obj->n_rot));
	data->d.t = ray->max_t;
	data->x = subtraction(ray->og, obj->coords);
	if (data->theta > 0)
	{
		data->cap.coords = data->l;
		data->cap.normal = obj->n_rot;
		caps_intersection(ray, obj, &data->cap);
	}
	else if (data->theta < 0)
	{
		data->cap.coords = data->c;
		data->cap.normal = data->neg_nrot;
		caps_intersection(ray, obj, &data->cap);
	}
	calculate_equation(ray, obj, data);
}
