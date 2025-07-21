/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouam <yel-ouam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 12:37:14 by ael-boul          #+#    #+#             */
/*   Updated: 2025/07/16 16:01:18 by yel-ouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*join_path(const char *dir, const char *cmd)
{
	size_t	len_dir;
	size_t	len_cmd;
	char	*full_path;

	len_dir = strlen(dir);
	len_cmd = strlen(cmd);
	full_path = malloc(len_dir + len_cmd + 2);
	if (!full_path)
		return (NULL);
	strcpy(full_path, dir);
	if (dir[len_dir - 1] != '/')
		strcat(full_path, "/");
	strcat(full_path, cmd);
	return (full_path);
}

static char	*check_direct_path(char *cmd)
{
	if (strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	return (NULL);
}

static char	*search_in_path(char *cmd, char *path_env)
{
	char	**paths;
	char	*full_path;
	int		i;

	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = join_path(paths[i], cmd);
		if (!full_path)
			break ;
		if (access(full_path, X_OK) == 0)
		{
			free_tab(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_tab(paths);
	return (NULL);
}

char	*get_cmd_path(char *cmd, t_env *env)
{
	char	*path_env;
	char	*direct;

	if (!cmd)
		return (NULL);
	path_env = NULL;
	direct = check_direct_path(cmd);
	if (direct)
		return (direct);
	while (env)
	{
		if (ft_strncmp(env->value, "PATH=", 5) == 0)
		{
			path_env = env->value + 5;
			break ;
		}
		env = env->next;
	}
	if (!path_env)
		return (NULL);
	return (search_in_path(cmd, path_env));
}

int	error_message(char *path)
{
	DIR	*folder;
	int	fd;
	int	ret;

	fd = open(path, O_WRONLY);
	folder = opendir(path);
	ft_putstr_fd("minishell: ", g_n.stderr_fd);
	ft_putstr_fd(path, g_n.stderr_fd);
	if (ft_strchr(path, '/') == NULL)
		ft_putendl_fd(": command not found", g_n.stderr_fd);
	else if (fd == -1 && folder == NULL)
		ft_putendl_fd(": No such file or directory", g_n.stderr_fd);
	else if (fd == -1 && folder != NULL)
		ft_putendl_fd(": is a directory", g_n.stderr_fd);
	else if (fd != -1 && folder == NULL)
		ft_putendl_fd(": Permission denied", g_n.stderr_fd);
	if (ft_strchr(path, '/') == NULL || (fd == -1 && folder == NULL))
		ret = g_n.unknown_command;
	else
		ret = g_n.is_directory;
	if (folder)
		closedir(folder);
	ft_close(fd);
	return (ret);
}
