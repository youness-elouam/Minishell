/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-boul <ael-boul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 09:38:57 by ael-boul          #+#    #+#             */
/*   Updated: 2025/07/03 15:33:06 by ael-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*p;
	unsigned char	*q;
	unsigned char	*temp;

	i = 0;
	p = (unsigned char *)dst;
	q = (unsigned char *)src;
	temp = (unsigned char *)malloc(len);
	if (!temp)
		return (NULL);
	while (i < len)
	{
		temp[i] = q[i];
		i++;
	}
	i = 0;
	while (i < len)
	{
		p[i] = temp[i];
		i++;
	}
	free(temp);
	return (dst);
}
