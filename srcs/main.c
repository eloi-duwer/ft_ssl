/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 15:21:45 by eduwer            #+#    #+#             */
/*   Updated: 2020/02/13 23:30:02 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

const unsigned int g_md5_sin[] =
{
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

const unsigned int g_md5_rotation[] =
{
	7, 12, 17, 22, 5, 9, 14, 20, 4, 11, 16, 23, 6, 10, 15, 21
};

void print_bits(unsigned char *msg, unsigned int length) {
	for (int i = 0; i < length; i++) {
		unsigned char c = msg[i];
		for (int j = 7; 0 <= j; j--) {
			printf("%c", (c & ( 1 << j)) ? '1' : '0');
		}
		printf("\n");
	}
}

static void append_size(uint64_t size, unsigned char *msg, size_t length)
{
	unsigned char	*ptr;
	int				i;

	size *= 8;
	ptr = (unsigned char *) &size;
	ft_memcpy(&msg[length - 8], ptr, 8);
}

static void	padding(t_md5_ctx *ctx)
{
	int				padding_size;
	unsigned char	*ret;

	padding_size = 56 - ctx->originalSize % 64;
	if (padding_size <= 0)
		padding_size += 64;
	padding_size += 8;
	ret = (unsigned char *)ft_memalloc(sizeof(unsigned char) * \
		(ctx->originalSize + padding_size));
	ft_memcpy(ret, ctx->message, ctx->originalSize);
	ret[ctx->originalSize] = 1 << 7 & 0xFF;
	ctx->currentSize = ctx->originalSize + padding_size;
	append_size(ctx->originalSize, ret, ctx->currentSize);
	ctx->message = ret;
}

static void	init_ctx(t_md5_ctx *ctx)
{
	ctx->bufferA = 0x67452301;
	ctx->bufferB = 0xefcdab89;
	ctx->bufferC = 0x98badcfe;
	ctx->bufferD = 0x10325476;
	ctx->buffers[0] = &ctx->bufferA;
	ctx->buffers[1] = &ctx->bufferB;
	ctx->buffers[2] = &ctx->bufferC;
	ctx->buffers[3] = &ctx->bufferD;
}

static void rotate_buffers(t_md5_ctx *ctx)
{
	uint32_t	*mem;

	mem = ctx->buffers[3];
	ctx->buffers[3] = ctx->buffers[2];
	ctx->buffers[2] = ctx->buffers[1];
	ctx->buffers[1] = ctx->buffers[0];
	ctx->buffers[0] = mem;
}

static void	md5_loop(t_md5_ctx *ctx, int i)
{
	uint32_t	buff[16];
	int			j;

	j = 0;
	while (j < 16)
	{
		ft_memcpy(&buff[j], &ctx->message[i * (16 * 4) + j * 4], 4);
		++j;
	}
	ctx->saveA = ctx->bufferA;
	ctx->saveB = ctx->bufferB;
	ctx->saveC = ctx->bufferC;
	ctx->saveD = ctx->bufferD;
	j = 0;
	while (j < 64)
	{
		g_rounds[j / 16](ctx, j, buff);
		printf("%u %u %u %u\n", ctx->bufferA,ctx->bufferB,ctx->bufferC,ctx->bufferD);
		printf("BEFOR %p %p %p %p\n", ctx->buffers[0],ctx->buffers[1],ctx->buffers[2],ctx->buffers[3]);
		rotate_buffers(ctx);
		printf("AFTER %p %p %p %p\n", ctx->buffers[0],ctx->buffers[1],ctx->buffers[2],ctx->buffers[3]);
		++j;
	}
	ctx->bufferA += ctx->saveA;
	ctx->bufferB += ctx->saveB;
	ctx->bufferC += ctx->saveC;
	ctx->bufferD += ctx->saveD;
}

void		md5_print(uint32_t bufA, uint32_t bufB, uint32_t bufC, uint32_t bufD)
{
	unsigned char res[16];
	int i;

	ft_memcpy(res, &bufA, 4);
	ft_memcpy(res + 4, &bufB, 4);
	ft_memcpy(res + 8, &bufC, 4);
	ft_memcpy(res + 12, &bufD, 4);
	i = 0;
	while (i < 16)
	{
		printf("%02x", res[i]);
		++i;
	}
	printf("\n");

}

void		calc_md5(char *str)
{
	int			i;
	t_md5_ctx	ctx;

	ctx.message = ft_char_to_unsigned(str);
	ctx.originalSize = ft_strlen(str);
	padding(&ctx);
	init_ctx(&ctx);
	i = 0;
	while (i < ctx.currentSize / (16 * 4))
	{
		md5_loop(&ctx, i);
		++i;
	}
	printf("%d rounds\n", i);
	md5_print(ctx.bufferA, ctx.bufferB, ctx.bufferC, ctx.bufferD);
}

int			main(int argc, char **argv)
{
	calc_md5("");
	return (0);
}
