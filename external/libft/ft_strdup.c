/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkayadib <zkayadib@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:05:39 by zkayadib          #+#    #+#             */
/*   Updated: 2024/11/07 16:37:34 by zkayadib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	i;

	i = (ft_strlen(s1) + 1);
	str = malloc(sizeof(char) * i);
	if (str)
	{
		ft_strlcpy(str, s1, i);
	}
	return (str);
}
