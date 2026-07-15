/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_atom.c                                       :+:      :+:    :+:   */
/*                                                      +:+ +:+         +:+   */
/*   By: djspright <djspright@student.42tokyo.jp>        +#+  +:+       +#+   */
/*                                                        +#+#+#+#+#+   +#+   */
/*   Created: 2025/06/04 00:00:00 by djspright                   #+#    #+#   */
/*   Updated: 2025/06/04 00:00:00 by djspright            ###   ########.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_vec3(char *s, t_vec3 *out)
{
	char	**fields;
	int		ok;

	if (count_char(s, ',') != 2)
		return (1);
	fields = split_set(s, ",");
	if (!fields)
		return (1);
	ok = 0;
	if (count_tokens(fields) != 3)
		ok = 1;
	if (ok == 0 && parse_double(fields[0], &out->x) != 0)
		ok = 1;
	if (ok == 0 && parse_double(fields[1], &out->y) != 0)
		ok = 1;
	if (ok == 0 && parse_double(fields[2], &out->z) != 0)
		ok = 1;
	free_split(fields);
	return (ok);
}

static int	parse_channel(char *s, int *out)
{
	double	val;

	if (parse_double(s, &val) != 0)
		return (1);
	if (val < 0.0 || val > 255.0)
		return (1);
	if (val != (double)(int)val)
		return (1);
	*out = (int)val;
	return (0);
}

int	parse_color(char *s, t_color *out)
{
	char	**fields;
	int		ok;

	if (count_char(s, ',') != 2)
		return (1);
	fields = split_set(s, ",");
	if (!fields)
		return (1);
	ok = 0;
	if (count_tokens(fields) != 3)
		ok = 1;
	if (ok == 0 && parse_channel(fields[0], &out->r) != 0)
		ok = 1;
	if (ok == 0 && parse_channel(fields[1], &out->g) != 0)
		ok = 1;
	if (ok == 0 && parse_channel(fields[2], &out->b) != 0)
		ok = 1;
	free_split(fields);
	return (ok);
}

int	parse_ratio(char *s, double *out)
{
	if (parse_double(s, out) != 0)
		return (1);
	if (*out < 0.0 || *out > 1.0)
		return (1);
	return (0);
}

int	parse_unit(char *s, t_vec3 *out)
{
	t_vec3	v;

	if (parse_vec3(s, &v) != 0)
		return (1);
	if (v.x < -1.0 || v.x > 1.0 || v.y < -1.0 || v.y > 1.0)
		return (1);
	if (v.z < -1.0 || v.z > 1.0)
		return (1);
	if (v.x == 0.0 && v.y == 0.0 && v.z == 0.0)
		return (1);
	*out = vec_norm(v);
	return (0);
}
