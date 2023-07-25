/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 08:43:09 by aarponen          #+#    #+#             */
/*   Updated: 2023/07/25 11:17:11 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char		*get_next_line(int fd);
char		*copy_new_line(char *line);
char		*ft_read_line(int fd, char *reading_line);
char		*go_to_next_line(char *line);
size_t		ft_strlen(const char *str);
char		*ft_strjoin(const char *s1, const char *s2);
char		*pre_ft_strjoin(char *line, char *temp_buffer);
char		*ft_strchr(const char *s, int c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strdup(const char *s);
//ssize_t custom_read(int fd, void *buf, size_t count);
// void* custom_malloc(size_t size);

#endif
