/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rounds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 14:36:33 by eduwer            #+#    #+#             */
/*   Updated: 2020/02/13 23:12:12 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint32_t rotate(uint32_t buff, unsigned int amount)
{
	return (buff << amount | buff >> (32 - amount));
}

void round1(t_md5_ctx *ctx, int i, uint32_t buff[16])
{
	*ctx->buffers[0] = (*ctx->buffers[1] + rotate(((*ctx->buffers[0] + \
		f(*ctx->buffers[1], *ctx->buffers[2], *ctx->buffers[3]) + \
		(uint32_t) buff[i] + g_md5_sin[i])), g_md5_rotation[i % 4]));
}

void round2(t_md5_ctx *ctx, int i, uint32_t buff[16])
{
	int k;

	k = (1 + ((i - 16) * 5)) % 16;
	*ctx->buffers[0] = (*ctx->buffers[1] + rotate(((*ctx->buffers[0] + \
		g(*ctx->buffers[1], *ctx->buffers[2], *ctx->buffers[3]) + \
		(uint32_t) buff[k] + g_md5_sin[i])), g_md5_rotation[4 + i % 4]));
}

void round3(t_md5_ctx *ctx, int i, uint32_t buff[16])
{
	int k;

	k = (5 + ((i - 32) * 3)) % 16;
	*ctx->buffers[0] = (*ctx->buffers[1] + rotate(((*ctx->buffers[0] + \
		h(*ctx->buffers[1], *ctx->buffers[2], *ctx->buffers[3]) + \
		(uint32_t) buff[k] + g_md5_sin[i])), g_md5_rotation[8 + i % 4]));
}

void round4(t_md5_ctx *ctx, int j, uint32_t buff[16])
{
	int k;

	k = (0 + ((j - 48) * 7)) % 16;
	*ctx->buffers[0] = (*ctx->buffers[1] + rotate(((*ctx->buffers[0] + \
		i(*ctx->buffers[1], *ctx->buffers[2], *ctx->buffers[3]) + \
		(uint32_t) buff[k] + g_md5_sin[j])), g_md5_rotation[12 + j % 4]));
}

void	(*g_rounds[4]) (t_md5_ctx *ctx, int i, uint32_t buff[16]) =
{
	round1,
	round2,
	round3,
	round4
};
