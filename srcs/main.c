/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvallhon <mvallhon@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:59:07 by mvallhon          #+#    #+#             */
/*   Updated: 2024/06/14 18:31:58 by mvallhon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/MiniRT.h"
#include "../includes/get_next_line.h"

static void	is_rtfile(char *file, int argc)
{
	size_t	len;

	if (argc == 1)
		return ;
	len = ft_strlen(file);
	if (len <= 3 || file[--len] != 't'
		|| file[len - 1] != 'r' || file[len - 2] != '.')
	{
		ft_putendl_fd("File hasn't a \".rt\" format", 2);
		exit(EXIT_FAILURE);
	}
}

static void	iterate_utils(t_vars *rt, t_iter *data)
{
	rt->camera.orientation = normalize(rt->camera.orientation);
	data->radiant_fov = M_PI * rt->camera.fov / 180;
	data->h = tanf(data->radiant_fov / 2);
	data->w = rt->a_ratio * data->h;
	data->i = -1;
	data->upguide.x = 0;
	data->upguide.y = 1;
	data->upguide.z = 0;
	data->right = normalize(cross(rt->camera.orientation, data->upguide));
	data->up = cross(data->right, rt->camera.orientation);
	data->ray.og.x = rt->camera.coords.x;
	data->ray.og.y = rt->camera.coords.y;
	data->ray.og.z = rt->camera.coords.z;
}

static void	iterate_pixels(t_vars *rt)
{
	t_iter	data;

	iterate_utils(rt, &data);
	while (++data.i < HEIGHT)
	{
		data.y = -2.0f * data.i / HEIGHT + 1.0f;
		data.j = -1;
		while (++data.j <= WIDTH)
		{
			data.x = 2.0f * data.j / WIDTH - 1.0f;
			data.ray.max_t = MAX_T;
			data.ray.colision = NULL;
			data.ray.dir = normalize(addition(rt->camera.orientation, \
			addition(multiplication(data.h * data.y, data.up), \
			multiplication(data.w * data.x, data.right))));
			check_intersections(rt, &data.ray);
			if (data.ray.colision != NULL)
			{
				colorize(rt, &data.ray);
				my_mlx_pixel_put(&rt->img, data.j, data.i, create_trgb(0, \
					data.ray.rgb.r, data.ray.rgb.g, data.ray.rgb.b));
			}
		}
	}
}

int	main(int argc, char **argv)
{
	t_vars	rt;

	if (argc > 2)
	{
		write(2, "Error: Invalid number of arguments\n", 35);
		return (1);
	}
	is_rtfile(argv[1], argc);
	rt.objs = NULL;
	if (argc == 2)
		parse_scene(&rt, argv[1]);
	rt.mlx.mlx_ptr = mlx_init();
	rt.mlx.win_ptr = mlx_new_window(rt.mlx.mlx_ptr, WIDTH, HEIGHT, "MiniRT");
	rt.img.img_ptr = mlx_new_image(rt.mlx.mlx_ptr, WIDTH, HEIGHT);
	rt.img.addr = mlx_get_data_addr(rt.img.img_ptr,
			&rt.img.bpp, &rt.img.line_len, &rt.img.endian);
	rt.a_ratio = ((float)WIDTH / (float)HEIGHT);
	if (argc == 2)
		iterate_pixels(&rt);
	mlx_put_image_to_window(rt.mlx.mlx_ptr,
		rt.mlx.win_ptr, rt.img.img_ptr, 0, 0);
	mlx_key_hook(rt.mlx.win_ptr, key_hook, &rt);
	mlx_hook(rt.mlx.win_ptr, 17, 0, close_win_mouse, &rt);
	mlx_loop(rt.mlx.mlx_ptr);
	return (0);
}
