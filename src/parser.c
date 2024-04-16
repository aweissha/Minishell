/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:36:48 by aweissha          #+#    #+#             */
/*   Updated: 2024/04/16 14:51:56 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
This function sets the node->command variable correct
and returns a pointer to an exec node.
*/
t_node	*parse_exec(t_token *token_list, t_data *data)
{
	t_node	*exec_node;

	if (token_list == NULL)
		return (NULL);
	exec_node = init_node(EXEC);
	if (exec_node == NULL)
		ft_error_and_free("Memory allocation of EXEC node failed\n",
			errno, data);
	add_command(token_list, exec_node, data);
	toklist_clear(&token_list);
	return (exec_node);
}

/**
this function returns a pointer to a redir node.
node->exec is set by calling the parse_exec() function.
If there is no redir present, parse_exec is called.
**/
t_node	*parse_redir(t_token *token_list, t_data *data)
{
	t_token	*redir_token;
	t_node	*redir_node;

	if (token_list == NULL)
		return (NULL);
	redir_token = find_token(token_list, REDIR);
	if (redir_token != NULL)
	{
		redir_node = init_node(REDIR);
		if (redir_node == NULL)
			ft_error_and_free("Memory allocation of REDIR node failed\n",
				errno, data);
		config_redir_node(redir_token, redir_node);
		update_token_list(&token_list);
		redir_node->next = parse_redir(token_list, data);
		return (redir_node);
	}
	else
		return (parse_exec(token_list, data));
}

/**
this function returns a pointer to a pipe node.
for left it calls the parse_redir() function,
because left will have no more Pipes,
for right it calls the parse_pipe function again.
If there is no pipe present, parse_redir is called.
**/
t_node	*parse_pipe(t_token *token_list, t_data *data)
{
	t_token	*pipe_token;
	t_node	*pipe_node;

	if (token_list == NULL)
		return (NULL);
	pipe_token = find_token(token_list, PIPE);
	if (pipe_token != NULL)
	{
		pipe_node = init_node(PIPE);
		if (pipe_node == NULL)
			ft_error_and_free("Memory allocation of PIPE node failed\n",
				errno, data);
		pipe_token->previous->next = NULL;
		pipe_token->next->previous = NULL;
		pipe_node->left = parse_redir(token_list, data);
		pipe_node->right = parse_pipe(pipe_token->next, data);
		free_token(pipe_token);
		return (pipe_node);
	}
	else
		return (parse_redir(token_list, data));
}
