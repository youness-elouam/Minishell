/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip_space.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-boul <ael-boul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 09:41:21 by ael-boul          #+#    #+#             */
/*   Updated: 2025/05/31 09:41:23 by ael-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_skip_space(const char *str, int *i)
{
	while ((str[*i] == ' ' || str[*i] == '\t') || (str[*i] == '\r'
			|| str[*i] == '\v' || str[*i] == '\f'))
		(*i)++;
}
