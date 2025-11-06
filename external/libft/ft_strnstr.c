/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkayadib <zkayadib@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:58:24 by zkayadib          #+#    #+#             */
/*   Updated: 2024/11/05 10:13:13 by zkayadib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*s1;
	char	*s2;
	size_t	i;
	size_t	j;

	s1 = (char *)(haystack);
	s2 = (char *)(needle);
	i = 0;
	j = 0;
	if (s2[j] == '\0')
		return (s1);
	while (s1[i] && s2[j] && i < len)
	{
		j = 0;
		while ((s1[i + j] == s2[j] || s2[j] == '\0') && i + j <= len)
		{
			if (s2[j] == '\0' && ft_strlen(s2) == j)
				return (&s1[i]);
			j ++;
		}
		i ++;
	}
	return (NULL);
}
