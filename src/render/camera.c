/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                      +:+ +:+         +:+   */
/*   By: djspright <djspright@student.42tokyo.jp>        +#+  +:+       +#+   */
/*                                                        +#+#+#+#+#+   +#+   */
/*   Created: 2025/06/04 00:00:00 by djspright                   #+#    #+#   */
/*   Updated: 2025/06/04 00:00:00 by djspright            ###   ########.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	setup_camera(t_camera *cam)
{
	t_vec3	world_up;

	cam->dir = vec_norm(cam->dir);
	world_up = vec(0, 1, 0);
	if (fabs(cam->dir.y) > 0.999)
		world_up = vec(0, 0, 1);
	cam->right = vec_norm(vec_cross(world_up, cam->dir));
	cam->up = vec_cross(cam->dir, cam->right);
	cam->half_w = tan(cam->fov * PI / 360.0);
	cam->half_h = cam->half_w * (double)WIN_H / (double)WIN_W;
}

t_ray	make_ray(t_camera *cam, double px, double py)
{
	t_ray	ray;
	double	sx;
	double	sy;
	t_vec3	dir;

	sx = (2.0 * (px + 0.5) / (double)WIN_W - 1.0) * cam->half_w;
	sy = (1.0 - 2.0 * (py + 0.5) / (double)WIN_H) * cam->half_h;
	dir = vec_add(cam->dir, vec_add(vec_scale(cam->right, sx),
				vec_scale(cam->up, sy)));
	ray.origin = cam->pos;
	ray.dir = vec_norm(dir);
	return (ray);
}
