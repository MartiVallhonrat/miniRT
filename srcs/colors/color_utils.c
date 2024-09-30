/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvallhon <mvallhon@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:59:07 by mvallhon          #+#    #+#             */
/*   Updated: 2024/06/14 18:31:58 by mvallhon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/MiniRT.h"

static t_myrgb	myrgb_clamp(t_myrgb color)
{
	if (color.r > 1.0f)
		color.r = 1.0f;
	if (color.g > 1.0f)
		color.g = 1.0f;
	if (color.b > 1.0f)
		color.b = 1.0f;
	if (color.r < 0.0f)
		color.r = 0.0f;
	if (color.g < 0.0f)
		color.g = 0.0f;
	if (color.b < 0.0f)
		color.b = 0.0f;
	return (color);
}

t_myrgb	rgb_const_mult(float const_v, t_myrgb color)
{
	t_myrgb	new_color;

	new_color.r = const_v * color.r;
	new_color.g = const_v * color.g;
	new_color.b = const_v * color.b;
	return (myrgb_clamp(new_color));
}

t_myrgb	rgb_mult(t_myrgb color1, t_myrgb color2)
{
	t_myrgb	new_color;

	new_color.r = color1.r * color2.r;
	new_color.g = color1.g * color2.g;
	new_color.b = color1.b * color2.b;
	return (new_color);
}

t_myrgb	rgb_add(t_myrgb color1, t_myrgb color2)
{
	t_myrgb	new_color;

	new_color.r = color1.r + color2.r;
	new_color.g = color1.g + color2.g;
	new_color.b = color1.b + color2.b;
	return (myrgb_clamp(new_color));
}
