/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_cyl_caps.c                                   :+:      :+:    :+:   */
/*                                                      +:+ +:+         +:+   */
/*   By: djspright <djspright@student.42tokyo.jp>        +#+  +:+       +#+   */
/*                                                        +#+#+#+#+#+   +#+   */
/*   Created: 2025/06/04 00:00:00 by djspright                   #+#    #+#   */
/*   Updated: 2025/06/04 00:00:00 by djspright            ###   ########.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_cap	make_cap(t_object *obj, double sign)
{
	t_cap	cap;

	cap.center = vec_add(obj->pos,
			vec_scale(obj->axis, sign * obj->height / 2.0));
	cap.normal = vec_scale(obj->axis, sign);
	cap.radius = obj->radius;
	return (cap);
}

static int	hit_one_cap(t_ray ray, t_cap cap, t_hit *hit)
{
	double	denom;
	double	t;
	t_vec3	p;

	denom = vec_dot(ray.dir, cap.normal);
	if (fabs(denom) < EPSILON)
		return (0);
	t = vec_dot(vec_sub(cap.center, ray.origin), cap.normal) / denom;
	if (t < EPSILON)
		return (0);
	p = vec_at(ray, t);
	if (vec_len2(vec_sub(p, cap.center)) > cap.radius * cap.radius)
		return (0);
	hit->hit = 1;
	hit->t = t;
	hit->point = p;
	hit->normal = face_normal(cap.normal, ray.dir);
	return (1);
}

int	hit_cyl_caps(t_object *obj, t_ray ray, t_hit *hit)
{
	t_hit	cur;
	int		found;

	found = 0;
	hit->t = INF;
	if (hit_one_cap(ray, make_cap(obj, 1.0), &cur) && cur.t < hit->t)
	{
		*hit = cur;
		found = 1;
	}
	if (hit_one_cap(ray, make_cap(obj, -1.0), &cur) && cur.t < hit->t)
	{
		*hit = cur;
		found = 1;
	}
	if (found)
		hit->color = obj->color;
	return (found);
}
