/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkayadib <zkayadib@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 21:31:50 by zkayadib          #+#    #+#             */
/*   Updated: 2024/11/13 04:07:57 by zkayadib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*c;
	int		i;

	i = ft_strlen(s1) + ft_strlen(s2);
	c = malloc(sizeof(char) * (i + 1));
	if (!c)
		return (NULL);
	ft_strlcpy(c, s1, ft_strlen(s1) + 1);
	ft_strlcat(c, s2, i + 1);
	return (c);
}
