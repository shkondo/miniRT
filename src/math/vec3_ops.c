/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkondo <shkondo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 08:05:08 by shkondo           #+#    #+#             */
/*   Updated: 2026/08/08 16:51:35 by shkondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	vec_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3	vec_cross(t_vec3 a, t_vec3 b)
{
	t_vec3	r;

	r.x = a.y * b.z - a.z * b.y;
	r.y = a.z * b.x - a.x * b.z;
	r.z = a.x * b.y - a.y * b.x;
	return (r);
}

double	vec_len2(t_vec3 a)
{
	return (vec_dot(a, a));
}

double	vec_len(t_vec3 a)
{
	return (sqrt(vec_dot(a, a)));
}

t_vec3	vec_norm(t_vec3 a)
{
	double	len;

	len = vec_len(a);
	if (len < EPSILON)
		return (vec(0, 0, 0));
	return (vec_scale(a, 1.0 / len));
}
