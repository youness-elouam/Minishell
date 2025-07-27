/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouam <yel-ouam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 09:38:51 by ael-boul          #+#    #+#             */
/*   Updated: 2025/07/27 02:57:28 by yel-ouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../../includes/minishell.h"

void	*ft_memdel(void *ptr)
{
	if (ptr)
	{
		ft_free(ptr);
		ptr = NULL;
	}
	return (NULL);
}
