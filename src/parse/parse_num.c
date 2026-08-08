/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkondo <shkondo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 05:20:45 by shkondo           #+#    #+#             */
/*   Updated: 2026/08/07 12:59:20 by shkondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	parse_sign(char **s)
{
	int	sign;

	sign = 1;
	if (**s == '+' || **s == '-')
	{
		if (**s == '-')
			sign = -1;
		(*s)++;
	}
	return (sign);
}

static int	parse_int_part(char **s, double *val, int *digits)
{
	int	digit;

	while (**s >= '0' && **s <= '9')
	{
		digit = **s - '0';
		*val = *val * 10.0 + (double)digit;
		(*digits)++;
		(*s)++;
	}
	return (0);
}

static int	parse_frac_part(char **s, double *val, int *digits)
{
	double	scale;
	int		digit;

	scale = 0.1;
	if (**s != '.')
		return (0);
	(*s)++;
	while (**s >= '0' && **s <= '9')
	{
		digit = **s - '0';
		*val = *val + (double)digit * scale;
		scale = scale * 0.1;
		(*digits)++;
		(*s)++;
	}
	return (0);
}

int	ft_atod(char *s, double *out)
{
	double	val;
	int		sign;
	int		digits;

	if (!s || !*s)
		return (1);
	val = 0.0;
	digits = 0;
	sign = parse_sign(&s);
	parse_int_part(&s, &val, &digits);
	parse_frac_part(&s, &val, &digits);
	if (*s != '\0' || digits == 0)
		return (1);
	if (val > MAX_NUM)
		return (1);
	*out = val * (double)sign;
	return (0);
}

int	parse_double(char *s, double *out)
{
	if (ft_atod(s, out) != 0)
		return (1);
	return (0);
}
