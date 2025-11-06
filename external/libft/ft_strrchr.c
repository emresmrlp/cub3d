/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkayadib <zkayadib@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 19:48:47 by zkayadib          #+#    #+#             */
/*   Updated: 2024/11/13 03:11:44 by zkayadib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	l;

	l = ft_strlen(s) - 1;
	if ((char)c == '\0')
	{
		l ++;
		return ((char *) &s[l]);
	}
	while (l >= 0 && s[l])
	{
		if (s[l] == (char)c)
			return ((char *)(s + l));
		l --;
	}
	return (NULL);
}
