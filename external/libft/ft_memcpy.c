/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkayadib <zkayadib@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 09:25:13 by zkayadib          #+#    #+#             */
/*   Updated: 2024/11/13 03:51:44 by zkayadib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*s_dst;
	unsigned char	*s_src;
	size_t			i;

	if (!src && !dst)
		return (dst);
	s_dst = (unsigned char *)(dst);
	s_src = (unsigned char *)(src);
	i = 0;
	while (i < n)
	{
		s_dst[i] = s_src[i];
		i ++;
	}
	return (s_dst);
}
