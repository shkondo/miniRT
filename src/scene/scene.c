/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                      +:+ +:+         +:+   */
/*   By: shkondo <shkondo@student.42tokyo.jp>            +#+  +:+       +#+   */
/*                                                        +#+#+#+#+#+   +#+   */
/*   Created: 2026/07/06 08:49:21 by shkondo                     #+#    #+#   */
/*   Updated: 2026/07/19 07:44:38 by shkondo              ###   ########.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_scene(t_scene *scene)
{
	scene->ambient.set = 0;
	scene->camera.set = 0;
	scene->light.set = 0;
	scene->objects = NULL;
}

static int	count_objects(t_object *obj)
{
	int	count;

	count = 0;
	while (obj)
	{
		count++;
		obj = obj->next;
	}
	return (count);
}

int	add_object(t_scene *scene, t_object obj)
{
	t_object	*node;

	if (count_objects(scene->objects) >= MAX_OBJECTS)
		return (0);
	node = malloc(sizeof(t_object));
	if (!node)
		return (0);
	*node = obj;
	node->next = scene->objects;
	scene->objects = node;
	return (1);
}

void	free_scene(t_scene *scene)
{
	t_object	*obj;
	t_object	*next;

	obj = scene->objects;
	while (obj)
	{
		next = obj->next;
		free(obj);
		obj = next;
	}
	scene->objects = NULL;
}
