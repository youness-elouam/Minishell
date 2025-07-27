/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouam <yel-ouam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:02:01 by ael-boul          #+#    #+#             */
/*   Updated: 2025/07/26 20:35:10 by yel-ouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	nb_args(char **args)
{
	int	size;

	size = 0;
	while (args[size])
		size++;
	return (size);
}

static int	check_n_option(char **args, int *i)
{
	int	n_option;

	n_option = 0;
	while (args[*i] && ft_strcmp(args[*i], "-n") == 0)
	{
		n_option = 1;
		(*i)++;
	}
	return (n_option);
}

static void	print_echo_args(char **args, int i, t_mini *mini)
{
	while (args[i])
	{
		if (ft_strcmp(args[i], "$?") == 0)
			ft_putnbr_fd(mini->ret, 1);
		else
			ft_putstr_fd(args[i], 1);
		if (args[i + 1] && args[i][0] != '\0')
			write(1, " ", 1);
		i++;
	}
}

int	ft_echo(t_mini *mini, char **args)
{
	int	i;
	int	n_option;

	i = 1;
	n_option = 0;
	if (nb_args(args) > 1)
	{
		n_option = check_n_option(args, &i);
		print_echo_args(args, i, mini);
	}
	if (n_option == 0)
		write(1, "\n", 1);
	mini->ret = 0;
	return (mini->ret);
}
