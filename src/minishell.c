/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:42:48 by aweissha          #+#    #+#             */
/*   Updated: 2024/03/13 18:41:53 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// void	handle_input(char *input, t_data *data)
// {
// 	lexer(input, data);
// 	parser(data);
// 	executer(data);
// }

/*
This function sets the node->command variable correct and returns a pointer to an exec node.
*/
t_node	*parse_exec(t_data *data)
{
	
}

/**
this function returns a pointer to a redir node.
node->exec is set by calling the parse_exec() function.
If there is no redir present, parse_exec is called.
**/
t_node	*parse_redir(t_data *data)
{
	
}

/**
this function returns a pointer to a pipe node.
for left it calls the parse_redir() function, because left will have no more Pipes,
for right it calls the parse_pipe function again.
If there is no pipe present, parse_redir is called.
**/
t_node	*parse_pipe(t_data *data)
{
	t_node	*pipe_node;

	// 1) look if there is a pipe
	if (seek(input, "|") != 0)
	{
		pipe_node = init_pipe_node();
		pipe_node->right = parse_pipe(ft_strchr(input, '|') + 1);
		pipe_node->left = parse_redir(term_left_str(input));
		return (pipe_node);
	}
	else
		return (parse_redir(input));
}

// function should return the top of the parse tree
t_node	*parse_input(char *input, t_data *data)
{
	t_node	*parse_tree;

	lexer(input, data);
	parse_tree = parse_pipe(data);

	return (parse_tree);
}

/** function should execute all commands, by starting at the top of the parse tree 
 * and calling itself whenever following a fork to another node **/
void	run_commands(t_node *node)
{
	// add the correct conditions for each type of node	
	// call itself, whenever its not the bottom of the parse tree (which is an EXEC type node)
	// how to implement these function: video shell program explained
	if (node->type == EXEC)
		run_exec(node);
	else if (node->type == PIPE)
		run_pipe(node);
	else if (node->type == BUILDIN)
		run_buildin(node);
	else if (node->type == REDIR)
		run_redir(node);
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_data	*data;

	data = init_data(argc, argv, env);
	while (1)
	{
		input = readline("Minishell $> ");
		// If input is NULL, user entered EOF (Ctrl+D)
		if (input == NULL)
		{
			printf("\n");
			break ;
		}
		// else if (ft_strcmp(input, "exit") == 0)
		// {
		// 	free(input);
		// 	exit(0);
		// }
		
		// Check for cd command and chdir in the parent process if needed
	
		// If input is empty, prompt again
		else if (ft_strlen(input) == 0)
			free(input);
		else
		{
			// printf("you entered: %s\n", input);
			if (ft_fork() == 0)
				run_commands(parse_input(input, data));
			wait(NULL);
		}
	}
	// free(data);
}


// Plan:
/*


- implement quotes '' and ""
- cd -



*/