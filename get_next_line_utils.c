/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kechan <kechan@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 12:34:04 by kechan            #+#    #+#             */
/*   Updated: 2026/08/18 17:53:21 by kechan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "get_next_line.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t		i;
	char		*scopy;
	void		*os;

	i = 0;
	os = s;
	while (i < n)
	{
		scopy = (char *)s;
		*scopy = c;
		s++;
		i++;
	}
	return (os);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*odest;
	char		*osrc;
	void		*os;

	i = 0;
	os = dest;
	if (dest == src && dest == NULL)
		return (os);
	while (i < n)
	{
		odest = (char *)dest;
		osrc = (char *)src;
		*odest = *osrc;
		dest++;
		src++;
		i++;
	}
	return (os);
}

char	*ft_strjoin(char const *s1, char const *s2, size_t i, size_t j)
{
	char	*mem;
	size_t	strl1;
	size_t	strl2;

	strl1 = 0;
	strl2 = 0;
	while (s1[strl1] != '\0')
		strl1++;
	while (s2[strl2] != '\0')
		strl2++;
	mem = malloc(strl1 + strl2 + 1);
	if (mem == NULL)
		return (NULL);
	while (i < strl1 + strl2 + 1)
	{
		while (i < strl1)
		{
			mem[i] = s1[i];
			i++;
		}
		while (j <= strl2)
			mem[i++] = s2[j++];
	}
	return (mem);
}

char	*ft_strchr(const char *s, int c)
{
	char	*scopy;

	scopy = (char *)s;
	if ((unsigned char)c == '\0')
	{
		while (*scopy != '\0')
			scopy++;
		return (scopy);
	}
	while (*scopy != '\0')
	{
		if (*scopy == (char) c)
			return (scopy);
		scopy++;
	}
	return (0);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void				*emptymem;
	void				*zeroedmem;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (SIZE_MAX / nmemb < size)
		return (NULL);
	emptymem = malloc(nmemb * size);
	if (emptymem == NULL)
		return (NULL);
	zeroedmem = ft_memset(emptymem, 0, nmemb * size);
	if (zeroedmem == NULL)
		return (NULL);
	return (zeroedmem);
}
