/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:03:02 by aahlyel           #+#    #+#             */
/*   Updated: 2023/01/17 00:18:52 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	s_len;

	dest = NULL;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	s_len = ft_strlen(s + start);
	if (len > s_len)
		len = s_len;
	dest = ft_calloc(len + 1, sizeof(char));
	if (dest)
		ft_memcpy(dest, (s + start), len);
	return (dest);
}
