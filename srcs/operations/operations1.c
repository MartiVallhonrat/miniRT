/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvallhon <mvallhon@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:59:07 by mvallhon          #+#    #+#             */
/*   Updated: 2024/06/14 18:31:58 by mvallhon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/MiniRT.h"

t_vector	addition(t_vector vec1, t_vector vec2)
{
	t_vector	res;

	res.x = vec1.x + vec2.x;
	res.y = vec1.y + vec2.y;
	res.z = vec1.z + vec2.z;
	return (res);
}

t_vector	subtraction(t_vector vec1, t_vector vec2)
{
	t_vector	res;

	res.x = vec1.x - vec2.x;
	res.y = vec1.y - vec2.y;
	res.z = vec1.z - vec2.z;
	return (res);
}

t_vector	negative(t_vector vec)
{
	t_vector	res;

	res.x = vec.x * -1;
	res.y = vec.y * -1;
	res.z = vec.z * -1;
	return (res);
}

t_vector	multiplication(float const_v, t_vector vec)
{
	t_vector	res;

	res.x = vec.x * const_v;
	res.y = vec.y * const_v;
	res.z = vec.z * const_v;
	return (res);
}

t_vector	division(float const_v, t_vector vec)
{
	t_vector	res;

	res.x = vec.x / const_v;
	res.y = vec.y / const_v;
	res.z = vec.z / const_v;
	return (res);
}
