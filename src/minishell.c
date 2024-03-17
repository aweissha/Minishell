/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:42:48 by aweissha          #+#    #+#             */
/*   Updated: 2024/03/17 17:35:41 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// void	handle_input(char *input, t_data *data)
// {
// 	lexer(input, data);
// 	parser(data);
// 	executer(data);
// }

int	ft_lstsize(t_token *token_list)
{
	t_list	*tmp;
	int		i;

	if (token_list == NULL)
		return (0);
	tmp = token_list;
	i = 1;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

void	ft_lstclear(t_token **token_list)
{
	t_list	*tmp;

	tmp = *token_list;
	while (tmp != NULL)
	{
		tmp = (*token_list)->next;
		free((*token_list)->token_str);
		free((*token_list));
		*token_list = tmp;
	}
}

/*
This function sets the node->command variable correct and returns a pointer to an exec node.
*/
t_node	*parse_exec(t_token *token_list)
{
	int		nb_tokens;
	t_node	*exec_node;
	int		i;
	t_token	*tmp;
	
	nb_tokens = ft_lstsize(token_list);
	exec_node = init_node(EXEC);
	exec_node->command = malloc(sizeof(char *) * (nb_tokens + 1));
	i = 0;
	tmp = token_list;
	while (i < nb_tokens)
	{
		exec_node->command[i] = ft_strdup(tmp->token_str);
		tmp = tmp->next;
		i++;
	}
	exec_node->command[i] = NULL;
	ft_lstclear(token_list);
	return (exec_node);
}

void	update_token_list(t_token **token_list, t_token *redir_token)
{
	t_token	*tmp;
	t_token	*tmp2;

	if ((*token_list)->token_str == REDIR)
	{
		tmp = *token_list;
		*token_list = (*token_list)->next->next;
		(*token_list)->previous = NULL;
		free_token(tmp);
		free_token(tmp->next);
	}
	else
	{
		tmp = *token_list;
		while (tmp->next->token_str != REDIR)
			tmp = tmp->next;
		tmp2 = tmp;
		tmp = tmp->next->next->next;
		free_token(tmp2->next);
		free_token(tmp->next->next);
		tmp2->next = tmp;
		if (tmp != NULL)
			tmp->previous = tmp2;
	}
}

void	config_redir_node(t_token *redir_token, t_node *redir_node)
{
	char	*token_str;
	
	token_str = redir_token->token_str;
	if (ft_strcmp(token_str, "<") == 0)
	{
		redir_node->node_type = REDINPT;
		redir_node->infile = redir_token->next->token_str;
	}
	else if (ft_strcmp(token_str, ">") == 0)
	{
		redir_node->node_type = REDOUT;
		redir_node->outfile = redir_token->next->token_str;
	}
	else if (ft_strcmp(token_str, ">>") == 0)
	{
		redir_node->node_type = REDAPPND;
		redir_node->outfile = redir_token->next->token_str;
	}
	else if (ft_strcmp(token_str, "<<") == 0)
	{
		redir_node->node_type = HEREDOC;
		redir_node->limiter = redir_token->next->token_str;
	}
}

/**
this function returns a pointer to a redir node.
node->exec is set by calling the parse_exec() function.
If there is no redir present, parse_exec is called.
**/
t_node	*parse_redir(t_token *token_list)
{
	t_token	*redir_token;
	t_node	*redir_node;

	redir_token = find_token(token_list, REDIR);
	if (redir_token != NULL)
	{
		redir_node = init_node(REDIR);
		if (redir_node == NULL)
			ft_error("Memory allocation of REDIR node failed", errno);
		config_redir_node(redir_token, redir_node);
		update_token_list(&token_list, redir_token);
		if (find_token(token_list, REDIR) != NULL)
			redir_node->next = parse_redir(token_list);
		else
			redir_node->next = parse_exec(token_list);
		return (redir_node);
	}
	else
		return (parse_exec(token_list));
}

t_node	*init_node(type node_type)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (node == NULL)
		return (NULL);
	if (node_type == PIPE)
		node->node_type = PIPE;
	else if (node_type == REDIR)
		node->node_type = REDIR;
	else if (node_type == EXEC)
		node->node_type = EXEC;	
	node->command = NULL;
	node->infile = NULL;
	node->outfile = NULL;
	node->limiter = NULL;
	node->next = NULL;
	node->left = NULL;
	node->right = NULL;
}

t_token	*find_token(t_token	*token_list, type token_type)
{
	while (token_list != NULL)
	{
		if (token_list->token_type == token_type)
			return (token_list);
		token_list = token_list->next;
	}
	return (NULL);
}

/**
this function returns a pointer to a pipe node.
for left it calls the parse_redir() function, because left will have no more Pipes,
for right it calls the parse_pipe function again.
If there is no pipe present, parse_redir is called.
**/
t_node	*parse_pipe(t_data *data)
{
	t_token	*token_list;
	t_token	*pipe_token;
	t_node	*pipe_node;

	token_list = data->token_list;
	pipe_token = find_token(token_list, PIPE);
	if (pipe_token != NULL)
	{
		pipe_node = init_node(PIPE);
		if (pipe_node == NULL)
			ft_error("Memory allocation of PIPE node failed", errno);
		pipe_token->previous->next = NULL;
		pipe_token->next->previous = NULL;
		pipe_node->left = parse_redir(token_list);
		pipe_node->right = parse_pipe(pipe_token->next);
		free_token(pipe_token);
		return (pipe_node);
	}
	else
		return (parse_redir(token_list));
}

// function should return the top of the parse tree
t_node	*parse_input(char *input, t_data *data)
{
	t_node	*parse_tree;

	// check_syntax(input);
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
	if (node->node_type == EXEC)
		run_exec(node);
	else if (node->node_type == PIPE)
		run_pipe(node);
	else if (node->node_type == BUILDIN)
		run_buildin(node);
	else if (node->node_type == REDIR)
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
			free(input);
		}
	}
	free(data);
}


// Plan:
/*


- implement quotes '' and ""
- cd -



*/