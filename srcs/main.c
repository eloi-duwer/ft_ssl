/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 15:21:45 by eduwer            #+#    #+#             */
/*   Updated: 2020/01/31 17:29:04 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void padding(t_ctx *ctx) {
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

void initBuffer(t_ctx *ctx)
{
	ctx->bufferA = 0x01234567;
	ctx->bufferB = 0x98abcdef;
	ctx->bufferC = 0xfedcba98;
	ctx->bufferD = 0x76543210;
}

void calcMd5(char *str) {
	t_ctx ctx;
	ctx.message = ft_char_to_unsigned(str);
	ctx.originalSize = ft_strlen(str);
	padding(&ctx);
	initBuffer(&ctx);
}

int main(int argc, char **argv)
{
	calcMd5("coucou");
	return 0;
}
