/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_basic.c                                       :+:      :+:    :+:   */
/*                                                      +:+ +:+         +:+   */
/*   By: djspright <djspright@student.42tokyo.jp>        +#+  +:+       +#+   */
/*                                                        +#+#+#+#+#+   +#+   */
/*   Created: 2025/06/04 00:00:00 by djspright                   #+#    #+#   */
/*   Updated: 2025/06/04 00:00:00 by djspright            ###   ########.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	vec(double x, double y, double z)
{
	t_vec3	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_vec3	vec_add(t_vec3 a, t_vec3 b)
{
	return (vec(a.x + b.x, a.y + b.y, a.z + b.z));
}

t_vec3	vec_sub(t_vec3 a, t_vec3 b)
{
	return (vec(a.x - b.x, a.y - b.y, a.z - b.z));
}

t_vec3	vec_scale(t_vec3 a, double s)
{
	return (vec(a.x * s, a.y * s, a.z * s));
}

t_vec3	vec_mul(t_vec3 a, t_vec3 b)
{
	return (vec(a.x * b.x, a.y * b.y, a.z * b.z));
}
