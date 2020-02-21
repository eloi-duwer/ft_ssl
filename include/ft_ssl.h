/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 15:23:10 by eduwer            #+#    #+#             */
/*   Updated: 2020/02/21 17:42:31 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <libft.h>
# include <stdint.h>
# include <stdbool.h>

# define A 0
# define B 1
# define C 2
# define D 3
# define E 4
# define F 5
# define G 6
# define H 7

typedef struct	s_md5_ctx {
	unsigned char	*message;
	size_t			original_size;
	size_t			current_size;
	uint32_t		buffera;
	uint32_t		bufferb;
	uint32_t		bufferc;
	uint32_t		bufferd;
	uint32_t		*buffers[4];
	uint32_t		savea;
	uint32_t		saveb;
	uint32_t		savec;
	uint32_t		saved;

}				t_md5_ctx;

typedef struct	s_sha256_ctx {
	unsigned char	*message;
	size_t			original_size;
	size_t			current_size;
	uint32_t		hash[8];
	uint32_t		work_var[8];
	uint32_t		work_table[64];
}				t_sha256_ctx;

typedef	struct	s_ssl_args {
	bool			quiet;
	bool			reverse;
	bool			read_stdin;
	bool			print_stdin;
	char			**files;
	char			**strings;
	bool			stop_parsing;
	char			*(*hash_func) (char *input);
}				t_ssl_args;

char			*calc_md5(char *str);
char			*calc_sha256(char *str);
char			*print_bits(void *bytes, size_t size);
uint32_t		(*g_bitwise_operation[4]) (uint32_t x, uint32_t y, uint32_t z);
void			universal_md5_round(t_md5_ctx *ctx, int i, uint32_t buff[16]);
uint32_t		left_rotate(uint32_t buff, unsigned int amount);
uint32_t		right_rotate(uint32_t buff, unsigned int amount);
uint32_t		sha256_init(char i, uint32_t word);
uint32_t		sha256_s(char i, uint32_t word);
uint32_t		sha256_ch(uint32_t x, uint32_t y, uint32_t z);
uint32_t		sha256_maj(uint32_t x, uint32_t y, uint32_t z);

#endif
