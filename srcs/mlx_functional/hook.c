/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvallhon <mvallhon@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:59:07 by mvallhon          #+#    #+#             */
/*   Updated: 2024/06/14 18:31:58 by mvallhon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/MiniRT.h"

int	key_hook(int keycode, t_vars *rt)
{
	if (ESC_KEY == keycode)
	{
		mlx_destroy_window(rt->mlx.mlx_ptr, rt->mlx.win_ptr);
		if (rt->objs)
			free(rt->objs);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int	close_win_mouse(t_vars *rt)
{
	mlx_destroy_window(rt->mlx.mlx_ptr, rt->mlx.win_ptr);
	if (rt->objs)
		free(rt->objs);
	exit(EXIT_SUCCESS);
}
