/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-boul <ael-boul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 21:52:11 by ael-boul          #+#    #+#             */
/*   Updated: 2025/07/03 15:28:51 by ael-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*prev;

	if (*lst == NULL || !del)
		return ;
	current = *lst;
	while (current->next != NULL)
	{
		prev = current;
		del(current->content);
		ft_memdel(current);
		current = prev->next;
	}
	del(current->content);
	ft_memdel(current);
	*lst = NULL;
}
