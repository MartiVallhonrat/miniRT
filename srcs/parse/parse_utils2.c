/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvallhon <mvallhon@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:59:07 by mvallhon          #+#    #+#             */
/*   Updated: 2024/06/14 18:31:58 by mvallhon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/MiniRT.h"

void	atod_aux(char *str, double *res, int *i, int *decimal)
{
	while (str[*i] && str[*i] != ','
		&& ((str[*i] >= '0' && str[*i] <= '9') || str[*i] == '.'))
	{
		if (*decimal > 0)
			*decimal *= 10;
		if (str[*i] == '.' || str[*i] == ',')
			*decimal = 1;
		else
			*res = *res * 10 + (str[*i] - 48);
		(*i)++;
	}
}

void	handle_line_error(t_vars *rt, const char *strerr)
{
	if (rt->objs)
		free(rt->objs);
	ft_putstr_fd("Error: Missconfiguration in ", 2);
	ft_putendl_fd(strerr, 2);
	exit(EXIT_FAILURE);
}
