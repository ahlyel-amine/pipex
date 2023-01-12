/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 03:03:40 by aahlyel           #+#    #+#             */
/*   Updated: 2023/01/12 14:03:20 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	returnlen;
	size_t	i;

	i = -1;
	returnlen = ft_strlen(src);
	if (!dstsize)
		return (returnlen);
	dstlen = ft_strlen(dst);
	if (dstlen > dstsize)
		return (returnlen + dstsize);
	returnlen += dstlen;
	while (*src && dstlen < dstsize - 1)
		*(dst + dstlen++) = *(src++);
	*(dst + dstlen) = '\0';
	return (returnlen);
}
