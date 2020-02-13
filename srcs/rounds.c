/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rounds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 14:36:33 by eduwer            #+#    #+#             */
/*   Updated: 2020/02/13 11:19:04 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint32_t rotate(uint32_t buff, unsigned int amount)
{
	return (buff << amount | buff >> (32 - amount));
}

void round1(t_md5_ctx *ctx, int i, uint32_t buff[16])
{
	if (i % 4 == 0)
		ctx->bufferA = (ctx->bufferB + rotate(((ctx->bufferA + \
			f(ctx->bufferB, ctx->bufferC, ctx->bufferD) + \
			(uint32_t) buff[i] + g_md5_sin[i])), g_md5_rotation[i % 4]));
	else if (i % 4 == 1)
		ctx->bufferD =  (ctx->bufferA + rotate(((ctx->bufferD + \
			f(ctx->bufferA, ctx->bufferB, ctx->bufferC) + \
			(uint32_t) buff[i] + g_md5_sin[i])), g_md5_rotation[i % 4]));
	else if (i % 4 == 2)
		ctx->bufferC = (ctx->bufferD + rotate(((ctx->bufferC + \
			f(ctx->bufferD, ctx->bufferA, ctx->bufferB) + \
			(uint32_t) buff[i] + g_md5_sin[i])), g_md5_rotation[i % 4]));
	else if (i % 4 == 3)
		ctx->bufferB = (ctx->bufferC + rotate(((ctx->bufferB + \
			f(ctx->bufferC, ctx->bufferD, ctx->bufferA) + \
			(uint32_t) buff[i] + g_md5_sin[i])), g_md5_rotation[i % 4]));
}

void round2(t_md5_ctx *ctx, int i, uint32_t buff[16])
{
	int k;

	k = (1 + ((i - 16) * 5)) % 16;
	if (i % 4 == 0)
		ctx->bufferA = (ctx->bufferB + rotate(((ctx->bufferA + \
			g(ctx->bufferB, ctx->bufferC, ctx->bufferD) + \
			(uint32_t) buff[k] + g_md5_sin[i])), g_md5_rotation[4 + i % 4]));
	else if (i % 4 == 1)
		ctx->bufferD =  (ctx->bufferA + rotate(((ctx->bufferD + \
			g(ctx->bufferA, ctx->bufferB, ctx->bufferC) + \
			(uint32_t) buff[k] + g_md5_sin[i])), g_md5_rotation[4 + i % 4]));
	else if (i % 4 == 2)
		ctx->bufferC = (ctx->bufferD + rotate(((ctx->bufferC + \
			g(ctx->bufferD, ctx->bufferA, ctx->bufferB) + \
			(uint32_t) buff[k] + g_md5_sin[i])), g_md5_rotation[4 + i % 4]));
	else if (i % 4 == 3)
		ctx->bufferB = (ctx->bufferC + rotate(((ctx->bufferB + \
			g(ctx->bufferC, ctx->bufferD, ctx->bufferA) + \
			(uint32_t) buff[k] + g_md5_sin[i])), g_md5_rotation[4 + i % 4]));
}

void round3(t_md5_ctx *ctx, int i, uint32_t buff[16])
{
	int k;

	k = (5 + ((i - 32) * 3)) % 16;
	if (i % 4 == 0)
		ctx->bufferA = (ctx->bufferB + rotate(((ctx->bufferA + \
			h(ctx->bufferB, ctx->bufferC, ctx->bufferD) + \
			(uint32_t) buff[k] + g_md5_sin[i])), g_md5_rotation[8 + i % 4]));
	else if (i % 4 == 1)
		ctx->bufferD =  (ctx->bufferA + rotate(((ctx->bufferD + \
			h(ctx->bufferA, ctx->bufferB, ctx->bufferC) + \
			(uint32_t) buff[k] + g_md5_sin[i])), g_md5_rotation[8 + i % 4]));
	else if (i % 4 == 2)
		ctx->bufferC = (ctx->bufferD + rotate(((ctx->bufferC + \
			h(ctx->bufferD, ctx->bufferA, ctx->bufferB) + \
			(uint32_t) buff[k] + g_md5_sin[i])), g_md5_rotation[8 + i % 4]));
	else if (i % 4 == 3)
		ctx->bufferB = (ctx->bufferC + rotate(((ctx->bufferB + \
			h(ctx->bufferC, ctx->bufferD, ctx->bufferA) + \
			(uint32_t) buff[k] + g_md5_sin[i])), g_md5_rotation[8 + i % 4]));
}

void round4(t_md5_ctx *ctx, int j, uint32_t buff[16])
{
	int k;

	k = (0 + ((j - 48) * 7)) % 16;
	if (j % 4 == 0)
		ctx->bufferA = (ctx->bufferB + rotate(((ctx->bufferA + \
			i(ctx->bufferB, ctx->bufferC, ctx->bufferD) + \
			(uint32_t) buff[k] + g_md5_sin[j])), g_md5_rotation[12 + j % 4]));
	else if (j % 4 == 1)
		ctx->bufferD =  (ctx->bufferA + rotate(((ctx->bufferD + \
			i(ctx->bufferA, ctx->bufferB, ctx->bufferC) + \
			(uint32_t) buff[k] + g_md5_sin[j])), g_md5_rotation[12 + j % 4]));
	else if (j % 4 == 2)
		ctx->bufferC = (ctx->bufferD + rotate(((ctx->bufferC + \
			i(ctx->bufferD, ctx->bufferA, ctx->bufferB) + \
			(uint32_t) buff[k] + g_md5_sin[j])), g_md5_rotation[12 + j % 4]));
	else if (j % 4 == 3)
		ctx->bufferB = (ctx->bufferC + rotate(((ctx->bufferB + \
			i(ctx->bufferC, ctx->bufferD, ctx->bufferA) + \
			(uint32_t) buff[k] + g_md5_sin[j])), g_md5_rotation[12 + j % 4]));
}

void	(*g_rounds[4]) (t_md5_ctx *ctx, int i, uint32_t buff[16]) =
{
	round1,
	round2,
	round3,
	round4
};
