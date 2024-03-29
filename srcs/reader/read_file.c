/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 18:03:30 by dshatilo          #+#    #+#             */
/*   Updated: 2024/01/18 10:00:02 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

char		*get_file_content(int fd, char *file_content);
static char	*add_to_string(char *s, char *buffer, size_t buf_len);
static char	*ft_strncpy(char *dest, char *src, size_t n);
void		check_newlines(char *file_content);

char	*read_file(char *filename)
{
	char	*file_content;
	int		fd;

	if (open_close_file("open", filename, &fd) != 0)
		exit(1);
	file_content = (char *)ft_calloc(1, sizeof(char));
	if (file_content)
		file_content = get_file_content(fd, file_content);
	if (open_close_file("close", filename, &fd) != 0)
	{
		if (file_content)
			free(file_content);
		exit(1);
	}
	if (!file_content)
		exit(0);
	check_newlines(file_content);
	return (file_content);
}

char	*get_file_content(int fd, char *file_content)
{
	char	*buffer;
	int		bytes;

	buffer = (char *)calloc(10000, sizeof(char));
	if (!buffer)
	{
		free(file_content);
		return (NULL);
	}
	while (file_content)
	{
		bytes = read(fd, buffer, 10000);
		if (bytes == -1)
		{
			free(file_content);
			free(buffer);
			return (NULL);
		}
		if (bytes == 0)
			break ;
		file_content = add_to_string(file_content, buffer, bytes);
		ft_bzero(buffer, bytes);
	}
	free(buffer);
	return (file_content);
}

static char	*add_to_string(char *s, char *buffer, size_t buf_len)
{
	size_t	s_len;
	size_t	new_len;
	char	*new_s;

	s_len = ft_strlen(s);
	if ((size_t)(-1) - s_len - 1 < buf_len)
	{
		free(s);
		return (NULL);
	}
	new_len = s_len + buf_len;
	new_s = (char *)malloc(sizeof(char) * (new_len + 1));
	if (!new_s)
	{
		free(s);
		return (NULL);
	}
	new_s[new_len] = 0;
	ft_strncpy(new_s, s, s_len);
	ft_strncpy(new_s + s_len, buffer, buf_len);
	free(s);
	return (new_s);
}

static char	*ft_strncpy(char *dest, char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(dest + i) = *(src + i);
		i++;
	}
	return (dest);
}

void	check_newlines(char *file_content)
{
	size_t	i;
	char	*temp;

	temp = file_content;
	while (*temp)
	{
		if (*temp == '\t')
			*temp = ' ';
		temp++;
	}
	if (*file_content == '\n')
	{
		free(file_content);
		exit(1);
	}
	i = 0;
	while (file_content[i])
	{
		if (file_content[i] == '\n' && file_content[i + 1] == '\n')
		{
			free(file_content);
			exit(1);
		}
		i++;
	}
}
