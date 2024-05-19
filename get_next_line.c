/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emsen <emsen@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 14:30:03 by emsen             #+#    #+#             */
/*   Updated: 2024/01/06 15:19:03 by emsen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	rest = ft_readbuf(fd, rest);
	if (!rest)
		return (NULL);
	line = ft_getline(rest);
	rest = ft_getrest(rest);
	return (line);
}

char	*ft_readbuf(int fd, char *rest)
{
	char	*buf;
	int		b;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	b = 1;
	while (!ft_strchr(rest, '\n') && b)
	{
		b = read(fd, buf, BUFFER_SIZE);
		if (b == -1)
			return (free(rest), free(buf), NULL);
		buf[b] = '\0';
		rest = ft_strjoin(rest, buf);
		if (!rest)
			return (free(buf), NULL);
	}
	free(buf);
	return (rest);
}

char	*ft_getline(char *rest)
{
	char	*line;
	int		i;

	i = 0;
	if (!rest[i])
		return (NULL);
	while (rest[i] != '\n' && rest[i])
		i++;
	line = (char *) malloc((i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (rest[i] && rest[i] != '\n')
	{
		line[i] = rest[i];
		i++;
	}
	if (rest[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_getrest(char *rest)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	while (rest[i] && rest[i] != '\n')
		i++;
	if (!rest[i])
		return (free(rest), NULL);
	new = malloc((ft_strlen(rest + i) + 1));
	if (!new)
		return (free(rest), NULL);
	j = 0;
	i++;
	while (rest[i + j])
	{
		new[j] = rest[i + j];
		j++;
	}
	new[j] = '\0';
	free(rest);
	return (new);
}
