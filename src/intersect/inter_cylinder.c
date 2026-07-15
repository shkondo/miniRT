/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_cylinder.c                                   :+:      :+:    :+:   */
/*                                                      +:+ +:+         +:+   */
/*   By: djspright <djspright@student.42tokyo.jp>        +#+  +:+       +#+   */
/*                                                        +#+#+#+#+#+   +#+   */
/*   Created: 2025/06/04 00:00:00 by djspright                   #+#    #+#   */
/*   Updated: 2025/06/04 00:00:00 by djspright            ###   ########.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	cyl_quad(t_object *obj, t_ray ray, t_quad *q)
{
	t_vec3	x;
	double	dda;
	double	xa;

	x = vec_sub(ray.origin, obj->pos);
	dda = vec_dot(ray.dir, obj->axis);
	xa = vec_dot(x, obj->axis);
	q->a = vec_len2(ray.dir) - dda * dda;
	q->b = 2.0 * (vec_dot(ray.dir, x) - dda * xa);
	q->c = vec_len2(x) - xa * xa - obj->radius * obj->radius;
}

static int	cyl_in_band(t_object *obj, t_ray ray, double t, t_hit *hit)
{
	t_vec3	p;
	double	m;

	if (t <= EPSILON)
		return (0);
	p = vec_at(ray, t);
	m = vec_dot(vec_sub(p, obj->pos), obj->axis);
	if (fabs(m) > obj->height / 2.0)
		return (0);
	hit->hit = 1;
	hit->t = t;
	hit->point = p;
	hit->normal = face_normal(vec_norm(vec_sub(vec_sub(p, obj->pos),
					vec_scale(obj->axis, m))), ray.dir);
	hit->color = obj->color;
	return (1);
}

int	hit_cyl_body(t_object *obj, t_ray ray, t_hit *hit)
{
	t_quad	q;
	double	t0;
	double	t1;

	cyl_quad(obj, ray, &q);
	if (!solve_quad2(&q, &t0, &t1))
		return (0);
	if (cyl_in_band(obj, ray, t0, hit))
		return (1);
	if (cyl_in_band(obj, ray, t1, hit))
		return (1);
	return (0);
}

int	hit_cylinder(t_object *obj, t_ray ray, t_hit *hit)
{
	t_hit	body;
	t_hit	caps;
	int		hb;
	int		hc;

	body.hit = 0;
	caps.hit = 0;
	hb = hit_cyl_body(obj, ray, &body);
	hc = hit_cyl_caps(obj, ray, &caps);
	if (hb && (!hc || body.t < caps.t))
	{
		*hit = body;
		return (1);
	}
	if (hc)
	{
		*hit = caps;
		return (1);
	}
	return (0);
}
