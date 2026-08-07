/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                      +:+ +:+         +:+   */
/*   By: shkondo <shkondo@student.42tokyo.jp>            +#+  +:+       +#+   */
/*                                                        +#+#+#+#+#+   +#+   */
/*   Created: 2026/07/18 21:40:15 by shkondo                     #+#    #+#   */
/*   Updated: 2026/07/20 18:45:16 by shkondo              ###   ########.fr   */
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
