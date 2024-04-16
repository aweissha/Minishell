/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 12:03:49 by aweissha          #+#    #+#             */
/*   Updated: 2024/04/16 15:16:25 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_token(t_token	*token)
{
	if (token->token_str != NULL)
		free(token->token_str);
	free(token);
}

void	free_env(t_env *env_node)
{
	if (env_node->var_name != NULL)
		free(env_node->var_name);
	if (env_node->var_name != NULL)
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
		i++;
	}
	free(array);
}

void	free_node(t_node *node)
{
	if (node == NULL)
		return ;
	if (node->node_type == EXEC)
	{
		if (node->command != NULL)
			free_str_array(node->command);
	}
	else if (node->node_type == REDINPT
		&& node->infile != NULL)
		free(node->infile);
	else if ((node->node_type == REDOUT
		|| node->node_type == REDAPPND)
		&& node->outfile != NULL)
		free(node->outfile);
	else if (node->node_type == HEREDOC
		&& node->limiter != NULL)
		free(node->limiter);
	free(node);
}
