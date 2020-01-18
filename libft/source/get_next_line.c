/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 11:28:57 by daron             #+#    #+#             */
/*   Updated: 2019/11/16 14:19:40 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static t_descriptor		*ft_next_file_descriptor(const int fd,
		t_descriptor **first_file)
{
	t_descriptor			*elem;

	elem = *first_file;
	while (elem)
	{
		if (elem->fd == fd)
			return (elem);
		elem = elem->next;
	}
	if (!(elem = (t_descriptor*)malloc(sizeof(t_descriptor))))
		return (NULL);
	elem->fd = fd;
	elem->str = ft_strnew(0);
	elem->next = *first_file;
	*first_file = elem;
	return (elem);
}

static char				*ft_join_file_str(char **str, char *buf,
		size_t str_count)
{
	char				*newstr;

	if (!(newstr = ft_strnew(str_count + ft_strlen(buf) + 1)))
		return (NULL);
	ft_strcpy(newstr, *str);
	ft_strcat(newstr, buf);
	ft_strdel(str);
	*str = ft_strdup(newstr);
	ft_strdel(&newstr);
	return (*str);
}

static char				*write_in_line(char **line, char **fileline)
{
	size_t				i;
	char				*newstr;

	i = 0;
	while ((*fileline)[i] != '\n' && (*fileline)[i])
		i++;
	*line = ft_strnew(i);
	ft_strncpy(*line, *fileline, i);
	if (*fileline && ft_strchr(*fileline, '\n'))
		newstr = ft_strdup(ft_strchr(*fileline, '\n') + 1);
	else
		newstr = ft_strnew(0);
	(*line)[i] = '\0';
	ft_strdel(fileline);
	return (newstr);
}

void					delete_element(t_descriptor **head, t_descriptor *elem)
{
	t_descriptor	*tmp;
	t_descriptor	*rem;

	tmp = *head;
	while (tmp && tmp->next)
	{
		if (tmp == elem)
		{
			rem = tmp->next;
			tmp->next = tmp->next->next;
			free(rem->str);
			free(rem);
		}
		else
			tmp = tmp->next;
	}
	tmp = *head;
	if (tmp == elem)
	{
		*head = tmp->next;
		free(tmp->str);
		free(tmp);
	}
}

int						get_next_line(const int fd, char **line)
{
	size_t				read_count;
	char				buf[BUFF_SIZE + 1];
	static t_descriptor	*head;
	t_descriptor		*elem;

	if (fd < 0 || !line || read(fd, buf, 0) < 0)
		return (-1);
	elem = ft_next_file_descriptor(fd, &head);
	while ((read_count = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[read_count] = '\0';
		elem->str = ft_join_file_str(&elem->str, buf, ft_strlen(elem->str));
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (!ft_strlen(elem->str))
		return (0);
	elem->str = write_in_line(line, &elem->str);
	if (elem->str[0] == '\0')
		delete_element(&head, elem);
	return (1);
}
