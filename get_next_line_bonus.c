/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 08:42:57 by aarponen          #+#    #+#             */
/*   Updated: 2023/07/24 21:35:33 by aarponen         ###   ########.fr       */
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

t_fd_node	*find_or_create_fd_node(t_fd_node **head, int fd)
{
	t_fd_node	*node;
	t_fd_node	*temp;

	node = *head;
	while (node)
	{
		if (node->fd == fd)
			return (node);
		node = node->next;
	}
	node = (t_fd_node *)malloc(sizeof(*node));
	if (!node)
	{
		while (*head)
		{
			temp = *head;
			*head = (*head)->next;
			free(temp);
		}
		return (NULL);
	}
	node->fd = fd;
	node->reading_line = NULL;
	node->next = *head;
	*head = node;
	return (node);
}

char	*get_next_line(int fd)
{
	static t_fd_node	*head;
	t_fd_node			*current_fd;
	char				*new_line;
	int					i;

	current_fd = find_or_create_fd_node(&head, fd);
	if (!current_fd || fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	current_fd->reading_line = ft_read_line(fd, current_fd->reading_line);
	if (!current_fd->reading_line)
		return (NULL);
	if (current_fd->reading_line[0] == '\0')
	{
		free(current_fd->reading_line);
		current_fd->reading_line = NULL;
		return (NULL);
	}
	i = 0;
	while (current_fd->reading_line[i] && current_fd->reading_line[i] != '\n')
		i++;
	new_line = ft_substr(current_fd->reading_line, 0, i + 1);
	if (!new_line)
		return (NULL);
	current_fd->reading_line = go_to_next_line(current_fd->reading_line);
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
// 		printf("Line %d: %s", line_nbr, line);
// 		free(line);
// 		line = NULL;
// 		line = get_next_line(test_file_1);
// 		if (!line)
// 			return (0);
// 		printf("Line %d: %s", line_nbr, line);
// 		free(line);
// 		line = NULL;
// 		line = get_next_line(test_file_2);
// 		if (!line)
// 			return (0);
// 		printf("Line %d: %s", line_nbr, line);
// 		free(line);
// 		line = NULL;
// 		line_nbr++;
// 	}
// 	close(test_file);
// 	return (0);
// }