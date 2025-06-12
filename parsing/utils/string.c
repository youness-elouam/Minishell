#include "../../includes/minishell.h"

char	*ft_substr(char *str, int start, int end)
{
	int		size;
	int		i;
	char	*cmd;

	size = end - start + 2;
	if (size - 2 < 0)
		return (NULL);
	cmd = malloc(sizeof(char) * size);
	i = 0;
	while (start <= end)
	{
		cmd[i] = str[start];
		start++;
		i++;
	}
	cmd[i] = '\0';
	return (cmd);
}

t_bool	is_space(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (true);
	return (false);
}
