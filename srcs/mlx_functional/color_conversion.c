/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_conversion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvallhon <mvallhon@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:59:07 by mvallhon          #+#    #+#             */
/*   Updated: 2024/06/14 18:31:58 by mvallhon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/MiniRT.h"

int	get_r(int rgb)
{
	return ((rgb >> 16) & 0xFF);
}

int	get_g(int rgb)
{
	return ((rgb >> 8) & 0xFF);
}

int	get_b(int rgb)
{
	return (rgb & 0xFF);
}

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}
