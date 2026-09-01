/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kechan <kechan@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 12:20:19 by kechan            #+#    #+#             */
/*   Updated: 2026/09/01 20:47:02 by kechan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

char	*ft_strdup(const char *s)
{
	char	*string;
	void	*mem;
	void	*temp;
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	string = (char *)s;
	mem = (char *)malloc(i + 1);
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
	int				read_n;
	char			*buf;
	char			*temp;

	read_n = 1;
	if (pline == NULL)
		pline = ft_calloc(1, sizeof(char));
	buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (pline == NULL || buf == NULL)
	{
		free(pline);
		free(buf);
		return (NULL);
	}
	while (ft_strchr(buf, '\n') == 0 && read_n > 0)
	{
		read_n = read(fd, buf, BUFFER_SIZE);
		if (read_n <= 0)
			break ;
		buf[read_n] = '\0';
		temp = pline;
		pline = ft_strjoin(temp, buf, 0, 0);
		free (temp);
	}
	if (read_n == 0 || pline[0] != '\0')
	{
		free (buf);
		return (pline);
	}
	free (pline);
	return (NULL);
}

char	*extract_line(char *pline)
{
	size_t	i;
	char	*line;

	i = 0;
	if (pline == NULL)
		return (NULL);
	if (pline[0] == '\n')
	{
		line = ft_strdup("\n\0");
		return (line);
	}
	while ((pline[i] != '\n' && ft_strchr(pline, '\n') != 0)
		|| (pline[i] != '\0' && ft_strchr(pline, '\0') != 0
			&& ft_strchr(pline, '\n') == 0))
		i++;
	if (i == 0 && (pline[i] != '\0' || pline[i] != '\n'))
		return (NULL);
	line = ft_calloc(i + 2, sizeof(char));
	ft_memcpy(line, pline, i);
	if (ft_strchr(pline, '\n') != 0)
		line[i] = '\n';
	return (line);
}

char	*extract_remnant(char *pline)
{
	char	*remnant;
	size_t	npos;
	size_t	i;
	size_t	strl;

	strl = 0;
	while (pline[strl] != '\0')
		strl++;
	npos = 0;
	i = 0;
	if (pline == NULL || pline[0] == '\0' || ft_strchr(pline, '\n') == 0)
		return (NULL);
	if (ft_strchr(pline, '\n') != 0)
		while (pline[npos] != '\n')
			npos++;
	if (npos == 0 && ft_strchr(pline, '\n') == 0)
		return (NULL);
	if (ft_strchr(pline, '\n') != 0)
		pline++;
	if (pline[0] == '\n')
		remnant = ft_calloc(strl - npos, sizeof(char));
	else
		remnant = ft_calloc(strl - npos + 1, sizeof(char));
	while (pline[npos] != '\0')
		remnant[i++] = pline[npos++];
	return (remnant);
}

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
		free(storage);
		return (NULL);
	}
	line = extract_line(input);
	storage = extract_remnant(input);
	if (line == NULL && storage == NULL)
	{
		free(input);
		free(storage);
		return (NULL);
	}
	free(input);
	return (line);
}

// #include <stdio.h>
// int main(void)
// {
// 	int fd;
// 	char *output;

// 	// fd = open("test.txt", O_RDONLY);
// 	fd = 0;
// 	// fd = 0;

// 	output = "init val";
// 	// while (output != NULL)
// 	// {
// 	// 	output = get_next_line(fd);
// 	// 	printf("%s", output);
// 	// 	free(output);
// 	// }

// 			output = get_next_line(fd);
// 		printf("1: %s", output);
// 		free(output);

// 				output = get_next_line(fd);
// 		printf("2: %s", output);
// 		free(output);

// 				output = get_next_line(fd);
// 		printf("3: %s", output);
// 		free(output);

// 				output = get_next_line(fd);
// 		printf("4: %s", output);
// 		free(output);

// 				output = get_next_line(fd);
// 		printf("5: %s", output);
// 		free(output);

// 				output = get_next_line(fd);
// 		printf("6: %s", output);
// 		free(output);

// 				output = get_next_line(fd);
// 		printf("7: %s", output);
// 		free(output);

// 				output = get_next_line(fd);
// 		printf("8: %s", output);
// 		free(output);

// 				output = get_next_line(fd);
// 		printf("9: %s", output);
// 		free(output);

// 				output = get_next_line(fd);
// 		printf("10: %s", output);
// 		free(output);

// 				output = get_next_line(fd);
// 		printf("11: %s", output);
// 		free(output);

// 					output = get_next_line(fd);
// 		printf("12: %s", output);
// 		free(output);
// }
