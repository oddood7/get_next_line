/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 15:38:47 by lde-mais          #+#    #+#             */
/*   Updated: 2023/01/13 14:15:56 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	find_newline(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*get_line(char *str)
{
	int		i;
	int		len;
	char	*dest;

	i = 0;
	if (!str[i])
		return (NULL);
	len = 0;
	while (str[len] && str[len] != '\n')
		len++;
	dest = malloc((len * sizeof(char)) + 2);
	if (!dest || !str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
	{
		dest[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*get_new_line(int fd, char *str)
{
	int		rd;
	char	*buff;

	rd = 1;
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	buff[0] = '\0';
	while (rd != 0 && !find_newline(buff))
	{
		rd = read(fd, buff, BUFFER_SIZE);
		if (rd == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[rd] = '\0';
		str = ft_strjoin(str, buff);
	}
	free(buff);
	return (str);
}

char	*left_line(char *str)
{
	int		i;
	int		j;
	char	*dest;

	j = 0;
	i = 0;
	while (str[i] != '\n' && str[i])
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	dest = malloc((ft_strlen(str) - i + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	i++;
	while (str[i + j])
	{
		dest[j] = str[i + j];
		j++;
	}
	dest[j] = '\0';
	free(str);
	return (dest);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	str = get_new_line(fd, str);
	if (!str)
		return (NULL);
	line = get_line(str);
	str = left_line(str);
	return (line);
}
