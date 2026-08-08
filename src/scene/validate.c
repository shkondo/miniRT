/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkondo <shkondo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 21:47:49 by shkondo           #+#    #+#             */
/*   Updated: 2026/08/08 16:52:03 by shkondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	validate_scene(t_scene *scene)
{
	if (scene->ambient.set != 1)
		return (1);
	if (scene->camera.set != 1)
		return (1);
	if (scene->light.set != 1)
		return (1);
	return (0);
}
