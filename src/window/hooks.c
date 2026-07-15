/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                      +:+ +:+         +:+   */
/*   By: djspright <djspright@student.42tokyo.jp>        +#+  +:+       +#+   */
/*                                                        +#+#+#+#+#+   +#+   */
/*   Created: 2025/06/04 00:00:00 by djspright                   #+#    #+#   */
/*   Updated: 2025/06/04 00:00:00 by djspright            ###   ########.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	key_hook(int keycode, t_app *app)
{
	if (keycode == KEY_ESC)
		close_app(app);
	return (0);
}

static int	close_hook(t_app *app)
{
	close_app(app);
	return (0);
}

void	setup_hooks(t_app *app)
{
	mlx_key_hook(app->win, key_hook, app);
	mlx_hook(app->win, EVENT_CLOSE, MASK_NONE, close_hook, app);
}
