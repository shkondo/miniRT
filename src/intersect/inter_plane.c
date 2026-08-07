/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_plane.c                                      :+:      :+:    :+:   */
/*                                                      +:+ +:+         +:+   */
/*   By: shkondo <shkondo@student.42tokyo.jp>            +#+  +:+       +#+   */
/*                                                        +#+#+#+#+#+   +#+   */
/*   Created: 2026/07/03 08:22:11 by shkondo                     #+#    #+#   */
/*   Updated: 2026/07/11 05:13:11 by shkondo              ###   ########.fr   */
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
