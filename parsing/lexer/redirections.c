#include "../../includes/minishell.h"

t_redirections	**get_redi_head(t_method method, t_redirections *syntax)
{
	static t_redirections	*head;
	t_redirections			*tmp;

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

void	add_redi_node(t_cmd_type type, char *value)
{
	t_redirections	*new_node;
	t_redirections	**head;
	t_redirections	*tmp;

	if (type == WORD && !value)
		return ;
	head = get_redi_head(GET, NULL);
	tmp = *head;
	new_node = malloc(sizeof(t_redirections));
	new_node->type = type;
	new_node->value = value;
	new_node->next = NULL;
	if (head == NULL || *head == NULL)
		get_redi_head(SET, new_node);
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
}
