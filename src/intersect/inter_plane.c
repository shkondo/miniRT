/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_plane.c                                      :+:      :+:    :+:   */
/*                                                      +:+ +:+         +:+   */
/*   By: djspright <djspright@student.42tokyo.jp>        +#+  +:+       +#+   */
/*                                                        +#+#+#+#+#+   +#+   */
/*   Created: 2025/06/04 00:00:00 by djspright                   #+#    #+#   */
/*   Updated: 2025/06/04 00:00:00 by djspright            ###   ########.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	hit_plane(t_object *obj, t_ray ray, t_hit *hit)
{
	double	denom;
	double	t;

	denom = vec_dot(ray.dir, obj->axis);
	if (fabs(denom) < EPSILON)
		return (0);
	t = vec_dot(vec_sub(obj->pos, ray.origin), obj->axis) / denom;
	if (t < EPSILON)
		return (0);
	hit->hit = 1;
	hit->t = t;
	hit->point = vec_at(ray, t);
	hit->normal = face_normal(vec_norm(obj->axis), ray.dir);
	hit->color = obj->color;
	return (1);
}
