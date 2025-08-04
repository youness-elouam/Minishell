/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouam <yel-ouam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:01:36 by ael-boul          #+#    #+#             */
/*   Updated: 2025/08/04 13:40:18 by yel-ouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	magic_box(char *path, t_cmd *cmd, t_env *env)
{
	char	**env_array;

	env_array = env_list_to_array(env);
	execve(path, cmd->args, env_array);
	perror("execve failed");
	free_tab(env_array);
	return (0);
}

// char	*path_join(const char *s1, const char *s2)
// {
// 	char	*tmp;
// 	char	*path;

// 	tmp = ft_strjoin(s1, "/");
// 	path = ft_strjoin(tmp, s2);
// 	ft_memdel(tmp);
// 	return (path);
// }

// char	*check_dir(char *bin, char *command)
// {
// 	DIR				*folder;
// 	struct dirent	*item;
// 	char			*path;

// 	path = NULL;
// 	folder = opendir(bin);
// 	if (!folder)
// 		return (NULL);
// 	item = readdir(folder);
// 	while (item)
// 	{
// 		if (ft_strcmp(item->d_name, command) == 0)
// 			path = path_join(bin, item->d_name);
// 		item = readdir(folder);
// 	}
// 	closedir(folder);
// 	return (path);
// }

// static char	*get_valid_path(char **args, char **bin)
// {
// 	int		i;
// 	char	*path;

// 	if (!args[0] && !bin[0])
// 	{
// 		free_tab(bin);
// 		return (NULL);
// 	}
// 	path = check_dir(bin[0] + 5, args[0]);
// 	i = 1;
// 	while (args[0] && bin[i] && !path)
// 		path = check_dir(bin[i++], args[0]);
// 	return (path);
// }

// int	exec_bin(char **args, t_env *env, t_mini *mini)
// {
// 	char	**bin;
// 	char	*path;
// 	int		ret;

// 	printf("dhfghdgfdgfhdghfgfgdsghdgfhdgfhdgfhdsgfjdgdshfsdjfds\n\n\n");
// 	path = get_cmd_path(args[0], env);
// 	ret = g_n.unknown_command;
// 	while (env && env->value && ft_strncmp(env->value, "PATH=", 5) != 0)
// 		env = env->next;
// 	if (env == NULL || env->next == NULL)
// 		return (magic_box(path, mini->start_cmd, env, mini));
// 	bin = ft_split(env->value, ':');
// 	path = get_valid_path(args, bin);
// 	if (path)
// 	{
// 		ft_memdel(mini->start_cmd->path);
// 		mini->start_cmd->path = path;
// 		ret = magic_box(path, mini->start_cmd, env, mini);
// 	}
// 	else
// 	{
// 		//ret = magic_box(path, mini->start_cmd, env, mini);
// 	}
// 	free_tab(bin);
// 	ft_memdel(path);
// 	return (ret);
// }
