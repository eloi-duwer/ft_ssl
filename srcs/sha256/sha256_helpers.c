/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 18:07:05 by eduwer            #+#    #+#             */
/*   Updated: 2020/02/18 00:13:02 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

uint32_t	sha256_init(char i, uint32_t word)
{
	if (i == 0)
		return (right_rotate(word, 7) ^ right_rotate(word, 18) ^ word >> 3);
	else
		return (right_rotate(word, 17) ^ right_rotate(word, 19) ^ word >> 10);
}

uint32_t	sha256_s(char i, uint32_t word)
{
	if (i == 1)
		return (right_rotate(word, 6) ^ right_rotate(word, 11) ^ \
			right_rotate(word, 25));
	else
		return (right_rotate(word, 2) ^ right_rotate(word, 13) ^ \
			right_rotate(word, 22));
}

uint32_t	sha256_ch(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x & y) ^ (~x & z));
}

uint32_t	sha256_maj(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x & y) ^ (x & z) ^ (y & z));
}
