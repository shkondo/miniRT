/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                      +:+ +:+         +:+   */
/*   By: djspright <djspright@student.42tokyo.jp>        +#+  +:+       +#+   */
/*                                                        +#+#+#+#+#+   +#+   */
/*   Created: 2025/06/04 00:00:00 by djspright                   #+#    #+#   */
/*   Updated: 2025/06/04 00:00:00 by djspright            ###   ########.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	valid_ext(char *path)
{
	size_t	len;

	len = ft_strlen(path);
	if (len < 4)
		return (0);
	if (ft_strncmp(path + len - 3, ".rt", 3) != 0)
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_app	app;

	if (argc != 2)
		return (error_msg("usage: ./miniRT <scene.rt>"));
	if (!valid_ext(argv[1]))
		return (error_msg("scene file must have a .rt extension"));
	init_scene(&app.scene);
	if (parse_scene(argv[1], &app.scene))
	{
		free_scene(&app.scene);
		return (1);
	}
	if (init_window(&app))
	{
		free_scene(&app.scene);
		return (1);
	}
	render_scene(&app);
	setup_hooks(&app);
	mlx_loop(app.mlx);
	return (0);
}
