/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 15:23:10 by eduwer            #+#    #+#             */
/*   Updated: 2020/02/14 00:36:08 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <libft.h>
# include <stdint.h>

typedef struct	s_md5_ctx {
	unsigned char 	*message;
	size_t			originalSize;
	size_t			currentSize;
	uint32_t		bufferA;
	uint32_t		bufferB;
	uint32_t		bufferC;
	uint32_t		bufferD;
	uint32_t		*buffers[4];
	uint32_t		saveA;
	uint32_t		saveB;
uint32_t		saveC;
	uint32_t		saveD;

}				t_md5_ctx;

uint32_t	(*g_bitwise_operation[4]) (uint32_t x, uint32_t y, uint32_t z);
void		universal_round(t_md5_ctx *ctx, int i, uint32_t buff[16]);

#endif
