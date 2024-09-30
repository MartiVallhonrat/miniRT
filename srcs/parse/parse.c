/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvallhon <mvallhon@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:59:07 by mvallhon          #+#    #+#             */
/*   Updated: 2024/06/14 18:31:58 by mvallhon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/MiniRT.h"

static int	obj_amount(int fd, char *file)
{
	char	*line;
	int		amount;
	int		i;

	amount = 0;
	i = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		write(2, "Error: File does not exists or you don't ", 41);
		write(2, "have permission\n", 16);
		exit(EXIT_FAILURE);
	}
	line = get_next_line(fd);
	while (line)
	{
		i = 0;
		ft_iterspace(line, &i);
		if (check_identifier(line, i, 0))
			amount++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (amount);
}

static void	init_objects(t_vars *rt, char *arg)
{
	int	fd;

	fd = 0;
	rt->objs = NULL;
	rt->obj_amount = obj_amount(fd, arg);
	rt->obj_counter = 0;
	rt->objs = (t_object *)malloc(sizeof(t_object) * rt->obj_amount);
	if (!rt->objs)
	{
		ft_putendl_fd("Error: Failed allocating the objects", 2);
		exit(EXIT_FAILURE);
	}
}

t_ambient	parse_ambient(char *line, int i, t_vars *rt)
{
	t_ambient	ambient;

	if (!check_ambient(line, i))
		handle_line_error(rt, "ambient");
	ft_iterspace(line, &i);
	ambient.range = ft_atod(line, i, rt);
	while (line[i] && (line[i] != ' ' && line[i] != '\t'))
		i++;
	ambient.color = parse_colors(line, &i);
	return (ambient);
}

void	parse_line(t_vars *rt, char *line)
{
	int	i;

	i = 0;
	ft_iterspace(line, &i);
	if (line[i] != 10 && line[i] == 'A' && check_identifier(line, i, 1))
		rt->ambient = parse_ambient(line, ++i, rt);
	else if (line[i] != 10 && line[i] == 'C' && check_identifier(line, i, 1))
		rt->camera = parse_camera(line, ++i, rt);
	else if (line[i] != 10 && line[i] == 'L' && check_identifier(line, i, 1))
		rt->light = parse_light(line, ++i, rt);
	else if (line[i] != 10 && !ft_strncmp(&line[i], "sp", 2)
		&& check_identifier(line, i, 0))
		rt->objs[rt->obj_counter++] = parse_sphere(rt, line, i + 2);
	else if (line[i] != 10 && !ft_strncmp(&line[i], "pl", 2)
		&& check_identifier(line, i, 0))
		rt->objs[rt->obj_counter++] = parse_plane(rt, line, i + 2);
	else if (line[i] != 10 && !ft_strncmp(&line[i], "cy", 2)
		&& check_identifier(line, i, 0))
		rt->objs[rt->obj_counter++] = parse_cylinder(rt, line, i + 2);
	else
	{
		if (!(line && line[i] == 10 && !line[i + 1]))
			handle_line_error(rt, "file");
	}
}

void	parse_scene(t_vars *rt, char *arg)
{
	char	*line;
	int		fd;

	fd = open(arg, O_RDONLY);
	if (fd == -1)
	{
		write(2, "Error: File does not exists or you don't ", 41);
		write(2, "have permission\n", 16);
		exit(EXIT_FAILURE);
	}
	init_objects(rt, arg);
	line = get_next_line(fd);
	while (line)
	{
		parse_line(rt, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}
