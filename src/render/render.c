/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                      +:+ +:+         +:+   */
/*   By: djspright <djspright@student.42tokyo.jp>        +#+  +:+       +#+   */
/*                                                        +#+#+#+#+#+   +#+   */
/*   Created: 2025/06/04 00:00:00 by djspright                   #+#    #+#   */
/*   Updated: 2025/06/04 00:00:00 by djspright            ###   ########.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	render_scene(t_app *app)
{
	int		x;
	int		y;
	t_ray	ray;

	setup_camera(&app->scene.camera);
	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			ray = make_ray(&app->scene.camera, x, y);
			put_pixel(&app->img, x, y, ray_color(&app->scene, ray));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(app->mlx, app->win, app->img.ptr, 0, 0);
}

int	ray_color(t_scene *scene, t_ray ray)
{
	t_hit	hit;
	t_vec3	col;

	hit = trace_ray(scene, ray);
	if (!hit.hit)
		return (0x000000);
	col = compute_lighting(scene, hit);
	return (vec_to_rgb(col));
}
