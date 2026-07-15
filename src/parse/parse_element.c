/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_element.c                                    :+:      :+:    :+:   */
/*                                                      +:+ +:+         +:+   */
/*   By: djspright <djspright@student.42tokyo.jp>        +#+  +:+       +#+   */
/*                                                        +#+#+#+#+#+   +#+   */
/*   Created: 2025/06/04 00:00:00 by djspright                   #+#    #+#   */
/*   Updated: 2025/06/04 00:00:00 by djspright            ###   ########.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_ambient(char **tok, t_scene *scene)
{
	if (count_tokens(tok) != 3)
		return (1);
	if (scene->ambient.set)
		return (1);
	if (parse_ratio(tok[1], &scene->ambient.ratio) != 0)
		return (1);
	if (parse_color(tok[2], &scene->ambient.color) != 0)
		return (1);
	scene->ambient.set = 1;
	return (0);
}

int	parse_camera(char **tok, t_scene *scene)
{
	if (count_tokens(tok) != 4)
		return (1);
	if (scene->camera.set)
		return (1);
	if (parse_vec3(tok[1], &scene->camera.pos) != 0)
		return (1);
	if (parse_unit(tok[2], &scene->camera.dir) != 0)
		return (1);
	if (parse_double(tok[3], &scene->camera.fov) != 0)
		return (1);
	if (scene->camera.fov <= 0.0 || scene->camera.fov >= 180.0)
		return (1);
	scene->camera.set = 1;
	return (0);
}

int	parse_light(char **tok, t_scene *scene)
{
	if (count_tokens(tok) != 4)
		return (1);
	if (scene->light.set)
		return (1);
	if (parse_vec3(tok[1], &scene->light.pos) != 0)
		return (1);
	if (parse_ratio(tok[2], &scene->light.ratio) != 0)
		return (1);
	if (parse_color(tok[3], &scene->light.color) != 0)
		return (1);
	scene->light.set = 1;
	return (0);
}
