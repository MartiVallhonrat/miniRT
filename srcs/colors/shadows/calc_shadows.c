/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_shadows.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvallhon <mvallhon@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:59:07 by mvallhon          #+#    #+#             */
/*   Updated: 2024/06/14 18:31:58 by mvallhon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/MiniRT.h"

static float	set_max(t_ray *ray, t_vector x)
{
	float	t;

	t = 0.0f;
	if (ray->dir.x != 0.0f)
		t = (x.x - ray->og.x) / ray->dir.x;
	else if (ray->dir.y != 0.0f)
		t = (x.y - ray->og.y) / ray->dir.y;
	else if (ray->dir.z != 0.0f)
		t = (x.z - ray->og.z) / ray->dir.z;
	return (t);
}

int	is_shadow(t_vars *rt, t_ray *past_ray, t_vector n_light)
{
	t_ray	new_ray;

	new_ray.og = addition(past_ray->og, \
		multiplication(past_ray->max_t, past_ray->dir));
	new_ray.dir = n_light;
	new_ray.colision = NULL;
	new_ray.max_t = set_max(&new_ray, rt->light.coords);
	check_intersections(rt, &new_ray);
	if (new_ray.colision && new_ray.max_t > MIN_T)
		return (1);
	return (0);
}
