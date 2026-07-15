/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                      +:+ +:+         +:+   */
/*   By: djspright <djspright@student.42tokyo.jp>        +#+  +:+       +#+   */
/*                                                        +#+#+#+#+#+   +#+   */
/*   Created: 2025/06/04 00:00:00 by djspright                   #+#    #+#   */
/*   Updated: 2025/06/04 00:00:00 by djspright            ###   ########.fr   */
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

int	add_object(t_scene *scene, t_object obj)
{
	t_object	*node;

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
