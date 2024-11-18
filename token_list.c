#include "./include/minishell.h"


t_token_list *init_token_list(const t_scanner *scanner)
{
	t_token_list *new_token;
	t_token_list *head;    // Head of the linked list
	t_token_list *current;

	head = NULL;
	current = NULL;
	while (scanner_has_next(scanner))
	{
		new_token = OOM_GUARDS(malloc(sizeof(t_token_list)), __FILE__, __LINE__);
		new_token->token_type = scanner->next.type;
		new_token->token_value = ft_strndup(scanner->next.lexeme.start, scanner->next.lexeme.length);
		new_token->next_token = NULL;
		if (!head)
			head = new_token;  // First token becomes the head
		else
			current->next_token = new_token; // Link the new token
		current = new_token;  // Move to the new end of the list
		print_token(scanner->next);
	}
	return (head); // Return the head of the linked list
}
