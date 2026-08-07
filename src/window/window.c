/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                      +:+ +:+         +:+   */
/*   By: shkondo <shkondo@student.42tokyo.jp>            +#+  +:+       +#+   */
/*                                                        +#+#+#+#+#+   +#+   */
/*   Created: 2026/07/16 06:49:29 by shkondo                     #+#    #+#   */
/*   Updated: 2026/07/17 07:03:11 by shkondo              ###   ########.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	init_window(t_app *app)
{
	app->mlx = mlx_init();
	if (!app->mlx)
		return (error_msg("mlx_init failed"));
	app->win = mlx_new_window(app->mlx, WIN_W, WIN_H, WIN_TITLE);
	if (!app->win)
	{
		platform_cleanup(app->mlx);
		return (error_msg("mlx_new_window failed"));
	}
	app->img.ptr = mlx_new_image(app->mlx, WIN_W, WIN_H);
	if (!app->img.ptr)
	{
		mlx_destroy_window(app->mlx, app->win);
		platform_cleanup(app->mlx);
		return (error_msg("mlx_new_image failed"));
	}
	app->img.addr = mlx_get_data_addr(app->img.ptr, &app->img.bpp,
			&app->img.line_len, &app->img.endian);
	return (0);
}

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = (unsigned int)color;
}

int	close_app(t_app *app)
{
	free_scene(&app->scene);
	if (app->img.ptr)
		mlx_destroy_image(app->mlx, app->img.ptr);
	if (app->win)
		mlx_destroy_window(app->mlx, app->win);
	platform_cleanup(app->mlx);
	exit(0);
	return (0);
}
