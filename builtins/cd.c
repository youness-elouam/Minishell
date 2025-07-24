/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouam <yel-ouam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:21:22 by ael-boul          #+#    #+#             */
/*   Updated: 2025/07/24 17:08:47 by yel-ouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	print_cd_error(char *path)
{
	if (errno == EACCES)
		ft_putstr_fd("cd: permission denied: ", STDERR_FILENO);
	else if (errno == ENOENT)
		ft_putstr_fd("cd: No such file or directory: ", STDERR_FILENO);
	else if (errno == ENOTDIR)
		ft_putstr_fd("cd: Not a directory: ", STDERR_FILENO);
	else
		ft_putstr_fd("cd: error: ", STDERR_FILENO);
	ft_putendl_fd(path, STDERR_FILENO);
}

int	ft_cd(char **args)
{
	if (!args[1])
	{
		if (chdir(ft_getenv("HOME")) < 0)
		{
			ft_putstr_fd("cd: relative or absolute path required\n", STDERR_FILENO);
			return (1);
		}
		return (0);
	}
	if (args[2])
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	if (chdir(args[1]) < 0)
	{
		print_cd_error(args[1]);
		return (1);
	}
	return (0);
}
