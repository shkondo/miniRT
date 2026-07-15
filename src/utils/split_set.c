/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_set.c                                        :+:      :+:    :+:   */
/*                                                      +:+ +:+         +:+   */
/*   By: djspright <djspright@student.42tokyo.jp>        +#+  +:+       +#+   */
/*                                                        +#+#+#+#+#+   +#+   */
/*   Created: 2025/06/04 00:00:00 by djspright                   #+#    #+#   */
/*   Updated: 2025/06/04 00:00:00 by djspright            ###   ########.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	is_set(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static char	*dup_word(char *s, int len)
{
	char	*word;
	int		i;

	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[len] = '\0';
	return (word);
}

void	free_split(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	count_tokens(char **tab)
{
	int	i;

	if (!tab)
		return (0);
	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char	**split_set(char *s, char *set)
{
	char	**tab;
	int		i;
	int		len;

	tab = malloc(sizeof(char *) * (ft_strlen(s) + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && is_set(*s, set))
			s++;
		len = 0;
		while (s[len] && !is_set(s[len], set))
			len++;
		if (len == 0)
			break ;
		tab[i] = dup_word(s, len);
		if (!tab[i])
			return (free_split(tab), NULL);
		i++;
		s += len;
	}
	tab[i] = NULL;
	return (tab);
}
