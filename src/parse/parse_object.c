/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object.c                                     :+:      :+:    :+:   */
/*                                                      +:+ +:+         +:+   */
/*   By: djspright <djspright@student.42tokyo.jp>        +#+  +:+       +#+   */
/*                                                        +#+#+#+#+#+   +#+   */
/*   Created: 2025/06/04 00:00:00 by djspright                   #+#    #+#   */
/*   Updated: 2025/06/04 00:00:00 by djspright            ###   ########.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	init_obj(t_object *obj, t_obj_type type)
{
	obj->type = type;
	obj->pos = vec(0.0, 0.0, 0.0);
	obj->axis = vec(0.0, 0.0, 1.0);
	obj->radius = 0.0;
	obj->height = 0.0;
	obj->color = color_new(0, 0, 0);
	obj->next = NULL;
}

int	parse_sphere(char **tok, t_scene *scene)
{
	t_object	obj;
	double		diameter;

	if (count_tokens(tok) != 4)
		return (1);
	init_obj(&obj, OBJ_SPHERE);
	if (parse_vec3(tok[1], &obj.pos) != 0)
		return (1);
	if (parse_double(tok[2], &diameter) != 0 || diameter <= 0.0)
		return (1);
	obj.radius = diameter / 2.0;
	if (parse_color(tok[3], &obj.color) != 0)
		return (1);
	if (add_object(scene, obj) == 0)
		return (1);
	return (0);
}

int	parse_plane(char **tok, t_scene *scene)
{
	t_object	obj;

	if (count_tokens(tok) != 4)
		return (1);
	init_obj(&obj, OBJ_PLANE);
	if (parse_vec3(tok[1], &obj.pos) != 0)
		return (1);
	if (parse_unit(tok[2], &obj.axis) != 0)
		return (1);
	if (parse_color(tok[3], &obj.color) != 0)
		return (1);
	if (add_object(scene, obj) == 0)
		return (1);
	return (0);
}

int	parse_cylinder(char **tok, t_scene *scene)
{
	t_object	obj;
	double		diameter;

	if (count_tokens(tok) != 6)
		return (1);
	init_obj(&obj, OBJ_CYLINDER);
	if (parse_vec3(tok[1], &obj.pos) != 0)
		return (1);
	if (parse_unit(tok[2], &obj.axis) != 0)
		return (1);
	if (parse_double(tok[3], &diameter) != 0 || diameter <= 0.0)
		return (1);
	obj.radius = diameter / 2.0;
	if (parse_double(tok[4], &obj.height) != 0 || obj.height <= 0.0)
		return (1);
	if (parse_color(tok[5], &obj.color) != 0)
		return (1);
	if (add_object(scene, obj) == 0)
		return (1);
	return (0);
}
