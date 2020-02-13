/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 15:21:45 by eduwer            #+#    #+#             */
/*   Updated: 2020/02/14 00:34:00 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

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
	ft_memcpy(&ret[ctx->currentSize - 8], &ctx->originalSize, 8);
	ctx->message = ret;
}

static void update_poiters(t_md5_ctx *ctx, int i)
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

	j = -1;
	while (++j < 16)
		ft_memcpy(&buff[j], &ctx->message[i * (16 * 4) + j * 4], 4);
	ctx->saveA = ctx->bufferA;
	ctx->saveB = ctx->bufferB;
	ctx->saveC = ctx->bufferC;
	ctx->saveD = ctx->bufferD;
	j = -1;
	while (++j < 64)
	{
		universal_round(ctx, j, buff);
		update_poiters(ctx, j);
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
	ctx.bufferA = 0x67452301;
	ctx.bufferB = 0xefcdab89;
	ctx.bufferC = 0x98badcfe;
	ctx.bufferD = 0x10325476;
	ctx.buffers[0] = &ctx.bufferA;
	ctx.buffers[1] = &ctx.bufferB;
	ctx.buffers[2] = &ctx.bufferC;
	ctx.buffers[3] = &ctx.bufferD;
	i = 0;
	while (i < ctx.currentSize / (16 * 4))
		md5_loop(&ctx, i++);
	md5_print(ctx.bufferA, ctx.bufferB, ctx.bufferC, ctx.bufferD);
}

int			main(int argc, char **argv)
{
	calc_md5("");
	return (0);
}
