/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 13:46:28 by ysumeral          #+#    #+#             */
/*   Updated: 2025/10/03 13:56:25 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/util.h"

char	*ft_strrchr(char *s, int c)
{
	int	slen;
    int	i;

	slen = 0;
	while (s[slen] != '\0')
		slen++;
	while (*(s + slen) != (char)c && slen > 0)
		slen--;
	if (*(s + slen) == (char)c)
		return ((char *)(s + slen));
	else
		return (NULL);
}