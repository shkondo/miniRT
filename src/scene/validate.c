/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                      +:+ +:+         +:+   */
/*   By: djspright <djspright@student.42tokyo.jp>        +#+  +:+       +#+   */
/*                                                        +#+#+#+#+#+   +#+   */
/*   Created: 2025/06/04 00:00:00 by djspright                   #+#    #+#   */
/*   Updated: 2025/06/04 00:00:00 by djspright            ###   ########.fr   */
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
