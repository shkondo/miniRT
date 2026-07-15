/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                      +:+ +:+         +:+   */
/*   By: djspright <djspright@student.42tokyo.jp>        +#+  +:+       +#+   */
/*                                                        +#+#+#+#+#+   +#+   */
/*   Created: 2025/06/04 00:00:00 by djspright                   #+#    #+#   */
/*   Updated: 2025/06/04 00:00:00 by djspright            ###   ########.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define READ_CHUNK 4096

static char	*join_free(char *dst, char *src, size_t len, size_t add)
{
	char	*res;
	size_t	i;

	res = malloc(sizeof(char) * (len + add + 1));
	if (!res)
		return (free(dst), NULL);
	i = 0;
	while (i < len)
	{
		res[i] = dst[i];
		i++;
	}
	while (i < len + add)
	{
		res[i] = src[i - len];
		i++;
	}
	res[len + add] = '\0';
	free(dst);
	return (res);
}

char	*read_file(int fd)
{
	char	buf[READ_CHUNK];
	char	*data;
	size_t	len;
	ssize_t	r;

	data = malloc(sizeof(char) * 1);
	if (!data)
		return (NULL);
	data[0] = '\0';
	len = 0;
	r = read(fd, buf, READ_CHUNK);
	while (r > 0)
	{
		data = join_free(data, buf, len, (size_t)r);
		if (!data)
			return (NULL);
		len += (size_t)r;
		r = read(fd, buf, READ_CHUNK);
	}
	if (r < 0)
		return (free(data), NULL);
	return (data);
}
