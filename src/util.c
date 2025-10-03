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

int	ft_strncmp(const char *s1, const char *s2, int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		if (s1[i] == '\0' || s2[i] == '\0')
			break ;
		i++;
	}
	return (0);
}