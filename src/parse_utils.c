/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:22:25 by aweissha          #+#    #+#             */
/*   Updated: 2024/04/16 12:36:50 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	add_command(t_token *token_list, t_node *exec_node, t_data *data)
{
	int		nb_tokens;
	int		i;
	t_token	*tmp;

	nb_tokens = toklist_size(token_list);
	exec_node->command = malloc(sizeof(char *) * (nb_tokens + 1));
	if (exec_node->command == NULL)
		ft_error_and_free("Memory allocation of command failed\n",
			errno, data);
	i = 0;
	tmp = token_list;
	while (i < nb_tokens)
	{
		exec_node->command[i] = ft_strdup(tmp->token_str);
		if (exec_node->command[i] == NULL)
			ft_error_and_free("Memory allocation of command_str failed\n",
				errno, data);		
		tmp = tmp->next;
		i++;
	}
	exec_node->command[i] = NULL;
}

void	update_token_list(t_token **token_list)
{
	t_token	*tmp;
	t_token	*tmp2;

	tmp = *token_list;
	if ((*token_list)->token_type == REDIR)
	{
		*token_list = (*token_list)->next->next;
		if (*token_list != NULL)
			(*token_list)->previous = NULL;
		free_token(tmp->next);
		free_token(tmp);
	}
	else
	{
		while (tmp->next->token_type != REDIR)
			tmp = tmp->next;
		tmp2 = tmp;
		tmp = tmp->next->next->next;
		free_token(tmp2->next->next);
		free_token(tmp2->next);
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
		redir_node->infile = ft_strdup(redir_token->next->token_str);
	}
	else if (ft_strcmp(token_str, ">") == 0)
	{
		redir_node->node_type = REDOUT;
		redir_node->outfile = ft_strdup(redir_token->next->token_str);
	}
	else if (ft_strcmp(token_str, ">>") == 0)
	{
		redir_node->node_type = REDAPPND;
		redir_node->outfile = ft_strdup(redir_token->next->token_str);
	}
	else if (ft_strcmp(token_str, "<<") == 0)
	{
		redir_node->node_type = HEREDOC;
		redir_node->limiter = ft_strdup(redir_token->next->token_str);
	}
}

t_token	*find_token(t_token	*token_list, t_type token_type)
{
	while (token_list != NULL)
	{
		if (token_list->token_type == token_type)
			return (token_list);
		token_list = token_list->next;
	}
	return (NULL);
}
