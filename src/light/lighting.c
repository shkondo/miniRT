/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                      +:+ +:+         +:+   */
/*   By: djspright <djspright@student.42tokyo.jp>        +#+  +:+       +#+   */
/*                                                        +#+#+#+#+#+   +#+   */
/*   Created: 2025/06/04 00:00:00 by djspright                   #+#    #+#   */
/*   Updated: 2025/06/04 00:00:00 by djspright            ###   ########.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec3	diffuse_term(t_scene *scene, t_hit hit, t_vec3 ldir)
{
	double	ndl;
	double	dist;

	dist = vec_len(ldir);
	ldir = vec_norm(ldir);
	ndl = vec_dot(hit.normal, ldir);
	if (ndl <= 0.0)
		return (vec(0, 0, 0));
	if (in_shadow(scene, hit, ldir, dist))
		return (vec(0, 0, 0));
	return (vec_scale(vec(1, 1, 1), scene->light.ratio * ndl));
}

t_vec3	compute_lighting(t_scene *scene, t_hit hit)
{
	t_vec3	base;
	t_vec3	ambient;
	t_vec3	diffuse;
	t_vec3	light;

	base = color_to_vec(hit.color);
	ambient = vec_scale(color_to_vec(scene->ambient.color),
			scene->ambient.ratio);
	diffuse = vec(0, 0, 0);
	if (scene->light.set)
		diffuse = diffuse_term(scene, hit,
				vec_sub(scene->light.pos, hit.point));
	light = vec_add(ambient, diffuse);
	return (vec_mul(base, light));
}
