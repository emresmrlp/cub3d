/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkayadib <zkayadib@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:41:04 by zkayadib          #+#    #+#             */
/*   Updated: 2024/11/13 04:15:57 by zkayadib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*mllc;
	int		i;
	int		j;

	i = ft_strlen(s);
	j = 0;
	mllc = malloc(sizeof(char) * (i + 1));
	if (!mllc)
		return (NULL);
	while (j < i)
	{
		mllc[j] = f(j, s[j]);
		j ++;
	}
	mllc[i] = '\0';
	return (mllc);
}
