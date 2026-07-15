/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   platform.c                                         :+:      :+:    :+:   */
/*                                                      +:+ +:+         +:+   */
/*   By: djspright <djspright@student.42tokyo.jp>        +#+  +:+       +#+   */
/*                                                        +#+#+#+#+#+   +#+   */
/*   Created: 2025/06/04 00:00:00 by djspright                   #+#    #+#   */
/*   Updated: 2025/06/04 00:00:00 by djspright            ###   ########.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
** Platform specific teardown. mlx_destroy_display() and freeing the display
** handle only exist on the Linux (X11) MiniLibX. The macOS (Metal) port has
** no such call, so platform_cleanup is a no-op there. Preprocessor branching
** lives at file scope (norm forbids it inside a function body).
*/
#ifdef __linux__

void	platform_cleanup(void *mlx)
{
	mlx_destroy_display(mlx);
	free(mlx);
}

#else

void	platform_cleanup(void *mlx)
{
	(void)mlx;
}

#endif
