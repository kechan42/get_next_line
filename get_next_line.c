/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kechan <kechan@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 12:20:19 by kechan            #+#    #+#             */
/*   Updated: 2026/08/17 20:50:01 by kechan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

#include <string.h>
#include <stdlib.h>
#include <stdint.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

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

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char	*str1;
// 	char	*str2;
// 	size_t	i;
// 	size_t	j;
// 	char	*mem;
// 	size_t	strlA;
// 	size_t	strlB;

// 	str1 = (char *) s1;
// 	str2 = (char *) s2;
// 	i = 0;
// 	j = 0;
// 	strlA = ft_strlen(str1);
// 	strlB = ft_strlen(str2);
// 	mem = malloc(strlA + strlB + 1);
// 	if (mem == NULL)
// 		return (NULL);
// 	while (i < strlA + strlB + 1)
// 	{
// 		while (i < strlA)
// 		{
// 			mem[i] = str1[i];
// 			i++;
// 		}
// 		while (j <= strlB)
// 			mem[i++] = str2[j++];
// 	}
// 	return (mem);
// }

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*mem;
	size_t	strl1;
	size_t	strl2;

	i = 0;
	j = 0;
	strl1 = ft_strlen(s1);
	strl2 = ft_strlen(s2);
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

char	*ft_strdup(const char *s)
{
	char	*string;
	void	*mem;
	void	*temp;

	string = (char *)s;
	mem = (char *)malloc(ft_strlen(s)+1);
	if (mem == NULL)
		return (NULL);
	temp = mem;
	while (*string != '\0')
	{
		ft_memset(temp++, *string, 1);
		string++;
	}
	ft_memset(temp, '\0', 1);
	return (mem);
}

char	*read_line(char *pline, int fd)
{
	char	*buf;
	char	*temp;
	ssize_t	read_res;

	if (!pline)
		pline = ft_calloc(1, sizeof(char));
	buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	read_res = 1;
	while (ft_strchr(pline, '\n') == 0 && read_res != 0)
	{
		read_res = read(fd, buf, BUFFER_SIZE);
		buf[read_res] = '\0';
		temp = pline;
		pline = ft_strjoin(temp, buf);
		free(temp);
	}
	if (read_res <= 0)
	{
		free(pline);
		free(buf);
		return (NULL);
	}
	free(buf);
	return (pline);
}

char	*extract_line(char *pline)
{
	size_t	i;
	char	*line;

	i = 0;
	if (pline == NULL || pline[0] == '\0')
		return (NULL);
	if (pline[i] == '\n')
	{
		line = ft_strdup("\0");
		return (line);
	}
	while (pline[i] != '\n')
		i++;
	line = calloc(i + 1, sizeof(char));
	ft_memcpy(line, pline, i);
	line[i] = '\0';
	return (line);
}

char	*extract_remnant(char *pline)
{
	char	*remnant;
	size_t	npos;
	size_t	i;
	size_t	strl;

	strl = ft_strlen(pline);
	npos = 0;
	i = 0;
	if (pline == NULL || pline[0] == '\0')
		return (NULL);
	while (pline[npos] != '\n')
		npos++;
	pline++;
	if (pline[0] == '\n')
		remnant = calloc(strl - npos, sizeof(char));
	else
		remnant = calloc(strl - npos + 1, sizeof(char));
	while (pline[npos] != '\0')
		remnant[i++] = pline[npos++];
	return (remnant);
}

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	unsigned int	i;
// 	size_t			strl;
// 	char			*res;

// 	i = 0;
// 	strl = ft_strlen(s);
// 	if (start >= strl || s[start] == '\0')
// 		return (ft_strdup(""));
// 	if (len > strl)
// 		len = strl;
// 	if (len == strl)
// 		res = malloc((len - start) + 1);
// 	else if (start + len > strl)
// 		res = malloc((strl - start) + 1);
// 	else
// 		res = malloc(len + 1);
// 	if (res == NULL)
// 		return (NULL);
// 	while (s[start] != '\0' && i < len)
// 		res[i++] = s[start++];
// 	res[i] = '\0';
// 	return (res);
// }

// char	*extract_remnant(char *pline)
// {
// 	char	*remnant;
// 	size_t	i;

// 	i = 0;
// 	if (pline == NULL)
// 		return (NULL);
// 	if (pline[i] == '\n')
// 	{
// 		pline++;
// 		remnant = ft_substr(pline, i, ft_strlen(pline));
// 		return (remnant);
// 	}
// 	while (pline[i] && pline[i] != '\n')
// 		i++;
// 	remnant = ft_substr(pline, i + 1, ft_strlen(pline));
// 	return (remnant);
// }

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*input;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	input = read_line(storage, fd);
	if (input == NULL)
	{
		free(input);
		return (NULL);
	}
	line = extract_line(input);
	storage = extract_remnant(input);
	free(input);
	return (line);
}

#include <stdio.h>
int main(void)
{
	int		fd;
	char	*output;

	output = "init";
	// fd = open("test.txt", O_RDONLY);
	fd = 0;
	while (output != NULL)
	{
		output = get_next_line(fd);
		printf("%s\n", output);
		free(output);
	}
	close(fd);
}
