/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 11:07:54 by aweissha          #+#    #+#             */
/*   Updated: 2024/04/12 18:35:23 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	test_parse_tree(t_node *node)
{
	if (node == NULL)
	{
		printf("end of parse_tree reched\n");
		return ;
	}
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

void	test_env_list(t_data *data)
{
	t_env	*env_list;
	
	env_list = data->env_list;
	while (env_list != NULL)
	{
		printf("%s=%s\n", env_list->var_name, env_list->var_str);
		env_list = env_list->next;
	}
}
/*
int	main(int argc, char **argv, char **env)
{
	t_data	*data;
	t_token	*tmp;
	char	*input;
	t_token	*test_token;

	data = init_data(argc, argv, env);
	create_env_list(data);
	// test_env_list(data);
	
	input = readline("Minishell $> ");
	lexer(input, data);
	// return (0);

	// print token list before expansion
	tmp = data->token_list;
	while (tmp != NULL)
	{
		printf("type: %u\ntoken_str: %s\n", tmp->token_type, tmp->token_str);
		tmp = tmp->next;
	}

	expander(data);

	// // test expander
	// test_token = malloc(sizeof(t_token));
	// test_token->token_str = "ls\"-la\"";
	// printf("str_expanded: %s\n", expand_str(test_token, data));
	// return (0);

	// print token list after expansion
	tmp = data->token_list;
	while (tmp != NULL)
	{
		printf("type: %u\ntoken_str: %s\n", tmp->token_type, tmp->token_str);
		tmp = tmp->next;
	}
	
	

	data->parse_tree = parse_pipe(data->token_list);
	test_parse_tree(data->parse_tree);
}
*/


void    sig_action(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    rl_replace_line("", 1);
    rl_on_new_line();
    rl_redisplay();
        return ;
}


int	main(int argc, char **argv, char **env)
{
	t_data	*data;
	char	*input;

	data = init_data(argc, argv, env);
	create_env_list(data);
	

	while (1)
	{
		rl_catch_signals = 0;
        signal(SIGQUIT, SIG_IGN);
        signal(SIGINT, sig_action);
		input = readline("\x1b[32mMinishell $> \x1b[0m");
		if (!input)
		{
			free_everything(data);
			printf("exit\n");
			return (0);
		}
		signal(SIGINT, SIG_IGN);
		add_history(input);
		lexer(input, data);
		free(input);


		if (syntax_check(data) == 1)
		{
			free_token_list(data->token_list);
			data->token_list = NULL;
			continue ;
		}
		expander(data);
		data->parse_tree = parse_pipe(data->token_list);
		data->token_list = NULL;
		// test_parse_tree(data->parse_tree);
		data->last_exit_code = pre_exec(data->parse_tree, data);
		free_parse_tree(data->parse_tree);
		data->parse_tree = NULL;
	}
	return (0);
}
/*
To do:
- exit codes does no work anymore(value in data struct does not get changed)
- free memory, when command fails (unset PATH->ls)
- check eval sheet for edge cases
- clean history
- check for memory leaks
- Norminette
...
*/
