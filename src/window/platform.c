/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   platform.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkondo <shkondo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 05:29:16 by shkondo           #+#    #+#             */
/*   Updated: 2026/08/09 15:38:49 by shkondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
