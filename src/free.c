/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 12:03:49 by aweissha          #+#    #+#             */
/*   Updated: 2024/04/12 14:38:00 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_token(t_token	*token)
{
	free(token->token_str);
	free(token);
}

void	free_token_list(t_token *token_list)
{
	t_token	*tmp;
	
	while (token_list != NULL)
	{
		tmp = token_list->next;
		free_token(token_list);
		token_list = tmp;
	}
}

void	free_env(t_env *env_node)
{
	free(env_node->var_name);
	free(env_node->var_str);
	free(env_node);
}

void	free_str_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		printf("str freed \n");
		i++;
	}
	free(array);
}

void	free_node(t_node *node)
{
	if (node->node_type == EXEC)
	{
		free_str_array(node->command);
		printf("array freed \n");
	}
	else if (node->node_type == REDINPT)
		free(node->infile);
	else if (node->node_type == REDOUT
		|| node->node_type == REDAPPND)
		free(node->outfile);
	else if (node->node_type == HEREDOC)
		free(node->limiter);
	printf("node of type %d freed\n", node->node_type);
	free(node);
}

void	free_parse_tree(t_node *node)
{
	if (node == NULL)
		return ;
	if (node->node_type == PIPE)
	{
		free_parse_tree(node->left);
		free_parse_tree(node->right);
	}
	else if (node->node_type == REDINPT
		|| node->node_type == REDOUT
		|| node->node_type == REDAPPND
		|| node->node_type == HEREDOC)
		free_parse_tree(node->next);
	free_node(node);
}

void	free_env_list(t_env *env_list)
{
	t_env	*tmp;
	
	while (env_list != NULL)
	{
		tmp = env_list->next;
		free_env(env_list);
		env_list = tmp;
	}
}

void	free_everything(t_data *data)
{
	free_parse_tree(data->parse_tree);
	data->parse_tree = NULL;
	free_env_list(data->env_list);
	data->env_list = NULL;
	free(data);
}
