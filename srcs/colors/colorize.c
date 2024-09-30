/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvallhon <mvallhon@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:59:07 by mvallhon          #+#    #+#             */
/*   Updated: 2024/06/14 18:31:58 by mvallhon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/MiniRT.h"

void	colorize(t_vars *rt, t_ray *ray)
{
	t_myrgb		ray_myrgb;
	t_myrgb		ambcolor_myrgb;
	t_myrgb		amblight_myrgb;
	t_vector	n_light;
	float		a_zeta;

	ray_myrgb = rgb_to_myrgb(ray->colision->color);
	ambcolor_myrgb = rgb_to_myrgb(rt->ambient.color);
	n_light = normalize(rt->light.coords);
	a_zeta = dot(n_light, ray->colision->normal);
	amblight_myrgb = rgb_add(rgb_const_mult(rt->ambient.range, ray_myrgb), \
		rgb_const_mult(rt->ambient.range, ambcolor_myrgb));
	if (a_zeta > 0 && is_shadow(rt, ray, n_light) == 0)
		ray_myrgb = rgb_add(rgb_const_mult(rt->light.brightness, \
			rgb_const_mult(a_zeta, ray_myrgb)), amblight_myrgb);
	else
		ray_myrgb = amblight_myrgb;
	ray->rgb = myrgb_to_rgb(ray_myrgb);
}
