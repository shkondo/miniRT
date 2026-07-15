/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                      +:+ +:+         +:+   */
/*   By: djspright <djspright@student.42tokyo.jp>        +#+  +:+       +#+   */
/*                                                        +#+#+#+#+#+   +#+   */
/*   Created: 2025/06/04 00:00:00 by djspright                   #+#    #+#   */
/*   Updated: 2025/06/04 00:00:00 by djspright            ###   ########.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	in_shadow(t_scene *scene, t_hit hit, t_vec3 ldir, double ldist)
{
	t_ray		ray;
	t_hit		sh;
	t_object	*obj;

	ray.origin = vec_add(hit.point, vec_scale(hit.normal, SHADOW_BIAS));
	ray.dir = ldir;
	obj = scene->objects;
	while (obj)
	{
		if (hit_object(obj, ray, &sh) && sh.t < ldist - SHADOW_BIAS)
			return (1);
		obj = obj->next;
	}
	return (0);
}
