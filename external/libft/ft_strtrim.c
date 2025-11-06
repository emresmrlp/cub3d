/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkayadib <zkayadib@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 21:53:42 by zkayadib          #+#    #+#             */
/*   Updated: 2024/11/13 04:08:39 by zkayadib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	char	*c;

	i = 0;
	j = ft_strlen(s1) -1;
	if (!s1)
		return (NULL);
	if (!set)
		return (c = ft_strdup(s1));
	while (s1[i] && ft_strchr(set, s1[i]) != NULL)
	{
		i ++;
	}
	while (j >= i && ft_strchr(set, s1[j]) != NULL)
	{
		j --;
	}
	c = ft_substr(s1 + i, 0, (&s1[j] - &s1[i]) + 1);
	return (c);
}
