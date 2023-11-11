/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 08:42:57 by aarponen          #+#    #+#             */
/*   Updated: 2023/07/25 17:11:08 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>

char	*pre_ft_strjoin(char *line, char *temp_buffer)
{
	char	*str;

	if (temp_buffer[0] == '\0' && !line)
	{
		free(temp_buffer);
		return (NULL);
	}
	if (!line)
	{
		line = (char *)malloc(sizeof(char) * 1);
		if (!line)
		{
			free(temp_buffer);
			return (NULL);
		}
		line[0] = '\0';
	}
	str = ft_strjoin(line, temp_buffer);
	if (!str)
		free(temp_buffer);
	free(line);
	return (str);
}

char	*go_to_next_line(char *line)
{
	char	*next_line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i] != '\n' && line[i])
		i++;
	if (line[i] == '\0')
	{
		free(line);
		return (NULL);
	}
	while (line[i + j])
		j++;
	next_line = ft_substr(line, i + 1, j);
	if (!next_line)
	{
		free(line);
		return (NULL);
	}
	free(line);
	return (next_line);
}

char	*ft_read_line(int fd, char *reading_line)
{
	int		read_bytes;
	char	*temp_buffer;

	temp_buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp_buffer)
		return (NULL);
	read_bytes = 1;
	while (!ft_strchr(reading_line, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, temp_buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			if (reading_line)
				free(reading_line);
			free(temp_buffer);
			return (NULL);
		}
		temp_buffer[read_bytes] = '\0';
		reading_line = pre_ft_strjoin(reading_line, temp_buffer);
		if (!reading_line)
			return (NULL);
	}
	free(temp_buffer);
	return (reading_line);
}

char	*copy_new_line(char *line)
{
	char	*new_line;
	int		i;

	i = 0;
	while (line[i] != '\n' && line[i])
		i++;
	new_line = ft_substr(line, 0, i + 1);
	if (!new_line)
	{
		free(line);
		line = NULL;
		return (NULL);
	}
	return (new_line);
}

char	*get_next_line(int fd)
{
	static char	*reading_line[1024];
	char		*new_line;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	reading_line[fd] = ft_read_line(fd, reading_line[fd]);
	if (!reading_line[fd])
		return (NULL);
	if (reading_line[fd][0] == '\0')
	{
		free(reading_line[fd]);
		reading_line[fd] = NULL;
		return (NULL);
	}
	new_line = copy_new_line(reading_line[fd]);
	if (!new_line)
		return (NULL);
	reading_line[fd] = go_to_next_line(reading_line[fd]);
	return (new_line);
}
// ssize_t custom_read(int fd, void *buf, size_t count)
// {
// 	if (fd && buf && count > 0)
//     	return (-1);
// 	else
// 		return (0);
// }
// void* custom_malloc(size_t size) 
// {
//     if (size > 0)
// 		return NULL;
// 	else
// 		return (ft_strdup(""));
// }
// int	main(void)
// {
// 	char	*line;
// 	int		line_nbr;
// 	int		test_file;
// 	int		test_file_1;
// 	int		test_file_2;
// 	test_file = open("fi.txt", O_RDONLY);
// 	// test_file = 0;
// 	test_file_1 = open("en.txt", O_RDONLY);
// 	test_file_2 = open("de.txt", O_RDONLY);
// 	line_nbr = 1;
// 	while (line_nbr <= 3)
// 	{
// 		line = get_next_line(test_file);
// 		if (!line)
// 			return (0);
// 		printf("File %d Line %d: %s", test_file, line_nbr, line);
// 		free(line);
// 		line = NULL;
// 		line = get_next_line(test_file_1);
// 		if (!line)
// 			return (0);
// 		printf("File %d Line %d: %s", test_file_1, line_nbr, line);
// 		free(line);
// 		line = NULL;
// 		line = get_next_line(test_file_2);
// 		if (!line)
// 			return (0);
// 		printf("File %d Line %d: %s", test_file_2, line_nbr, line);
// 		free(line);
// 		line = NULL;
// 		line_nbr++;
// 	}
// 	close(test_file);
// 	return (0);
// }