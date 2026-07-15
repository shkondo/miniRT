/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                      +:+ +:+         +:+   */
/*   By: djspright <djspright@student.42tokyo.jp>        +#+  +:+       +#+   */
/*                                                        +#+#+#+#+#+   +#+   */
/*   Created: 2025/06/04 00:00:00 by djspright                   #+#    #+#   */
/*   Updated: 2025/06/04 00:00:00 by djspright            ###   ########.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	color_new(int r, int g, int b)
{
	t_color	c;

	c.r = r;
	c.g = g;
	c.b = b;
	return (c);
}

t_vec3	color_to_vec(t_color c)
{
	return (vec(c.r / 255.0, c.g / 255.0, c.b / 255.0));
}

int	vec_to_rgb(t_vec3 c)
{
	int	r;
	int	g;
	int	b;

	r = (int)(clampd(c.x, 0.0, 1.0) * 255.0 + 0.5);
	g = (int)(clampd(c.y, 0.0, 1.0) * 255.0 + 0.5);
	b = (int)(clampd(c.z, 0.0, 1.0) * 255.0 + 0.5);
	return ((r << 16) | (g << 8) | b);
}
