/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouam <yel-ouam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 10:30:46 by yel-ouam          #+#    #+#             */
/*   Updated: 2025/07/02 10:30:47 by yel-ouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <stdio.h>

void	*ft_malloc(size_t size);
void	ft_free(void *s);

typedef struct s_malloc
{
	void			*ptr;
	struct s_malloc	*next;
}	t_malloc;

#endif