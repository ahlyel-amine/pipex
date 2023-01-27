/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:02:50 by aahlyel           #+#    #+#             */
/*   Updated: 2023/01/23 20:31:22 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int	i;

	if (!*needle || (haystack == needle && ft_strlen(needle) == len))
		return ((char *)haystack);
	while (len && *haystack)
	{
		i = 0;
		while (*(needle + i) == *(haystack + i) && *(needle + i) && len--)
			if (!*(needle + ++i))
				return ((char *)(haystack));
		len += --i;
		haystack++;
	}
	return (NULL);
}
