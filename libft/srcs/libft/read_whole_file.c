/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_whole_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 20:03:01 by eduwer            #+#    #+#             */
/*   Updated: 2020/02/28 22:30:45 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

static int	remalloc_the_line(void **ptr, size_t *current_length)
{
	void	*newbuf;

	if ((newbuf = (void *)malloc(*current_length + READ_BUFF_SIZE)) == NULL)
		return (1);
	if (*current_length > 0 && *ptr)
	{
		ft_memcpy(newbuf, ptr, *current_length);
		free(ptr);
	}
	*ptr = newbuf;
	*current_length += READ_BUFF_SIZE;
	return (0);
}

int			read_whole_file(int fd, void **ptr, size_t *size)
{
	int		readsize;
	void	*ret;
	char	buff[READ_BUFF_SIZE];
	size_t	total_size;

	if ((ret = (void *)malloc(READ_BUFF_SIZE)) == NULL)
		return (1);
	total_size = 0;
	while ((readsize = read(fd, buff, READ_BUFF_SIZE)) == READ_BUFF_SIZE)
	{
		ft_memcpy(&ret[total_size], buff, readsize);
		if (remalloc_the_line(&ret, &total_size) != 0)
			return (1);
	}
	if (readsize == -1)
		return (1);
	ft_memcpy(&ret[total_size], buff, readsize);
	*ptr = ret;
	*size = total_size;
	return (0);
}
