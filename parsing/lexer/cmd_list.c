#include "../../includes/minishell.h"

t_cmd_lexer	**get_lexer_head(t_method method, t_cmd_lexer *syntax)
{
	static t_cmd_lexer	*head;
	t_cmd_lexer			*tmp;

	if (method == SET)
		head = syntax;
	else if (method == RESET)
	{
		while (head)
		{
			tmp = head;
			head = head->next;
			if (tmp->value != NULL)
				free(tmp->value);
			free(tmp);
		}
	}
	return (&head);
}

void	add_lexer_node(t_cmd_type type, char *value)
{
	t_cmd_lexer	*new_node;
	t_cmd_lexer	**head;
	t_cmd_lexer	*tmp;

	if (type == WORD && !value)
		return ;
	head = get_lexer_head(GET, NULL);
	tmp = *head;
	new_node = malloc(sizeof(t_cmd_lexer));
	new_node->type = type;
	new_node->value = value;
	new_node->next = NULL;
	if (head == NULL || *head == NULL)
		get_lexer_head(SET, new_node);
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
}
