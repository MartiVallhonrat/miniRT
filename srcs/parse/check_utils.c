/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvallhon <mvallhon@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:59:07 by mvallhon          #+#    #+#             */
/*   Updated: 2024/06/14 18:31:58 by mvallhon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/MiniRT.h"

bool	check_double(char *line, int *i)
{
	if (line[*i] == '-')
		(*i)++;
	if (!ft_isdigit(line[*i]))
		return (false);
	while (line[*i] && ft_isdigit(line[*i]))
		(*i)++;
	if (line[*i] == '.')
		(*i)++;
	else
		return (false);
	if (!ft_isdigit(line[*i]))
		return (false);
	while (line[*i] && ft_isdigit(line[*i]))
		(*i)++;
	if (line[*i] != '\n' && line[*i] != ','
		&& line[*i] != ' ' && line[*i] != '\t')
		return (false);
	return (true);
}

bool	check_colors(char *line, int *i)
{
	int	colon_counter;

	colon_counter = 0;
	while (line[*i] && line[*i] != '\n' && colon_counter < 3)
	{
		if (!ft_isdigit(line[*i]))
			return (false);
		while (line[*i] != '\n' && ft_isdigit(line[*i]))
			(*i)++;
		if (colon_counter == 2 && (line[*i] == ' '
				|| line[*i] == '\t' || line[*i] == '\n' || !line[*i]))
			return (true);
		else if (line[*i] == ',')
		{
			colon_counter++;
			(*i)++;
		}
		else
			return (false);
	}
	return (true);
}

bool	check_coords(char *line, int *i)
{
	int	trigger;
	int	counter;

	counter = 0;
	trigger = 0;
	while (counter < 2)
	{
		if (!check_number(line, *i, &trigger) && !check_double(line, i))
			return (false);
		else if (trigger)
		{
			check_double(line, i);
			trigger = 0;
		}
		if (line[*i] != ',')
			return (false);
		else
			(*i)++;
		counter++;
	}
	if (!check_number(line, *i, &trigger) && !check_double(line, i))
		return (false);
	else if (trigger)
		check_double(line, i);
	return (true);
}

bool	check_number(char *line, int i, int *trigger)
{
	if (line[i] == '-')
		i++;
	if (!ft_isdigit(line[i]))
		return (false);
	while (line[i] && ft_isdigit(line[i]))
		i++;
	if (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != ',')
		return (false);
	if (trigger)
		*trigger = 1;
	return (true);
}

bool	check_colors_aux(char *line, int *i)
{
	ft_iterspace(line, i);
	if (!check_colors(line, i))
		return (false);
	ft_iterspace(line, i);
	if (line[*i] && line[*i] != '\n')
		return (false);
	return (true);
}
