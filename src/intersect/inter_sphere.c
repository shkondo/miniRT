/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_sphere.c                                     :+:      :+:    :+:   */
/*                                                      +:+ +:+         +:+   */
/*   By: djspright <djspright@student.42tokyo.jp>        +#+  +:+       +#+   */
/*                                                        +#+#+#+#+#+   +#+   */
/*   Created: 2025/06/04 00:00:00 by djspright                   #+#    #+#   */
/*   Updated: 2025/06/04 00:00:00 by djspright            ###   ########.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	solve_quad2(t_quad *q, double *t0, double *t1)
{
	double	sq;

	if (fabs(q->a) < EPSILON)
		return (0);
	q->disc = q->b * q->b - 4.0 * q->a * q->c;
	if (q->disc < 0.0)
		return (0);
	sq = sqrt(q->disc);
	*t0 = (-q->b - sq) / (2.0 * q->a);
	*t1 = (-q->b + sq) / (2.0 * q->a);
	return (1);
}

int	solve_quad(t_quad *q, double *t)
{
	double	sq;
	double	t0;
	double	t1;

	if (fabs(q->a) < EPSILON)
		return (0);
	q->disc = q->b * q->b - 4.0 * q->a * q->c;
	if (q->disc < 0.0)
		return (0);
	sq = sqrt(q->disc);
	t0 = (-q->b - sq) / (2.0 * q->a);
	t1 = (-q->b + sq) / (2.0 * q->a);
	if (t0 > EPSILON)
	{
		*t = t0;
		return (1);
	}
	if (t1 > EPSILON)
	{
		*t = t1;
		return (1);
	}
	return (0);
}

int	hit_sphere(t_object *obj, t_ray ray, t_hit *hit)
{
	t_quad	q;
	t_vec3	oc;
	double	t;

	oc = vec_sub(ray.origin, obj->pos);
	q.a = vec_dot(ray.dir, ray.dir);
	q.b = 2.0 * vec_dot(oc, ray.dir);
	q.c = vec_dot(oc, oc) - obj->radius * obj->radius;
	if (!solve_quad(&q, &t))
		return (0);
	hit->hit = 1;
	hit->t = t;
	hit->point = vec_at(ray, t);
	hit->normal = face_normal(vec_norm(vec_sub(hit->point, obj->pos)),
			ray.dir);
	hit->color = obj->color;
	return (1);
}
