/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkayadib <zkayadib@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:20:04 by zkayadib          #+#    #+#             */
/*   Updated: 2024/11/13 03:50:34 by zkayadib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_totalwords(const char *s, int c)
{
	int	i;
	int	wordcount;

	i = 0;
	wordcount = 0;
	while (s[i])
	{
		if (s[i] == c)
			if (i > 0 && s[i - 1] != c)
				wordcount++;
		if (s[i + 1] == '\0' && s[i] != c)
			wordcount++;
		while (s[i] == c && (s[i + 1] == c))
			i++;
		i++;
	}
	return (wordcount);
}

static void	*ft_free(char **splt)
{
	int	i;

	i = 0;
	while (splt[i] != NULL)
	{
		free(splt[i]);
		i ++;
	}
	free(splt);
	return (NULL);
}

static void	*assign(const char *s, int c, int totalwords, char **splt)
{
	int	wordcount;
	int	i;
	int	fixed;

	i = 0;
	fixed = i;
	wordcount = 0;
	while (wordcount < totalwords)
	{
		while (s[i] == c)
		{
			i++;
			fixed = i;
		}
		while (s[i] && s[i] != c)
			i++;
		splt[wordcount] = ft_substr(s + fixed, 0, (&s[i] - &s[fixed]));
		if (splt[wordcount] == NULL)
			return (ft_free(splt));
		wordcount++;
		fixed = i + 1;
	}
	return (splt);
}

char	**ft_split(char const *s, char c)
{
	int		totalwords;
	char	**splt;

	totalwords = ft_totalwords(s, c);
	splt = malloc(sizeof(char *) * (totalwords + 1));
	if (!splt)
		return (NULL);
	splt[totalwords] = NULL;
	assign(s, c, totalwords, splt);
	return (splt);
}
