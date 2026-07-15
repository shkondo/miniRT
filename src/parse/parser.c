/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                      +:+ +:+         +:+   */
/*   By: djspright <djspright@student.42tokyo.jp>        +#+  +:+       +#+   */
/*                                                        +#+#+#+#+#+   +#+   */
/*   Created: 2025/06/04 00:00:00 by djspright                   #+#    #+#   */
/*   Updated: 2025/06/04 00:00:00 by djspright            ###   ########.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	id_eq(char *tok, char *id)
{
	size_t	len;

	len = ft_strlen(id);
	if (ft_strlen(tok) != len)
		return (0);
	if (ft_strncmp(tok, id, len) != 0)
		return (0);
	return (1);
}

static int	dispatch(char **tok, t_scene *scene)
{
	if (id_eq(tok[0], "A"))
		return (parse_ambient(tok, scene));
	if (id_eq(tok[0], "C"))
		return (parse_camera(tok, scene));
	if (id_eq(tok[0], "L"))
		return (parse_light(tok, scene));
	if (id_eq(tok[0], "sp"))
		return (parse_sphere(tok, scene));
	if (id_eq(tok[0], "pl"))
		return (parse_plane(tok, scene));
	if (id_eq(tok[0], "cy"))
		return (parse_cylinder(tok, scene));
	return (1);
}

int	parse_line(char *line, t_scene *scene)
{
	char	**tok;
	int		ret;

	tok = split_set(line, " \t\r");
	if (!tok)
		return (error_msg("memory allocation failed"));
	if (count_tokens(tok) == 0)
		return (free_split(tok), 0);
	ret = dispatch(tok, scene);
	free_split(tok);
	if (ret != 0)
		return (error_msg("invalid element definition"));
	return (0);
}

static int	parse_content(char *content, t_scene *scene)
{
	char	**lines;
	int		i;
	int		ret;

	lines = split_set(content, "\n");
	if (!lines)
		return (1);
	i = 0;
	ret = 0;
	while (lines[i] && ret == 0)
	{
		ret = parse_line(lines[i], scene);
		i++;
	}
	free_split(lines);
	return (ret);
}

int	parse_scene(char *path, t_scene *scene)
{
	int		fd;
	char	*content;
	int		ret;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (error_msg("cannot open scene file"));
	content = read_file(fd);
	close(fd);
	if (!content)
		return (error_msg("cannot read scene file"));
	ret = parse_content(content, scene);
	free(content);
	if (ret != 0)
		return (1);
	if (validate_scene(scene) != 0)
		return (error_msg("incomplete scene"));
	return (0);
}
