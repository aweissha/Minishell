/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 11:07:54 by aweissha          #+#    #+#             */
/*   Updated: 2024/03/22 13:48:31 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	test_parse_tree(t_node *node)
{
	if (node->node_type == PIPE)
	{
		printf("hello from PIPE node\n");
		test_parse_tree(node->left);
		test_parse_tree(node->right);
	}
	else if (node->node_type == REDINPT)
	{
		printf("hello from REDINPT node\n");
		test_parse_tree(node->next);
	}
	else if (node->node_type == REDOUT)
	{
		printf("hello from REDOUT node\n");
		test_parse_tree(node->next);
	}
	else if (node->node_type == REDAPPND)
	{
		printf("hello from REDAPPND node\n");
		test_parse_tree(node->next);
	}
	else if (node->node_type == HEREDOC)
	{
		printf("hello from HEREDOC node\n");
		test_parse_tree(node->next);
	}
	else if (node->node_type == EXEC)
	{
		printf("hello from EXEC node. Here comes the command:");
		int i = 0;
		while (node->command[i] != NULL)
		{
			printf("%s ", node->command[i]);
			i++;
		}
		printf("\n");
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;
	t_token	*tmp;
	char	*input;

	input = readline("Minishell $> ");
	data = init_data(argc, argv, env);
	lexer(input, data);

	tmp = data->token_list;
	while (tmp != NULL)
	{
		printf("type: %u\ntoken_str: %s\n", tmp->token_type, tmp->token_str);
		tmp = tmp->next;
	}
	data->parse_tree = parse_pipe(data->token_list);
	test_parse_tree(data->parse_tree);
}
