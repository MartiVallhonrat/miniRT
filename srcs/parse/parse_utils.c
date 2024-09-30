/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvallhon <mvallhon@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:59:07 by mvallhon          #+#    #+#             */
/*   Updated: 2024/06/14 18:31:58 by mvallhon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/MiniRT.h"

t_rgb	parse_colors(char *line, int *i)
{
	t_rgb	rgb;

	ft_iterspace(line, i);
	rgb.r = ft_atoi(&line[*i]);
	while (line[*i] != ',')
		(*i)++;
	rgb.g = ft_atoi(&line[++(*i)]);
	while (line[++(*i)] != ',')
		;
	rgb.b = ft_atoi(&line[++(*i)]);
	return (rgb);
}

t_vector	parse_coords(char *line, int *i, t_vars *rt)
{
	t_vector	crd;

	ft_iterspace(line, i);
	crd.x = ft_atod(line, *i, rt);
	while (line[*i] && line[*i] != ',')
		(*i)++;
	(*i)++;
	crd.y = ft_atod(line, *i, rt);
	while (line[*i] && line[*i] != ',')
		(*i)++;
	(*i)++;
	crd.z = ft_atod(line, *i, rt);
	while (line[*i] && line[*i] != ' ' && line[*i] != '\t')
		(*i)++;
	return (crd);
}

bool	check_identifier(char *line, int i, int type)
{
	if (type == 1)
	{
		if (line[i + 1] && (line[i + 1] == ' ' || line[i + 1] == '\t'))
			return (true);
		else
			return (false);
	}
	if (!ft_strncmp("pl", &line[i], 2)
		|| !ft_strncmp("sp", &line[i], 2)
		|| !ft_strncmp("cy", &line[i], 2))
	{
		i += 2;
		if (line[i] && (line[i] == ' ' || line[i] == '\t'))
			return (true);
		else
			return (false);
	}
	return (false);
}

void	ft_iterspace(char *line, int *i)
{
	if (line && line[*i])
	{
		while (line[*i] && line[*i] != '\n'
			&& (line[*i] == ' ' || line[*i] == '\t'))
			(*i)++;
	}
}

double	ft_atod(const char *str, int i, t_vars *rt)
{
	double	res;
	double	negative;
	int		decimal;

	negative = 1;
	res = 0;
	decimal = 0;
	if (str[i] != '-' && (str[i] < '0' || str[i] > '9'))
	{
		ft_putendl_fd("Error: Missconfiguration in file", 2);
		if (rt->objs)
			free(rt->objs);
		exit(EXIT_FAILURE);
	}
	if (str[i] == '-')
	{
		i++;
		negative = -1;
	}
	atod_aux((char *)str, &res, &i, &decimal);
	if (decimal)
		res /= decimal;
	return (res * negative);
}
