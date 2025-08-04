/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_dir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouam <yel-ouam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:26:39 by yel-ouam          #+#    #+#             */
/*   Updated: 2025/07/27 21:11:31 by yel-ouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_dir(char *filename)
{
	struct stat	pro;

	if (stat(filename, &pro) == -1)
		return 0;
	return (S_ISDIR(pro.st_mode));
}
