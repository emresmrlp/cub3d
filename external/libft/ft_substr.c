/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkayadib <zkayadib@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:14:47 by zkayadib          #+#    #+#             */
/*   Updated: 2024/11/13 04:07:14 by zkayadib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*c;

	if (start >= (ft_strlen(s)))
		return (ft_strdup(""));
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	if ((ft_strlen(s) - start) < len)
		len = (ft_strlen(s) - start);
	c = malloc(sizeof(char) * len + 1);
	i = 0;
	while (i < start)
		i ++;
	if (c)
		ft_strlcpy(c, s + i, len + 1);
	return (c);
}
