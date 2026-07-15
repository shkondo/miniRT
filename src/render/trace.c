/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                      +:+ +:+         +:+   */
/*   By: djspright <djspright@student.42tokyo.jp>        +#+  +:+       +#+   */
/*                                                        +#+#+#+#+#+   +#+   */
/*   Created: 2025/06/04 00:00:00 by djspright                   #+#    #+#   */
/*   Updated: 2025/06/04 00:00:00 by djspright            ###   ########.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hit	trace_ray(t_scene *scene, t_ray ray)
{
	t_hit		best;
	t_hit		cur;
	t_object	*obj;

	best.hit = 0;
	best.t = INF;
	obj = scene->objects;
	while (obj)
	{
		if (hit_object(obj, ray, &cur) && cur.t < best.t)
			best = cur;
		obj = obj->next;
	}
	return (best);
}

int	hit_object(t_object *obj, t_ray ray, t_hit *hit)
{
	if (obj->type == OBJ_SPHERE)
		return (hit_sphere(obj, ray, hit));
	if (obj->type == OBJ_PLANE)
		return (hit_plane(obj, ray, hit));
	if (obj->type == OBJ_CYLINDER)
		return (hit_cylinder(obj, ray, hit));
	return (0);
}
