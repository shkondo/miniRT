/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                      +:+ +:+         +:+   */
/*   By: shkondo <shkondo@student.42tokyo.jp>            +#+  +:+       +#+   */
/*                                                        +#+#+#+#+#+   +#+   */
/*   Created: 2026/06/05 18:04:40 by shkondo                     #+#    #+#   */
/*   Updated: 2026/06/10 07:50:34 by shkondo              ###   ########.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	error_msg(char *msg)
{
	write(2, "Error\n", 6);
	if (msg)
	{
		write(2, msg, ft_strlen(msg));
		write(2, "\n", 1);
	}
	return (1);
}

void	error_exit(t_app *app, char *msg)
{
	error_msg(msg);
	if (app)
		free_scene(&app->scene);
	exit(1);
}
