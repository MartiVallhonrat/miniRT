/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvallhon <mvallhon@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:59:07 by mvallhon          #+#    #+#             */
/*   Updated: 2024/06/14 18:31:58 by mvallhon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/MiniRT.h"

bool	check_ambient(char *line, int i) /* DONE */
{
	int	trigger;

	trigger = 0;
	ft_iterspace(line, &i);
	if (!check_number(line, i, &trigger) && !check_double(line, &i))
		return (false);
	else if (trigger)
		check_double(line, &i);
	if (!check_colors_aux(line, &i))
		return (false);
	return (true);
}

bool	check_camera(char *line, int i)
{
	int	counter;

	counter = 0;
	while (counter < 2)
	{
		ft_iterspace(line, &i);
		if (!check_coords(line, &i))
			return (false);
		counter++;
	}
	ft_iterspace(line, &i);
	if (line[i] == '-')
		i++;
	while (line[i] && ft_isdigit(line[i]))
		i++;
	ft_iterspace(line, &i);
	if (line[i] && line[i] != '\n')
		return (false);
	return (true);
}

bool	check_light_or_sphere(char *line, int i)
{
	int	trigger;

	trigger = 0;
	ft_iterspace(line, &i);
	if (!check_coords(line, &i))
		return (false);
	ft_iterspace(line, &i);
	if (!check_number(line, i, &trigger) && !check_double(line, &i))
		return (false);
	else if (trigger)
		check_double(line, &i);
	if (!check_colors_aux(line, &i))
		return (false);
	return (true);
}

bool	check_plane(char *line, int i)
{
	int	counter;

	counter = 0;
	while (counter < 2)
	{
		ft_iterspace(line, &i);
		if (!check_coords(line, &i))
			return (false);
		counter++;
	}
	if (!check_colors_aux(line, &i))
		return (false);
	return (true);
}

bool	check_cylinder(char *line, int i)
{
	int	counter;
	int	trigger;

	counter = 0;
	trigger = 0;
	while (counter < 2)
	{
		ft_iterspace(line, &i);
		if (!check_coords(line, &i))
			return (false);
		counter++;
	}
	while (counter < 4)
	{
		ft_iterspace(line, &i);
		if (!check_number(line, i, &trigger) && !check_double(line, &i))
			return (false);
		else if (trigger)
			check_double(line, &i);
		trigger = 0;
		counter++;
	}
	if (!check_colors_aux(line, &i))
		return (false);
	return (true);
}
