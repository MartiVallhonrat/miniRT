/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_intersections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvallhon <mvallhon@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:59:07 by mvallhon          #+#    #+#             */
/*   Updated: 2024/06/14 18:31:58 by mvallhon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/MiniRT.h"

void	check_intersections(t_vars *rt, t_ray *ray)
{
	int		i;

	i = -1;
	while (++i < rt->obj_amount)
	{
		if (rt->objs[i].type == PLANE)
			plane_intersection(ray, &rt->objs[i]);
		else if (rt->objs[i].type == SPHERE)
			sphere_intersection(ray, &rt->objs[i]);
		else if (rt->objs[i].type == CYLINDER)
			cylinder_intersection(ray, &rt->objs[i]);
	}
}
