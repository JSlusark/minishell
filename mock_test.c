/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mock_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 16:10:27 by jslusark          #+#    #+#             */
/*   Updated: 2024/11/10 16:10:40 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void print_tree(t_node *node) {
	if (!node) {
		printf("NULL\n");
		return;
	}

	if (node->node_type == COMMAND) {
		printf("COMMAND Node:\n");
		printf("  Command: %s\n", node->data.command_sequence->curr->lexeme.start);
		if (node->data.command_sequence->next)
			printf("  Argument: %s\n", node->data.command_sequence->next->lexeme.start);
	} else if (node->node_type == BINARY) {
		printf("BINARY Node:\n");
		printf("  Operator: %s\n", node->data.pair_node.binary_operator.lexeme.start);
		printf("  Left:\n");
		print_tree(node->data.pair_node.node_l);
		printf("  Right:\n");
		print_tree(node->data.pair_node.node_r);
	}
}

void test_parse_with_mock_data() {
	// Test case 1: "echo hello"
	printf("Testing 'echo hello':\n");
	t_mock_scanner *scanner1 = mock_scanner_init(mock_tokens_1, sizeof(mock_tokens_1) / sizeof(mock_tokens_1[0]));
	t_node *tree1 = parse(scanner1);
	print_tree(tree1);
	free(tree1);
	free(scanner1);

	// Test case 2: "echo hello | cat"
	printf("\nTesting 'echo hello | cat':\n");
	t_mock_scanner *scanner2 = mock_scanner_init(mock_tokens_2, sizeof(mock_tokens_2) / sizeof(mock_tokens_2[0]));
	t_node *tree2 = parse(scanner2);
	print_tree(tree2);
	free(tree2);
	free(scanner2);
}

int main() {
	test_parse_with_mock_data();
	return 0;
}
