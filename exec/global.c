/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouam <yel-ouam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 09:46:20 by ael-boul          #+#    #+#             */
/*   Updated: 2025/07/16 16:01:29 by yel-ouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_const	g_n = {.error = 1, .success = 0, .buff_size = 4096, .empty = 0,
	.pipe = 6,
	.end = 7, .stdin_fd = 0, .stdout_fd = 1, .stderr_fd = 2, .skip = 1,
	.no_skip = 0, .unknown_command = 127, .is_directory = 126};