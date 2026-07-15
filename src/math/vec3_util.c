/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_util.c                                        :+:      :+:    :+:   */
/*                                                      +:+ +:+         +:+   */
/*   By: djspright <djspright@student.42tokyo.jp>        +#+  +:+       +#+   */
/*                                                        +#+#+#+#+#+   +#+   */
/*   Created: 2025/06/04 00:00:00 by djspright                   #+#    #+#   */
/*   Updated: 2025/06/04 00:00:00 by djspright            ###   ########.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	vec_neg(t_vec3 a)
{
	return (vec(-a.x, -a.y, -a.z));
}

t_vec3	vec_at(t_ray ray, double t)
{
	return (vec_add(ray.origin, vec_scale(ray.dir, t)));
}

double	clampd(double v, double lo, double hi)
{
	if (v < lo)
		return (lo);
	if (v > hi)
		return (hi);
	return (v);
}

t_vec3	face_normal(t_vec3 n, t_vec3 dir)
{
	if (vec_dot(n, dir) > 0.0)
		return (vec_neg(n));
	return (n);
}
