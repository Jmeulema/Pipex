/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeulema <jmeulema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 17:40:40 by mlazzare          #+#    #+#             */
/*   Updated: 2023/02/10 11:30:16 by jmeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/pipex.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		result;

	i = 0;
	result = 0;
	while (i < n)
	{
		result = (unsigned char)s1[i] - (unsigned char)s2[i];
		if (result != 0 || !s1[i] || !s2[i])
			return (result);
		i++;
	}
	return (result);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	if (!s)
		return (NULL);
	if (len < ft_strlen(s))
		i = len;
	else
		i = ft_strlen(s);
	str = malloc(sizeof(char) * i + 1);
	if (!str)
		return (NULL);
	i = 0;
	if (start > (unsigned int)ft_strlen(s))
	{
		str[0] = '\0';
		return (str);
	}
	while ((len - i) > 0 && s[start + i])
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	ft_putstr(char *s, char *t)
{
	if (!s)
		return (2);
	if (t)
	{
		write(2, "file: ", 7);
		write(2, t, ft_strlen(t));
		write(2, ": ", 2);
	}
	while (*s)
	{
		write(2, &(*s), 1);
		s++;
	}
	write(2, "\n", 1);
	return (2);
}

char	*ft_strjoin(char *s1, const char *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}
