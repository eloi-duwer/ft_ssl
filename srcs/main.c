/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 15:21:45 by eduwer            #+#    #+#             */
/*   Updated: 2020/02/02 23:09:41 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static const unsigned int md5_sin[] =
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

static const unsigned int md5_rotation[] =
{
	7, 12, 17, 22, 5, 9, 14, 20, 4, 11, 16, 23, 6, 10, 15, 21
};

static void padding(t_md5_ctx *ctx) {
	int	paddingSize;
	unsigned char	*ret;

	paddingSize = 56 - ctx->originalSize % 64;
	if (paddingSize <= 0)
		paddingSize += 64;
	paddingSize += 8;
	ret = (unsigned char *)ft_memalloc(sizeof(unsigned char) * \
		(ctx->originalSize + paddingSize));
	ft_memcpy(ret, ctx->message, ctx->originalSize);
	ret[ctx->originalSize] = 1 << 8 & 0xFF;
	ctx->currentSize = ctx->originalSize + paddingSize;
	ft_memcpy(&ret[ctx->currentSize - 2], &(ctx->originalSize), 8);
	ctx->message = ret;
}

static void initBuffer(t_md5_ctx *ctx)
{
	ctx->bufferA = 0x67452301;
	ctx->bufferB = 0xefcdab89;
	ctx->bufferC = 0x98badcfe;
	ctx->bufferD = 0x10325476;
}

static void md5_loop(t_md5_ctx *ctx, int i)
{
	unsigned char buff[16 * 4];

	ft_memcpy(buff, &(ctx->message[i * 16]), 16 * 4);
	ctx->saveA = ctx->bufferA;
	ctx->saveB = ctx->bufferB;
	ctx->saveC = ctx->bufferC;
	ctx->saveD = ctx->bufferD;
}

void calcMd5(char *str)
{
	int i;

	t_md5_ctx ctx;
	ctx.message = ft_char_to_unsigned(str);
	ctx.originalSize = ft_strlen(str);
	padding(&ctx);
	initBuffer(&ctx);
	i = 0;
	while (i < ctx.currentSize / 16)
	{
		md5_loop(&ctx, i);
		++i;
	}
}

int main(int argc, char **argv)
{
	calcMd5("coucou");
	return 0;
}
