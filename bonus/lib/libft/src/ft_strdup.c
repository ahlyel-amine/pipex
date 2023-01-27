/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:13:32 by aahlyel           #+#    #+#             */
/*   Updated: 2023/01/23 20:31:22 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dst;
	int		count;

	count = -1;
	dst = (char *)ft_calloc((ft_strlen(s1) + 1), sizeof(char));
	if (!dst)
		return (NULL);
	while (*(char *)(s1 + ++count))
		*(dst + count) = *(char *)(s1 + count);
	return (dst);
}
