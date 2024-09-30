/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvallhon <mvallhon@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:59:07 by mvallhon          #+#    #+#             */
/*   Updated: 2024/06/14 18:31:58 by mvallhon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/MiniRT.h"

/* Modifica los valores entre 0 y 255 a 0 y 1 */

t_myrgb	rgb_to_myrgb(t_rgb color)
{
	t_myrgb	new_color;

	new_color.r = color.r / 255.f;
	new_color.g = color.g / 255.f;
	new_color.b = color.b / 255.f;
	return (new_color);
}

/* Modifica los valores entre 0 y 1 a 0 y 255 */

t_rgb	myrgb_to_rgb(t_myrgb color)
{
	t_rgb	new_color;

	new_color.r = color.r * 255.f;
	new_color.g = color.g * 255.f;
	new_color.b = color.b * 255.f;
	return (new_color);
}
