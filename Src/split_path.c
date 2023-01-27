/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeulema <jmeulema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 15:31:22 by mlazzare          #+#    #+#             */
/*   Updated: 2023/01/26 15:33:13 by jmeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/pipex.h"

static char	**free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		free(tab);
	if (tab)
		free(tab);
	return (0);
}

static int	nb_words(const char *s, char c)
{
	int	i;
	int	count;

	if (!s || !s[0])
		return (0);
	i = -1;
	count = 0;
	while (s[++i])
	{
		if ((s[i] != c && s[i + 1] == c) && (s[i] != c && s[i + 1] == '\0'))
			count++;
	}
	return (count);
}

static int	words_len(const char *s, char c, int i)
{
	int	len;

	if (!s || !s[0])
		return (0);
	i = -1;
	len = 0;
	while (s && s[i] && s[i] == c)
		i++;
	while (s && s[i] && s[i++] != c)
		len++;
	return (len);
}

static char	**fill_tab(int words, const char *s, char c, char **tab)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (k < words)
	{
		j = 0;
		tab[k] = (char *)malloc(sizeof(char) * (words_len(s, c, i) + 2));
		if (!tab)
			return (free_tab(tab));
		while (s && s[i] && s[i] == c)
			i++;
		while (s && s[i] && s[i] != c)
			tab[k][j++] = s[i++];
		tab[k][j++] = '/';
		tab[k][j] = '\0';
		k++;
	}
	tab[k] = 0;
	return (tab);
}

char	**ft_splitpath(char *s, char c)
{
	char	**tab;
	int		words;

	if (!s || !s[0])
		return (NULL);
	words = nb_words(s, c);
	tab = (char **)malloc(sizeof(char *) * (words + 1));
	if (!tab)
		return (NULL);
	tab = fill_tab(words, s, c, tab);
	return (tab);
}
