/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_values.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvallhon <mvallhon@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:59:07 by mvallhon          #+#    #+#             */
/*   Updated: 2024/06/14 18:31:58 by mvallhon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/MiniRT.h"

t_camera	parse_camera(char *line, int i, t_vars *rt)
{
	t_camera	camera;

	if (!check_camera(line, i))
		handle_line_error(rt, "camera");
	camera.coords = parse_coords(line, &i, rt);
	ft_iterspace(line, &i);
	camera.orientation = parse_coords(line, &i, rt);
	ft_iterspace(line, &i);
	camera.fov = ft_atoi(&line[i]);
	return (camera);
}

t_light	parse_light(char *line, int i, t_vars *rt)
{
	t_light	light;

	if (!check_light_or_sphere(line, i))
		handle_line_error(rt, "light");
	light.coords = parse_coords(line, &i, rt);
	ft_iterspace(line, &i);
	light.brightness = ft_atod(line, i, rt);
	while (line[i] && line[i] != ' ' && line[i] != '\t')
		i++;
	light.color = parse_colors(line, &i);
	return (light);
}

t_object	parse_sphere(t_vars *rt, char *line, int i)
{
	t_object	obj;

	if (!check_light_or_sphere(line, i))
		handle_line_error(rt, "sphere");
	obj.type = SPHERE;
	obj.coords = parse_coords(line, &i, rt);
	ft_iterspace(line, &i);
	obj.diameter = ft_atod(line, i, rt);
	while (line[i] && line[i] != ' ' && line[i] != '\t')
		i++;
	obj.color = parse_colors(line, &i);
	return (obj);
}

t_object	parse_plane(t_vars *rt, char *line, int i)
{
	t_object	obj;

	if (!check_plane(line, i))
		handle_line_error(rt, "plane");
	obj.type = PLANE;
	obj.coords = parse_coords(line, &i, rt);
	obj.normal = parse_coords(line, &i, rt);
	obj.color = parse_colors(line, &i);
	return (obj);
}

t_object	parse_cylinder(t_vars *rt, char *line, int i)
{
	t_object	obj;
	int			counter;

	counter = -1;
	if (!check_cylinder(line, i))
		handle_line_error(rt, "cylinder");
	obj.type = CYLINDER;
	obj.coords = parse_coords(line, &i, rt);
	obj.n_rot = parse_coords(line, &i, rt);
	while (++counter < 2)
	{
		ft_iterspace(line, &i);
		if (!counter)
			obj.diameter = ft_atod(line, i, rt);
		else
			obj.height = ft_atod(line, i, rt);
		while (line[i] && line[i] != ' ' && line[i] != '\t')
			i++;
	}
	obj.color = parse_colors(line, &i);
	return (obj);
}
